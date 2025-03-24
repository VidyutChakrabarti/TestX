#include <iostream>

#include <set>

#include "graphtg.h"

using namespace std;

int main()
{

    srand(time(NULL));

    Graphtg_userfunction testGenerator;

    // The dummy targets set is not used now.

    set<unsigned int> dummyTargets;

    set<Graph *> &tests = testGenerator.generateTests(dummyTargets);

    testGenerator.writeAllTestsToFile();

    cout << "# tests generated = " << tests.size() << endl;

    return 0;
}
