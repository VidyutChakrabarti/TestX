#include <iostream>
#include <set>
#include "lltg.h"

using namespace std;
using namespace testgenerator;
int main() {
    srand(time(NULL));
    Lltg_reverseLinkedList testGenerator;
    set<unsigned int> targets({1u, 2u, 3u});
    set<LinkedList *>& tests = testGenerator.generateTests(targets);
    testGenerator.writeAllTestsToFile();
    cout << "#tests = " << tests.size() << endl;
    return 0;
}
