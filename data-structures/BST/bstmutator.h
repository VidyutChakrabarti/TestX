#ifndef BST_MUTATOR_H
#define BST_MUTATOR_H

#include "mutator.h"
#include "bst.h"
#include <functional>
#include <vector>

using namespace std;

class BSTMutator : public Mutator<BST *>
{
public:
    BSTMutator();
    virtual const vector<function<BST *(BST *)>> &getMutations(BST *const &bst) const override;

private:
    static BST *insertNode(BST *bst);
    static BST *removeNode(BST *bst);
    static BST *swapNodes(BST *bst);
    static BST *duplicateNode(BST *bst);
};

#endif
