#include "../bst.h"
#include <cassert>
#include <iostream>

void test_insert_search()
{
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    assert(bst.search(10));
    assert(bst.search(5));
    assert(bst.search(15));
    assert(!bst.search(20));
}

void test_remove()
{
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.remove(10);
    assert(!bst.search(10));
    assert(bst.search(5));
    assert(bst.search(15));
}

void test_inorder()
{
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    auto v = bst.inorder();
    assert(v.size() == 3);
    assert(v[0] == 5 && v[1] == 10 && v[2] == 15);
}

int main()
{
    test_insert_search();
    test_remove();
    test_inorder();
    std::cout << "All BST tests passed!\n";
    return 0;
}
