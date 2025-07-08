
#include "bst.h"
#include <iostream>
#include <stack>
#include <limits>
#include <queue>
#include <set>
using namespace std;

BSTNode::BSTNode(string data, int value) : data(data), value(value), left(nullptr), right(nullptr) {}

BST::BST() : root(nullptr), n(0) {}

BST::~BST()
{
    destroy(root);
}

void BST::destroy(BSTNode *node)
{
    if (node)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

void BST::collect_nodes(BSTNode *node)
{
    if (!node)
        return;
    nodes.push_back(node);
    collect_nodes(node->left);
    collect_nodes(node->right);
}

void BST::insert(string data, int value)
{
    root = insert(root, data, value);
    n = 0;
    nodes.clear();
    collect_nodes(root);
    n = nodes.size();
}

BSTNode *BST::insert(BSTNode *node, string data, int value)
{
    if (!node)
        return new BSTNode(data, value);
    if (value < node->value)
        node->left = insert(node->left, data, value);
    else if (value > node->value)
        node->right = insert(node->right, data, value);
    return node;
}

bool BST::search(int value) const
{
    return search(root, value);
}

bool BST::search(BSTNode *node, int value) const
{
    if (!node)
        return false;
    if (value == node->value)
        return true;
    if (value < node->value)
        return search(node->left, value);
    return search(node->right, value);
}

void BST::remove(int value)
{
    root = remove(root, value);
    n = 0;
    nodes.clear();
    collect_nodes(root);
    n = nodes.size();
}

BSTNode *BST::remove(BSTNode *node, int value)
{
    if (!node)
        return nullptr;
    if (value < node->value)
    {
        node->left = remove(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = remove(node->right, value);
    }
    else
    {
        if (!node->left)
        {
            BSTNode *right = node->right;
            delete node;
            return right;
        }
        else if (!node->right)
        {
            BSTNode *left = node->left;
            delete node;
            return left;
        }
        else
        {
            BSTNode *succ = node->right;
            while (succ->left)
                succ = succ->left;
            node->value = succ->value;
            node->data = succ->data;
            node->right = remove(node->right, succ->value);
        }
    }
    return node;
}

vector<int> BST::inorder() const
{
    vector<int> result;
    inorder(root, result);
    return result;
}

void BST::inorder(BSTNode *node, vector<int> &result) const
{
    if (!node)
        return;
    inorder(node->left, result);
    result.push_back(node->value);
    inorder(node->right, result);
}

set<int> BST::dfs(BSTNode *node)
{
    set<int> visited;
    stack<BSTNode *> s;
    if (node)
        s.push(node);
    while (!s.empty())
    {
        BSTNode *curr = s.top();
        s.pop();
        if (visited.find(curr->value) == visited.end())
        {
            visited.insert(curr->value);
            if (curr->right)
                s.push(curr->right);
            if (curr->left)
                s.push(curr->left);
        }
    }
    return visited;
}

vector<set<int>> BST::connected_components()
{
    vector<set<int>> comps;
    if (!root)
        return comps;
    set<int> comp = dfs(root);
    comps.push_back(comp);
    return comps;
}

void BST::print_bst()
{
    cout << "BST (inorder): ";
    for (int v : inorder())
    {
        cout << v << " ";
    }
    cout << endl;
}

void BST::print_connectedComponents()
{
    auto comps = connected_components();
    cout << "Connected components:" << endl;
    for (auto &comp : comps)
    {
        cout << "{ ";
        for (auto v : comp)
            cout << v << " ";
        cout << "}" << endl;
    }
}

void BST::print_all_nodes()
{
    nodes.clear();
    collect_nodes(root);
    cout << "Nodes:" << endl;
    for (auto node : nodes)
    {
        cout << node->data << "(" << node->value << ") ";
    }
    cout << endl;
}
