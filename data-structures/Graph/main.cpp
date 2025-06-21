#include <iostream>
#include <set>
#include "graphtg.h"

using namespace std;
using namespace testgenerator;

int main() {
    srand(time(NULL));
    Graphtg testGenerator;
    set<unsigned int> dummyTargets; // Not used, but required by interface
    set<Graph*>& tests = testGenerator.generateTests(dummyTargets);
    testGenerator.writeAllTestsToFile();
    cout << "#tests = " << tests.size() << endl;
    return 0;
}
