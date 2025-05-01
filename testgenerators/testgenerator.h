#ifndef TESTGENERATOR_H
#define TESTGENERATOR_H

#include <filesystem>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

namespace testgenerator {

template <typename T> class TestGenerator {
protected:
    set<T> testcases;
    // Pure virtual: each derived class must specify what function to call.
    virtual void callPUT(T) = 0;
public:
    TestGenerator();
    virtual ~TestGenerator() = 0;
    virtual set<T>& generateTests(set<unsigned int>&);
    virtual T generateTest() = 0; // Generate a single test case.
    virtual void deleteTest(T) = 0;
    virtual bool isValid(T); // Returns true if test case is valid.
    virtual bool toContinue() = 0; // Decide whether to continue generating tests.

    bool ends_with(const string& value, const string& ending);
    vector<string> getFileList(string);

    virtual string toString(T) = 0;
    virtual string toJSON(T) = 0;
    virtual T readFromJSONFile(string) = 0;
    virtual void writeToFile(string, string);
    virtual void deleteDirectoryContents(const std::filesystem::path&);
    virtual void writeAllTestsToFile();
};

} // namespace testgenerator

#include "testgenerator.cpp"
#endif

