#include <iostream>
#include <stdlib.h>
#include "coveragelogger.h"

using namespace std;

CoverageLogger * CoverageLogger::logger = NULL;

CoverageLogger::CoverageLogger() {}

CoverageLogger *CoverageLogger::getInstance() {
    if(logger == nullptr) {
        CoverageLogger::logger = new CoverageLogger();
    }
    return CoverageLogger::logger;
}

void CoverageLogger::log(unsigned int loc) {
    coverage.insert(loc);
}

set<unsigned int>& CoverageLogger::getCoverage() {
    return coverage;
}

set<unsigned int>& CoverageLogger::getTargets() {
    return targets;
}

void CoverageLogger::reset() {
    coverage.clear();
    targets.clear();
}

void CoverageLogger::reset(set<unsigned int>& t) {
    reset();
    targets = t;
}
