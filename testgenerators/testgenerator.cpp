#ifndef TESTGENERATOR_CPP
#define TESTGENERATOR_CPP

#include "testgenerator.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <exception>
#include <unordered_set>

namespace testgenerator {

using namespace std;

template <typename T>
TestGenerator<T>::TestGenerator() : mutator(nullptr) {}

template <typename T>
TestGenerator<T>::~TestGenerator() {
    if (mutator) delete mutator;
}

template <typename T>
void TestGenerator<T>::setMutator(Mutator<T>* m) {
    if (mutator) delete mutator;
    mutator = m;
}

template <typename T>
bool TestGenerator<T>::isValid(T) { return true; }

template <typename T>
T TestGenerator<T>::deepCopy(T t) { return t; }

template <typename T> 
bool TestGenerator<T>::ends_with(const string & value, const string & ending) {
    if (ending.size() > value.size()) {
        return false;
    }
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

template <typename T>
vector<T> TestGenerator<T>::generateTest(T base) {
    vector<T> result;
    if (!mutator) return result;
    auto mutations = mutator->getMutations(base);
    for (auto& mutation : mutations) {
        try {
            T mutated = mutation(deepCopy(base));
            result.push_back(mutated);
        } catch (...) {
            // If mutation fails, skip this mutation
        }
    }
    return result;
}

template <typename T>
set<T>& TestGenerator<T>::generateTests(set<unsigned int>&) {
    cout << "Generating tests using guided mutation ..." << endl;
    testcases.clear();

    // 1. Start with a random test case as seed
    T seed = generateRandomTest();
    queue<T> q;
    q.push(seed);

    unordered_set<string> seen_coverage;
    //float threshold = 90.0f;

    while (!q.empty() && toContinue()) {
        T t = q.front(); q.pop();
        if (!isValid(t)) {
            deleteTest(t);
            continue;
        }

        bool error_in_put = false;
        try {
            callPUT(t);
        } catch (const exception& e) {
            cerr << "Error in callPUT: " << e.what() << endl;
            error_in_put = true;
        } catch (...) {
            cerr << "Unknown error in callPUT." << endl;
            error_in_put = true;
        }

        float coverage = getCoverage();
        string cov_str = to_string(coverage);

        // Only keep if new coverage or queue is empty
        if (!error_in_put && (seen_coverage.find(cov_str) == seen_coverage.end() || q.empty())) {
            testcases.insert(t);
            seen_coverage.insert(cov_str);

            // Apply all mutations and enqueue all results
            vector<T> mutated_cases = generateTest(t);
            for (T m : mutated_cases) {
                if (isValid(m)) {
                    q.push(m);
                } else {
                    deleteTest(m);
                }
            }
        } else {
            deleteTest(t);
        }

        //if (coverage >= threshold) break;
    }
    getCoverage();
    return testcases;
}

namespace fs = std::filesystem;
template <typename T>
vector<string> TestGenerator<T>::getFileList(string path) {
    vector<string> fileNames;
    for (const auto& entry : fs::directory_iterator(path)) {
        string fileName = entry.path();
        if(ends_with(fileName, ".json")) {
            fileNames.push_back(fileName);
        }
    }
    return fileNames;
}

template <typename T>
void TestGenerator<T>::writeToFile(string s, string fname) {
    ofstream fout(fname);
    fout << s;
    fout.close();
}

template <typename T>
void TestGenerator<T>::deleteDirectoryContents(const filesystem::path& dir) {
    for (const auto& entry : filesystem::directory_iterator(dir))
        filesystem::remove_all(entry.path());
}

template <typename T>
void TestGenerator<T>::writeAllTestsToFile() {
    string dirName = "test/testcases/";
    filesystem::create_directories(dirName);
    deleteDirectoryContents(dirName);
    unsigned int i = 1;
    for(const auto& t : testcases) {
        string json = toJSON(t);
        string fileName = "t" + to_string(i) + ".json";
        string path = dirName + fileName;
        cout << "Writing test file: " << path << endl;
        writeToFile(json, path);
        i++;
    }
}


} // namespace testgenerator

#endif
