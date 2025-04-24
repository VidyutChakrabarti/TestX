#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <set>
using namespace std;

class Graphnode {
public:
    std::string data;
    Graphnode(std::string data);
};

class Graph {
public:
    int n;
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<float>> weights;
    std::vector<Graphnode*> nodes;
    Graph();
    ~Graph();

    std::set<int> dfs(const std::vector<std::vector<int>> &matrix, int start_node);
    std::vector<std::set<int>> connected_components(const std::vector<std::vector<int>> &matrix);
    void print_graph();
    void print_connectedComponents();
    void print_all_nodes();
};

#endif

