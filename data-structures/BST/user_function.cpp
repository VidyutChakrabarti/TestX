#include "bst.h"
extern "C"
{

    BST *create_bst() { return new BST(); }
    void destroy_bst(BST *bst) { delete bst; }
    void bst_insert(BST *bst, int value) { bst->insert(value); }
    bool bst_search(BST *bst, int value) { return bst->search(value); }
    void bst_remove(BST *bst, int value) { bst->remove(value); }
}
