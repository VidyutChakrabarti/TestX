#include <iostream>
#include <vector>
#include "testgenerator.h"
#include "graphtg.h"
#include "user_function.h"

using namespace std;
using namespace testgenerator;
extern "C" void __gcov_dump(void);

int main() {
    Graphtg testGenerator;
    vector<string> fileNames = testGenerator.getFileList("testcases");
    for (auto &fileName : fileNames) {
        cout << "Running test from file: " << fileName << endl;
        Graph *g = testGenerator.readFromJSONFile(fileName);
        cout << "Graph details:" << endl;
        g->print_graph();
        cout << "Invoking user function on test case:" << endl;
        user_function(g);
        __gcov_dump(); 
    }
    cout << "Tests complete. Run 'gcov -b user_function.cpp' to see the coverage report." << endl;
    return 0;
}

