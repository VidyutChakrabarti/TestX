#ifndef COVERAGELOGGER_H
#define COVERAGELOGGER_H
#include<set>

using namespace std;
class CoverageLogger {
private:
    set<unsigned int> coverage;
    set<unsigned int> targets;
    static CoverageLogger *logger;
    CoverageLogger();

public:
    static CoverageLogger *getInstance();
    void log(unsigned int loc);
    set<unsigned int>& getCoverage();
    set<unsigned int>& getTargets();
    void reset();
    void reset(set<unsigned int>&);
};
#endif
