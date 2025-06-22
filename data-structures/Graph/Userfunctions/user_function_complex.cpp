#include "user_function.h"
#include <iostream>
#include <set>
#include <queue>
#include <limits>
using namespace std;

// Helper: Check if the graph is connected using BFS
bool is_connected(Graph* g) {
    if (g->n == 0) return true;
    vector<bool> visited(g->n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    int count = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < g->n; ++v) {
            if (g->graph[u][v] && !visited[v]) {
                visited[v] = true;
                q.push(v);
                count++;
            }
        }
    }
    return count == g->n;
}

// Helper: Find node with max degree
int max_degree_node(Graph* g) {
    int max_deg = -1, idx = -1;
    for (int i = 0; i < g->n; ++i) {
        int deg = 0;
        for (int j = 0; j < g->n; ++j)
            if (g->graph[i][j]) deg++;
        if (deg > max_deg) {
            max_deg = deg;
            idx = i;
        }
    }
    return idx;
}

// Helper: Find shortest path between two nodes using Dijkstra
float shortest_path(Graph* g, int src, int dest) {
    vector<float> dist(g->n, numeric_limits<float>::infinity());
    set<pair<float, int>> pq;
    dist[src] = 0;
    pq.insert({0, src});
    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        for (int v = 0; v < g->n; ++v) {
            if (g->graph[u][v] && dist[v] > dist[u] + g->weights[u][v]) {
                pq.erase({dist[v], v});
                dist[v] = dist[u] + g->weights[u][v];
                pq.insert({dist[v], v});
            }
        }
    }
    return dist[dest];
}

void user_function(Graph* g) {
    cout << "User Function: Complex graph analysis for mutation coverage." << endl;

    // 1. Print node data and check for duplicate node names
    set<string> node_names;
    bool has_duplicate = false;
    for (int i = 0; i < g->n; ++i) {
        cout << "Node " << i << ": " << g->nodes[i]->data << endl;
        if (!node_names.insert(g->nodes[i]->data).second) {
            has_duplicate = true;
        }
    }
    if (has_duplicate) {
        cout << "Duplicate node names found!" << endl;
    }

    // 2. Check if the graph is connected
    if (is_connected(g)) {
        cout << "Graph is connected." << endl;
    } else {
        cout << "Graph is NOT connected." << endl;
    }

    // 3. Find and print the node with the maximum degree
    int max_deg_idx = max_degree_node(g);
    if (max_deg_idx != -1) {
        cout << "Node with max degree: " << max_deg_idx << " (" << g->nodes[max_deg_idx]->data << ")" << endl;
    }

    // 4. For each node, print its neighbors and edge weights
    for (int i = 0; i < g->n; ++i) {
        cout << "Neighbors of node " << i << ": ";
        for (int j = 0; j < g->n; ++j) {
            if (g->graph[i][j]) {
                cout << j << "(w=" << g->weights[i][j] << ") ";
            }
        }
        cout << endl;
    }

    // 5. If there are at least 2 nodes, compute shortest path between first and last node
    if (g->n >= 2) {
        float sp = shortest_path(g, 0, g->n - 1);
        if (sp < numeric_limits<float>::infinity()) {
            cout << "Shortest path from node 0 to node " << g->n - 1 << " is " << sp << endl;
        } else {
            cout << "No path from node 0 to node " << g->n - 1 << endl;
        }
    }

    // 6. If there is an isolated node, print it
    for (int i = 0; i < g->n; ++i) {
        bool isolated = true;
        for (int j = 0; j < g->n; ++j) {
            if (g->graph[i][j]) {
                isolated = false;
                break;
            }
        }
        if (isolated) {
            cout << "Node " << i << " (" << g->nodes[i]->data << ") is isolated." << endl;
        }
    }

    // 7. If there are any self-loops, print them
    for (int i = 0; i < g->n; ++i) {
        if (g->graph[i][i]) {
            cout << "Node " << i << " (" << g->nodes[i]->data << ") has a self-loop." << endl;
        }
    }
}
