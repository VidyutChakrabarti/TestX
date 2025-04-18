#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <string>
#include <stack>
#include <set>

#include "graph.h"
#include "coveragelogger.h"

using namespace std;

Graphnode::Graphnode(string data)
{
    this->data = data;
}

//Graphnode::~Graphnode()
//{
//  delete this;
//}

Graph::Graph()
{
    int n; // no. of nodes
    vector<vector<int>> graph;
    vector<Graphnode *> nodes;
    vector<vector<float>> weights;
}

Graph::~Graph()
{
    for (Graphnode *node : nodes)
    {
        delete node;
    }
  
}

// function to traverse (depth first search) the graph.
set<int> Graph::dfs(const vector<vector<int>> &matrix, int start_node)
{
    set<int> visited;
    set<int> component;

    stack<int> stack;
    stack.push(start_node);

    while (!stack.empty())
    {
        int node = stack.top();
        stack.pop();
        if (visited.find(node) == visited.end())
        {
            visited.insert(node);
            component.insert(node);
            // Add unvisited adjacent nodes to the stack
            for (int i = 0; i < matrix[node].size(); ++i)
            {
                if (matrix[node][i] && visited.find(i) == visited.end())
                {
                    stack.push(i);
                }
            }
        }
    }
    return component;
}

// function to find the connected node sets after intermediate random generation of graph
vector<set<int>> Graph::connected_components(const vector<vector<int>> &matrix)
{
    set<int> visited;
    vector<set<int>> components;

    for (int node = 0; node < matrix.size(); ++node)
    {
        if (visited.find(node) == visited.end())
        {
            // Get connected component using DFS
            set<int> component = dfs(matrix, node);
            components.push_back(component);
            // Mark all nodes in the component as visited
            visited.insert(component.begin(), component.end());
        }
    }

    return components;
}

void Graph::print_graph()
{
    cout << "Graph:" << endl;
    for (const auto &row : weights)
    {
        for (float val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

void Graph::print_connectedComponents()
{
    auto connected_sets = connected_components(graph);

    cout << "Connected Sets:" << endl;
    for (const auto &component : connected_sets)
    {
        cout << "{ ";
        for (int node : component)
        {
            cout << node << " ";
        }
        cout << "}" << endl;
    }
}

void Graph::print_all_nodes()
{
    cout << "Node Data:" << endl;
    for (Graphnode *node : nodes)
    {
        cout << node->data << " ";
    }
    cout << endl;
}

void sum_of_all_edges(Graph &g)
{
    CoverageLogger::getInstance()->log(1u);
    vector<vector<float>> weights = g.weights;
    int V = weights.size(); // Number of vertices in the graph
    const float INF = numeric_limits<float>::infinity();
    float total_weight_sum = 0.0;

    for (int i = 0; i < V; ++i)
    {
        CoverageLogger::getInstance()->log(2u);
        for (int j = i + 1; j < V; ++j)
        {
            CoverageLogger::getInstance()->log(3u);
            if (weights[i][j] != INF)
            {
                CoverageLogger::getInstance()->log(4u);
                total_weight_sum += weights[i][j];
            }
        }
    }
    cout << "Total Weight: " << total_weight_sum << "/n";
}
