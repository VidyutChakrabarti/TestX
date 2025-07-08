
#ifndef BST_H
#define BST_H

#include <vector>
#include <string>
#include <set>
using namespace std;

class BSTNode
{
public:
    string data;
    int value;
    BSTNode *left;
    BSTNode *right;
    BSTNode(string data, int value);
};

class BST
{
public:
    int n;
    vector<BSTNode *> nodes;
    BST();
    ~BST();

    set<int> dfs(BSTNode *node);
    vector<set<int>> connected_components();
    void print_bst();
    void print_connectedComponents();
    void print_all_nodes();

    void insert(string data, int value);
    bool search(int value) const;
    void remove(int value);
    vector<int> inorder() const;

private:
    BSTNode *root;
    void destroy(BSTNode *node);
    BSTNode *insert(BSTNode *node, string data, int value);
    BSTNode *remove(BSTNode *node, int value);
    bool search(BSTNode *node, int value) const;
    void inorder(BSTNode *node, vector<int> &result) const;
    void collect_nodes(BSTNode *node);
};

#endif
