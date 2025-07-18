#ifndef TESTGENERATOR_CPP
#define TESTGENERATOR_CPP

#include "testgenerator.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <exception>
#include <unordered_set>

namespace testgenerator
{

    using namespace std;

    template <typename T>
    TestGenerator<T>::TestGenerator() : mutator(nullptr), energyAssigner(new EnergyAssigner<T>()) {}

    template <typename T>
    TestGenerator<T>::~TestGenerator()
    {
        if (mutator)
            delete mutator;
        if (energyAssigner)
            delete energyAssigner;
    }
    template <typename T>
    void TestGenerator<T>::setEnergyAssigner(EnergyAssigner<T> *e)
    {
        if (energyAssigner)
            delete energyAssigner;
        energyAssigner = e;
    }

    template <typename T>
    void TestGenerator<T>::setMutator(Mutator<T> *m)
    {
        if (mutator)
            delete mutator;
        mutator = m;
    }

    template <typename T>
    bool TestGenerator<T>::isValid(T) { return true; }

    template <typename T>
    T TestGenerator<T>::deepCopy(T t) { return t; }

    template <typename T>
    bool TestGenerator<T>::ends_with(const string &value, const string &ending)
    {
        if (ending.size() > value.size())
        {
            return false;
        }
        return equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    template <typename T>
    vector<T> TestGenerator<T>::generateTest(T base)
    {
        vector<T> result;
        if (!mutator)
            return result;
        auto mutations = mutator->getMutations(base);
        for (auto &mutation : mutations)
        {
            try
            {
                T mutated = mutation(deepCopy(base));
                result.push_back(mutated);
            }
            catch (...)
            {
                // If mutation fails, skip this mutation
            }
        }
        return result;
    }

    template <typename T>
    set<T> &TestGenerator<T>::generateTests(set<unsigned int> &)
    {
        cout << "Generating tests using guided mutation ..." << endl;
        testcases.clear();

        last_accepted_lines.clear();
        cumulative_covered_lines.clear();

        // Priority queue for testcases, highest energy first
        struct PQEntry
        {
            int energy;
            T testcase;
            // For max-heap
            bool operator<(const PQEntry &other) const { return energy < other.energy; }
        };

        T seed = generateRandomTest();
        std::priority_queue<PQEntry> pq;
        // Assign energy=1 for the initial seed
        pq.push(PQEntry{1, seed});

        const float epsilon = 1e-6f;

        while (!pq.empty() && toContinue())
        {
            PQEntry entry = pq.top();
            pq.pop();
            T t = entry.testcase;
            if (!isValid(t))
            {
                deleteTest(t);
                continue;
            }

            bool error_in_put = false;
            float new_coverage = 0.0f;
            try
            {
                callPUT(t);
                new_coverage = static_cast<float>(getIndividualCoverage());
            }
            catch (const exception &e)
            {
                cerr << "Error in callPUT: " << e.what() << endl;
                error_in_put = true;
            }
            catch (...)
            {
                cerr << "Unknown error in callPUT." << endl;
                error_in_put = true;
            }

            // Only keep if new coverage is found (or queue would be empty)
            if (new_coverage > epsilon || pq.empty())
            {
                testcases.insert(t);
                // Assign energy based on new_coverage
                int energy = energyAssigner ? energyAssigner->assignEnergy(t, new_coverage) : 1;
                vector<T> mutated_cases = generateTest(t);
                for (T m : mutated_cases)
                {
                    if (isValid(m))
                    {
                        // Assign parent's energy (just calculated) to children
                        pq.push(PQEntry{energy, m});
                    }
                    else
                    {
                        deleteTest(m);
                    }
                }
            }
            else
            {
                deleteTest(t);
            }
        }
        getTotalCoverage();
        return testcases;
    }

    namespace fs = std::filesystem;
    template <typename T>
    vector<string> TestGenerator<T>::getFileList(string path)
    {
        vector<string> fileNames;
        for (const auto &entry : fs::directory_iterator(path))
        {
            string fileName = entry.path();
            if (ends_with(fileName, ".json"))
            {
                fileNames.push_back(fileName);
            }
        }
        return fileNames;
    }

    template <typename T>
    void TestGenerator<T>::writeToFile(string s, string fname)
    {
        ofstream fout(fname);
        fout << s;
        fout.close();
    }

    template <typename T>
    void TestGenerator<T>::deleteDirectoryContents(const filesystem::path &dir)
    {
        for (const auto &entry : filesystem::directory_iterator(dir))
            filesystem::remove_all(entry.path());
    }

    template <typename T>
    void TestGenerator<T>::writeAllTestsToFile()
    {
        string dirName = "test/testcases/";
        filesystem::create_directories(dirName);
        deleteDirectoryContents(dirName);
        unsigned int i = 1;
        for (const auto &t : testcases)
        {
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
