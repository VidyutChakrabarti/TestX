#ifndef USER_FUNCTION_H
#define USER_FUNCTION_H

#include "bst.h"
#ifdef __cplusplus
extern "C"
{
#endif

    BST *create_bst();
    void destroy_bst(BST *bst);
    void bst_insert(BST *bst, int value);
    bool bst_search(BST *bst, int value);
    void bst_remove(BST *bst, int value);

#ifdef __cplusplus
}
#endif

#endif // USER_FUNCTION_H
