#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include "lltg.h"

using namespace std;
using namespace testgenerator;

int main()
{
    srand(time(NULL));
    Lltg testGenerator;
    set<unsigned int> dummyTargets; // Not used, but required by interface
    set<LinkedList *> &tests = testGenerator.generateTests(dummyTargets);
    testGenerator.writeAllTestsToFile();
    cout << "#tests = " << tests.size() << endl;
    return 0;
}
