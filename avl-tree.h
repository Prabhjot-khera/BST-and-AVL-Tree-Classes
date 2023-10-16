#ifndef LAB3_AVL_TREE_H
#define LAB3_AVL_TREE_H

#include "binary-search-tree.h"

class AVLTree : public BinarySearchTree {
public:
    // Overriden insert and remove functions
    // Do not modify these definitions

    // The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);

    // Define additional functions and attributes below if you need
    void SingleRightRotation(Node **pT,Node *alpha);
    void SingleLeftRotation(Node **pT,Node *alpha);
    void LeftRightRotation(Node **pT,Node *alpha);
    void RightLeftRotation(Node **pT,Node *alpha);
    void rebalance(Node **pT,Node *alpha, DataType val);
    int getBalance(Node *N);
    int Height(Node *T);
};

#endif  // LAB3_AVL_TREE_H
