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
    virtual void callPUT(Graph *) override;
    virtual float getCoverage() override;
public:
    static const unsigned int MAXTESTCOUNT;
    unsigned int count = 0;
    Graphtg();
    virtual ~Graphtg();
    virtual Graph *generateRandomTest() override;
    virtual vector<Graph*> generateTest(Graph* base) override;
    virtual void deleteTest(Graph *);
    virtual bool toContinue() override;
    virtual string toString(Graph *);
    virtual string toJSON(Graph *);
    virtual Graph *readFromJSONFile(string);
    virtual void writeToFile(string s, string fname);
    virtual void deleteDirectoryContents(const std::filesystem::path &dir);
    virtual void writeAllTestsToFile();
    virtual Graph* deepCopy(Graph* g) override;
};

#endif
