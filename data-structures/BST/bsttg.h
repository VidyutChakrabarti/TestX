#ifndef BSTTG_H
#define BSTTG_H

#include "testgenerator.h"
#include "bst.h"
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
using namespace testgenerator;

class BSTtg : public TestGenerator<BST *>
{
public:
    static const unsigned int MAXTESTCOUNT;
    unsigned int count;
    BSTtg();
    virtual ~BSTtg();
    virtual BST *generateRandomTest() override;
    virtual vector<BST *> generateTest(BST *base) override;
    virtual void deleteTest(BST *bst);
    virtual bool toContinue() override;
    virtual string toString(BST *bst);
    virtual string toJSON(BST *bst);
    virtual BST *readFromJSONFile(string fileName);
    virtual void writeToFile(string s, string fname);
    virtual void deleteDirectoryContents(const std::filesystem::path &dir);
    virtual void writeAllTestsToFile();
    virtual BST *deepCopy(BST *bst) override;

protected:
    virtual void callPUT(BST *bst) override;
    virtual float getCoverage() override;
};

#endif
#ifndef BSTTG_H
#define BSTTG_H

// Placeholder for BST test generator header, if needed for testgen integration.

#endif // BSTTG_H
