#ifndef GTG
#define GTG

#include "testgenerator.h"
#include "graph.h"
#include <string>

using namespace std;
using namespace testgenerator;

class Graphtg : public TestGenerator<Graph *>
{
protected:
    // Pure virtual—each subclass must define how to “put” (i.e. execute) the test.
    virtual void callPUT(Graph *) = 0;
public:
    static const unsigned int MAXTESTCOUNT;
    unsigned int count = 0;
    virtual ~Graphtg();
    virtual Graph *generateTest();
    virtual void deleteTest(Graph *);
    // Modified to check gcov-based coverage.
    virtual bool toContinue();
    virtual string toString(Graph *);
    virtual string toJSON(Graph *);
    virtual Graph *readFromJSONFile(string);
    virtual void writeToFile(string s, string fname);
    virtual void deleteDirectoryContents(const std::filesystem::path &dir);
    virtual void writeAllTestsToFile();
};

class Graphtg_userfunction : public Graphtg
{
protected:
    void callPUT(Graph *);
};

#endif

