#include "user_function.h"
#include <iostream>
using namespace std;

void user_function(Graph* g) {
    
    cout << "User Function: Testing full coverage." << endl;

    //a simple operation that will always execute (covers line 2)
    int total_nodes = g->n;
    cout << "Total nodes in the graph: " << total_nodes << endl;

    //always executes (covers line 3+)
    for (int i = 0; i < min(total_nodes, 1); i++) {
        cout << "Iterating through node " << i << endl;
    }

    // all branches are trivial 
    if (true) {
        cout << "Always true branch executed." << endl;
    } else {
        cout << "This branch will never execute." << endl;
    }
}

