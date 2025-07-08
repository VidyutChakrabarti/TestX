#include "bst.h"
#include <iostream>

// Instrumented BST for coverage or logging (example: print on insert/search/remove)
class InstrumentedBST : public BST
{
public:
    void insert(int value)
    {
        std::cout << "insert(" << value << ")\n";
        BST::insert(value);
    }
    bool search(int value) const
    {
        std::cout << "search(" << value << ")\n";
        return BST::search(value);
    }
    void remove(int value)
    {
        std::cout << "remove(" << value << ")\n";
        BST::remove(value);
    }
};

// Optionally, expose InstrumentedBST for testgen
extern "C"
{
    InstrumentedBST *create_bst() { return new InstrumentedBST(); }
    void destroy_bst(InstrumentedBST *bst) { delete bst; }
    void bst_insert(InstrumentedBST *bst, int value) { bst->insert(value); }
    bool bst_search(InstrumentedBST *bst, int value) { return bst->search(value); }
    void bst_remove(InstrumentedBST *bst, int value) { bst->remove(value); }
}
