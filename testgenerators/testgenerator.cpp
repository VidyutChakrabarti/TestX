#ifndef TESTGENERATOR_CPP

#define TESTGENERATOR_CPP

#include <filesystem>

#include <iostream>

#include <set>

#include <vector>

#include <fstream>

#include "testgenerator.h"

using namespace std;

namespace testgenerator
{

    template <typename T>

    TestGenerator<T>::TestGenerator()
    {
    }

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

    TestGenerator<T>::~TestGenerator()
    {
    }

    template <typename T>

    set<T> &TestGenerator<T>::generateTests(set<unsigned int> &dummyTargets)
    {

        // In this revised version, we ignore dummyTargets and rely on gcov.

        cout << "Generating tests using user-defined function ..." << endl;

        testcases.clear();

        while (toContinue())
        {

            T t = generateTest();

            while (!isValid(t))
            {

                deleteTest(t);

                t = generateTest();
            }

            callPUT(t);

            testcases.insert(t);
        }

        return testcases;
    }

    template <typename T>

    bool TestGenerator<T>::isValid(T val)
    {

        return true;
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

    void TestGenerator<T>::deleteDirectoryContents(const fs::path &dir)
    {

        for (const auto &entry : fs::directory_iterator(dir))

            fs::remove_all(entry.path());
    }

    template <typename T>

    void TestGenerator<T>::writeAllTestsToFile()
    {

        string dirName = "test/testcases/";

        fs::create_directories(dirName);

        TestGenerator<T>::deleteDirectoryContents(dirName);

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
