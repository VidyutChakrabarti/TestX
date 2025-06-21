#ifndef GRAPH_MUTATOR_H
#define GRAPH_MUTATOR_H

#include "mutator.h"
#include "graph.h"
#include <functional>
#include <vector>

using namespace std;

class GraphMutator : public Mutator<Graph*> {
public:
    GraphMutator();
    virtual const vector<function<Graph*(Graph*)>>& getMutations(Graph* const& g) const override;

private:
    static Graph* addEdge(Graph* g);
    static Graph* removeEdge(Graph* g);
    static Graph* swapNodes(Graph* g);
    static Graph* duplicateNode(Graph* g);
};

#endif
