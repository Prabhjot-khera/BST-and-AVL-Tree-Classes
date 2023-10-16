#include "avl-tree.h"
#include<iostream>
#include<string>
#include <algorithm>    // std::max
#include <stack>
using namespace std;

int AVLTree::Height(Node *T) {
    if(T == nullptr) return -1;
    else if (T->left == nullptr && T->right == nullptr) return 0;
    else {
        return 1 + ::max(Height(T->left), Height(T->right) );
    }
}

int AVLTree::getBalance(Node *N) {
    if (N ==NULL) return 0;
    return Height(N->left)- Height(N->right);
}
void AVLTree::SingleRightRotation(Node **pT, Node *alpha) {
    Node *A = alpha->left;

    //alphas left = A's right
    alpha->left = A->right;

    //A's right = alpha
    A->right = alpha;

    //If alpha was the root of the whole tree, make A to be the new root.
    if (*pT == alpha) {
        *pT = A;
    }
    else {
        //Let alpha's parent take A as the new child.

        //find 	alphas parent
        Node *temp = *pT;
        Node **parentPointerToAlpha = NULL;
        do{
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);

        *parentPointerToAlpha = A;
    }
}

void AVLTree::SingleLeftRotation(Node **pT,Node *alpha) {
//Input is alpha
    //A is alpha's right
    Node *A = alpha->right;

    //alphas right = A's left
    alpha->right = A->left;

    //A's left = alpha
    A->left = alpha;


    //If alpha was the root of the whole tree, make A to be the new root.
    if (*pT == alpha) {
        *pT = A;
    }
    else {
        //Let alpha's parent take A as the new child.

        //find 	alphas parent
        Node *temp = *pT;
        Node **parentPointerToAlpha = NULL;
        do{
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);

        *parentPointerToAlpha = A;
    }
}

void AVLTree::RightLeftRotation(Node **pT,Node *alpha) {
    //Input is alpha

    //A is alpha's right
    Node *A = alpha->right;

    //B is A's left


    //Call single right rotation with input (A)
    SingleRightRotation(pT, A);

    //Call single left rotation with input (alpha)
    SingleLeftRotation(pT, alpha);
}

void AVLTree::LeftRightRotation(Node **pT,Node *alpha) {
//Input is alpha

    //A is alpha's left
    Node *A = alpha->left;

    //B is A's right


    //Call single left rotation with input (A)
    SingleLeftRotation(pT, A);

    //Call single right rotation with input (alpha)
    SingleRightRotation(pT, alpha);
}

void AVLTree::rebalance(Node **pT, Node *alpha, DataType val) {
    if     ( val < alpha->val && val < alpha->left->val  ) SingleRightRotation (pT, alpha);
    else if (val > alpha->val && val > alpha->right->val ) SingleLeftRotation(pT, alpha);
    else if ( val < alpha->val && val > alpha->left->val ) LeftRightRotation(pT, alpha);
    else if (val > alpha->val && val < alpha->right->val ) RightLeftRotation(pT, alpha);
}

bool AVLTree::insert(DataType val) {
    bool result = BinarySearchTree::insert(val);

    if(result == false) return false;

    Node **pT = getRootNodeAddress();
    Node *root;
    root = *pT;

    //special case, if N is inserted at the root node, nothing unbalanced, just return.
    if(root->val == val) return true;

    Node *temp;
    temp = root;
    Node *temp_parent;
    Node *alpha = NULL;

    do{
        temp_parent = temp;
        if(val > temp->val) temp = temp->right;
        else if (val < temp->val) temp =  temp->left;
        //now, check if temp_parent is unbalanced.
        int leftHeight = Height(temp_parent->left);
        int rightHeight = Height(temp_parent->right);
        if( abs(leftHeight - rightHeight) >= 2 ) alpha = temp_parent;

    } while ( temp->val != val  );

    if(!alpha) return true;

    //Then re-balance the AVL tree using one of the four rotations, depending on the cases.
    rebalance(pT, alpha, val);

    return true;

}

bool AVLTree::remove(DataType val) {



    bool result = BinarySearchTree::remove(val);

    if(result == false) return false;

    Node **pT = getRootNodeAddress();
    Node *root;
    root= *pT;





    if(root == nullptr) return true;

    int balance = getBalance(root);
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        SingleRightRotation(pT, root);


    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        LeftRightRotation(pT,root);
    }


    if (balance < -1 &&
        getBalance(root->right) <= 0)
        SingleLeftRotation(pT,root);


    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        RightLeftRotation(pT, root);
    }

    return true;




}

