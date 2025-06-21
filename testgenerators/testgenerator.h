#ifndef TESTGENERATOR_H
#define TESTGENERATOR_H

#include <set>
#include <vector>
#include <string>
#include <queue>
#include <filesystem>
#include <functional>
#include <iostream>
#include "mutator.h"

namespace testgenerator {

using namespace std;

template <typename T>
class TestGenerator {
protected:
    set<T> testcases;
    Mutator<T>* mutator = nullptr;

    virtual void callPUT(T) = 0;
    virtual float getCoverage() = 0;

public:
    TestGenerator();
    virtual ~TestGenerator();

    void setMutator(Mutator<T>* m);

    // Generate a random test case (for initial seed)
    virtual T generateRandomTest() = 0;

    // Generate all mutated test cases from a base
    virtual vector<T> generateTest(T base);

    // Main test generation loop
    virtual set<T>& generateTests(set<unsigned int>&);

    virtual void deleteTest(T) = 0;
    virtual bool isValid(T);
    virtual bool toContinue() = 0;

    virtual string toString(T) = 0;
    virtual string toJSON(T) = 0;
    virtual T readFromJSONFile(string) = 0;
    bool ends_with(const string& value, const string& ending);
    vector<string> getFileList(string);
    virtual void writeToFile(string, string);
    virtual void deleteDirectoryContents(const std::filesystem::path&);
    virtual void writeAllTestsToFile();

    virtual T deepCopy(T t);
};

} // namespace testgenerator

#include "testgenerator.cpp"
#endif
