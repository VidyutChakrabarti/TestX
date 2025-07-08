#include "bstmutator.h"
#include "valuegenerators.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

BSTMutator::BSTMutator()
{
    addMutation(insertNode);
    addMutation(removeNode);
    addMutation(swapNodes);
    addMutation(duplicateNode);
}

const vector<function<BST *(BST *)>> &BSTMutator::getMutations(BST *const &bst) const
{
    return mutations;
}

BST *BSTMutator::insertNode(BST *bst)
{
    testgenerator::IntGenerator ig;
    testgenerator::StringGenerator sg;
    cout << "Inserting a node..." << endl;
    string data = sg.generate();
    int value = ig.generate() % 100;
    bst->insert(data, value);
    return bst;
}

BST *BSTMutator::removeNode(BST *bst)
{
    testgenerator::IntGenerator ig;
    cout << "Removing a node..." << endl;
    if (bst->nodes.empty())
        return bst;
    int idx = ig.generate() % bst->nodes.size();
    int value = bst->nodes[idx]->value;
    bst->remove(value);
    return bst;
}

BST *BSTMutator::swapNodes(BST *bst)
{
    testgenerator::IntGenerator ig;
    if (bst->nodes.size() < 2)
        return bst;
    cout << "Swapping nodes..." << endl;
    int i = ig.generate() % bst->nodes.size();
    int j = ig.generate() % bst->nodes.size();
    while (i == j)
        j = ig.generate() % bst->nodes.size();
    swap(bst->nodes[i]->data, bst->nodes[j]->data);
    swap(bst->nodes[i]->value, bst->nodes[j]->value);
    return bst;
}

BST *BSTMutator::duplicateNode(BST *bst)
{
    testgenerator::IntGenerator ig;
    if (bst->nodes.size() >= 15)
        return bst;
    cout << "Duplicating node..." << endl;
    int idx = ig.generate() % bst->nodes.size();
    string data = bst->nodes[idx]->data + "_dup";
    int value = ig.generate() % 100;
    bst->insert(data, value);
    return bst;
}
