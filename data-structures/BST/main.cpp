#include "bst.h"
#include <iostream>

int main()
{
    BST bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    std::cout << "Inorder traversal: ";
    for (int v : bst.inorder())
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "Search 4: " << (bst.search(4) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 10: " << (bst.search(10) ? "Found" : "Not found") << std::endl;

    bst.remove(7);
    std::cout << "Inorder after removing 7: ";
    for (int v : bst.inorder())
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}
