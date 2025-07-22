#ifndef LLTG
#define LLTG

#include "testgenerator.h"
#include "linkedlist.h"
#include <string>
#include <set>

using namespace std;
using namespace testgenerator;

class Lltg : public TestGenerator<LinkedList *>
{
protected:
    virtual void callPUT(LinkedList *) override;
    virtual float getCoverage() override;
    set<int> getCoveredLinesFromGcov();
    float getIndividualCoverage();
    float getTotalCoverage();

public:
    static const unsigned int MAXTESTCOUNT;
    unsigned int count = 0;
    Lltg();
    virtual ~Lltg();
    virtual LinkedList *generateRandomTest() override;
    virtual vector<LinkedList *> generateTest(LinkedList *base) override;
    virtual void deleteTest(LinkedList *);
    virtual bool toContinue() override;
    virtual string toString(LinkedList *);
    virtual string toJSON(LinkedList *);
    virtual LinkedList *readFromJSONFile(string);
    virtual void writeToFile(string s, string fname);
    virtual void deleteDirectoryContents(const std::filesystem::path &dir);
    virtual void writeAllTestsToFile();
    virtual LinkedList *deepCopy(LinkedList *ll) override;
};

#endif
