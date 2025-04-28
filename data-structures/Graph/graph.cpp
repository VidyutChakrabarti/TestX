#include "graph.h"
#include <iostream>
#include <stack>
#include <limits>

using namespace std;

Graphnode::Graphnode(string data) {
    this->data = data;
}

Graph::Graph() : n(0) {
}

Graph::~Graph() {
    for (auto node : nodes) {
        delete node;
    }
}

set<int> Graph::dfs(const vector<vector<int>> &matrix, int start_node) {
    set<int> visited;
    set<int> component;
    stack<int> s;
    s.push(start_node);
    while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (visited.find(node) == visited.end()) {
            visited.insert(node);
            component.insert(node);
            for (size_t i = 0; i < matrix[node].size(); ++i) {
                if (matrix[node][i] && visited.find(i) == visited.end()) {
                    s.push(i);
                }
            }
        }
    }
    return component;
}

vector<set<int>> Graph::connected_components(const vector<vector<int>> &matrix) {
    set<int> visited;
    vector<set<int>> components;
    for (int node = 0; node < matrix.size(); ++node) {
        if (visited.find(node) == visited.end()) {
            set<int> comp = dfs(matrix, node);
            components.push_back(comp);
            visited.insert(comp.begin(), comp.end());
        }
    }
    return components;
}

void Graph::print_graph() {
    cout << "Graph (adjacency values):" << endl;
    for (auto &row : graph) {
        for (auto val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "Weights:" << endl;
    for (auto &row : weights) {
        for (auto w : row) {
            if (w == numeric_limits<float>::infinity())
                cout << "INF ";
            else
                cout << w << " ";
        }
        cout << endl;
    }
}

void Graph::print_connectedComponents() {
    vector<set<int>> comps = connected_components(graph);
    cout << "Connected components:" << endl;
    for (auto &comp : comps) {
        cout << "{ ";
        for (auto node : comp)
            cout << node << " ";
        cout << "}" << endl;
    }
}

void Graph::print_all_nodes() {
    cout << "Nodes:" << endl;
    for (auto node : nodes) {
        cout << node->data << " ";
    }
    cout << endl;
}

