#include "graphmutator.h"
#include "valuegenerators.h"
#include <limits>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

GraphMutator::GraphMutator() {
    addMutation(addEdge);
    addMutation(removeEdge);
    addMutation(swapNodes);
    addMutation(duplicateNode);
}

const vector<function<Graph*(Graph*)>>& GraphMutator::getMutations(Graph* const& g) const {
    return mutations;
}

Graph* GraphMutator::addEdge(Graph* g) {
    testgenerator::IntGenerator ig;
    if (g->n < 2) return g;
    cout << "Adding an edge..." << endl;
    vector<pair<int, int>> possible_edges;
    for (int i = 0; i < g->n; ++i)
        for (int j = i + 1; j < g->n; ++j)
            if (g->graph[i][j] == 0)
                possible_edges.push_back({i, j});
    if (possible_edges.empty()) return g;
    auto edge = possible_edges[ig.generate() % possible_edges.size()];
    int i = edge.first, j = edge.second;
    g->graph[i][j] = g->graph[j][i] = 1;
    float weight = static_cast<float>((ig.generate() % 100) + 1);
    g->weights[i][j] = g->weights[j][i] = weight;
    return g;
}

Graph* GraphMutator::removeEdge(Graph* g) {
    testgenerator::IntGenerator ig;
    vector<pair<int, int>> existing_edges;
    cout << "Removing an edge..." << endl;
    for (int i = 0; i < g->n; ++i)
        for (int j = i + 1; j < g->n; ++j)
            if (g->graph[i][j] == 1)
                existing_edges.push_back({i, j});
    if (existing_edges.empty()) return g;
    auto edge = existing_edges[ig.generate() % existing_edges.size()];
    int i = edge.first, j = edge.second;
    g->graph[i][j] = g->graph[j][i] = 0;
    g->weights[i][j] = g->weights[j][i] = numeric_limits<float>::infinity();
    return g;
}

Graph* GraphMutator::swapNodes(Graph* g) {
    testgenerator::IntGenerator ig;
    if (g->n < 2) return g;
    cout << "Swapping nodes....." << endl;
    int i = ig.generate() % g->n;
    int j = ig.generate() % g->n;
    while (i == j) j = ig.generate() % g->n;
    swap(g->nodes[i], g->nodes[j]);
    for (int k = 0; k < g->n; ++k) {
        swap(g->graph[i][k], g->graph[j][k]);
        swap(g->graph[k][i], g->graph[k][j]);
        swap(g->weights[i][k], g->weights[j][k]);
        swap(g->weights[k][i], g->weights[j][i]);
    }
    return g;
}

Graph* GraphMutator::duplicateNode(Graph* g) {
    testgenerator::IntGenerator ig;
    if (g->n >= 15) return g;
    cout << "Duplicating node...." << endl;
    int idx = ig.generate() % g->n;
    g->nodes.push_back(new Graphnode(g->nodes[idx]->data + "_dup"));
    g->n += 1;
    for (int i = 0; i < g->n - 1; ++i) {
        g->graph[i].push_back(0);
        g->weights[i].push_back(numeric_limits<float>::infinity());
    }
    g->graph.push_back(vector<int>(g->n, 0));
    g->weights.push_back(vector<float>(g->n, numeric_limits<float>::infinity()));
    for (int i = 0; i < g->n - 1; ++i) {
        if (g->graph[idx][i] == 1 && (ig.generate() % 2 == 0)) {
            g->graph[g->n - 1][i] = g->graph[i][g->n - 1] = 1;
            g->weights[g->n - 1][i] = g->weights[i][g->n - 1] = g->weights[idx][i];
        }
    }
    return g;
}
