
#include "bsttg.h"
#include "user_function.h"
#include "valuegenerators.h"
#include "bstmutator.h"
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <exception>

using namespace std;
using namespace testgenerator;

class BSTtg : public TestGenerator<BST *>
{
public:
    static const unsigned int MAXTESTCOUNT = 20;
    unsigned int count = 0;
    BSTtg() { setMutator(new BSTMutator()); }
    virtual ~BSTtg()
    {
        for (auto &t : testcases)
            delete t;
    }
    virtual BST *generateRandomTest() override
    {
        BST *bst = new BST();
        IntGenerator ig;
        StringGenerator sg;
        int num = (ig.generate() % 10) + 2;
        for (int i = 0; i < num; ++i)
        {
            string data = sg.generate();
            int value = ig.generate() % 100;
            bst->insert(data, value);
        }
        return bst;
    }
    virtual vector<BST *> generateTest(BST *base) override
    {
        vector<BST *> result;
        if (!mutator)
            return result;
        auto mutations = mutator->getMutations(base);
        for (auto &mutation : mutations)
        {
            try
            {
                BST *mutated = mutation(deepCopy(base));
                result.push_back(mutated);
            }
            catch (...)
            {
            }
        }
        return result;
    }
    virtual void deleteTest(BST *bst) { delete bst; }
    virtual bool toContinue() override
    {
        if (count >= MAXTESTCOUNT)
            return false;
        count++;
        return true;
    }
    virtual string toString(BST *bst)
    {
        stringstream ss;
        ss << "BST inorder: ";
        for (int v : bst->inorder())
            ss << v << " ";
        return ss.str();
    }
    virtual string toJSON(BST *bst)
    {
        stringstream ss;
        ss << "{\"Nodes\":[";
        for (size_t i = 0; i < bst->nodes.size(); ++i)
        {
            ss << "{\"data\":\"" << bst->nodes[i]->data << "\",\"value\":" << bst->nodes[i]->value << "}";
            if (i != bst->nodes.size() - 1)
                ss << ",";
        }
        ss << "]}";
        return ss.str();
    }
    virtual BST *readFromJSONFile(string fileName)
    {
        ifstream test_file(fileName, ifstream::binary);
        Json::Value t1;
        test_file >> t1;
        BST *bst = new BST();
        for (const auto &node : t1["Nodes"])
        {
            string data = node["data"].asString();
            int value = node["value"].asInt();
            bst->insert(data, value);
        }
        return bst;
    }
    virtual void writeToFile(string s, string fname)
    {
        ofstream fout(fname);
        fout << s;
        fout.close();
    }
    virtual void deleteDirectoryContents(const std::filesystem::path &dir)
    {
        for (const auto &entry : std::filesystem::directory_iterator(dir))
            std::filesystem::remove_all(entry.path());
    }
    virtual void writeAllTestsToFile()
    {
        string dirName = "test/testcases/";
        std::filesystem::create_directories(dirName);
        BSTtg::deleteDirectoryContents(dirName);
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
    virtual BST *deepCopy(BST *bst) override
    {
        BST *copy = new BST();
        for (auto node : bst->nodes)
        {
            copy->insert(node->data, node->value);
        }
        return copy;
    }

protected:
    virtual void callPUT(BST *bst) override
    {
        try
        {
            user_function(bst);
        }
        catch (const std::exception &e)
        {
            cerr << "Exception in user_function: " << e.what() << endl;
            throw;
        }
        catch (...)
        {
            cerr << "Unknown exception in user_function." << endl;
            throw;
        }
    }
    virtual float getCoverage() override { return 0.0f; }
};

int main()
{
    BSTtg bsttg;
    BST *test = bsttg.generateRandomTest();
    cout << bsttg.toString(test) << endl;
    delete test;
    return 0;
}
