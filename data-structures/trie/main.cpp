#include <iostream>
#include <set>
#include "trietg.h"

using namespace std;
using namespace testgenerator;
int main() {
    srand(time(NULL));
    Trietg_search_key testGenerator;
    set<unsigned int> targets({1u, 2u, 3u});
    set<Trie *>& tests = testGenerator.generateTests(targets);
    testGenerator.writeAllTestsToFile();
    cout << "#tests = " << tests.size() << endl;
    return 0;
}
