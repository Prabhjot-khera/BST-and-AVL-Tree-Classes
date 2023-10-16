#include "binary-search-tree.h"
#include <queue>
#include <iostream>
#include <stack>
using namespace std;
BinarySearchTree::Node::Node(DataType newval) {
val=newval;
left = nullptr;
right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const {

}

BinarySearchTree::BinarySearchTree() {
    root_= nullptr;
    size_=0;

}

BinarySearchTree::~BinarySearchTree() {
    std::queue<Node*> nodes;
    nodes.push(root_);
    while (!nodes.empty()) {
        Node* current = nodes.front();
        nodes.pop();
        if (current) {
            nodes.push(current->left);
            nodes.push(current->right);
            delete current;
        }
    }
}

unsigned int BinarySearchTree::size() const {
return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {


Node *current = root_;

while (current->right != nullptr)
{
    current=current->right;
}

return current->val;

}

BinarySearchTree::DataType BinarySearchTree::min() const {

    Node *current = root_;

    while (current->left != nullptr)
    {
        current=current->left;
    }

    return current->val;
}

unsigned int BinarySearchTree::depth() const {
if (root_->left == nullptr && root_->right== nullptr)
    return 0;

//having trouble with recursion so I used BFT and each level I added one to the counter
queue<Node*> q;
q.push(root_);
int depth = -1;
while (!q.empty()) {
        depth++;
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }
    return depth;
}




void BinarySearchTree::print() const {
    if (root_ == nullptr) {
        return;
    }
    stack<Node*> s;
    Node* current = root_;
    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        cout << current->val << " ";
        current = current->right;
    }
}


bool BinarySearchTree::exists(DataType val) const {
if (root_== nullptr)
{
    return false;
}
Node *current = root_;

while (current != nullptr)
{
  if (current ->val == val)
      return true;
  else if ( val<current->val)
      current = current ->left;
  else if ( val > current->val)
      current = current ->right;

}
return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {

    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
if (root_== nullptr) {
    root_ = new Node(val);
    size_++;
    return true;

}

if (exists(val))
    return false;

Node *current = root_;

while (current != nullptr)
{
    if (val <current ->val)
    {
        if (current ->left == nullptr)
        {
            current ->left = new Node(val);
            size_++;
            return true;
        }
        current = current ->left;
    }
    if (val > current ->val)
    {
        if (current ->right == nullptr)
        {
            current ->right = new Node(val);
            size_++;
            return true;
        }
        current = current ->right;
    }
}

return false;

}

bool BinarySearchTree::remove(DataType val) {

    Node **pT = getRootNodeAddress();

    Node *current = root_;
    Node *parent = nullptr;
    bool isleft = false;
    bool found = false;

    if (size_==0)
        return false;

    while (current != nullptr)
    {
        if (current ->val == val)
        {
            found = true;
            break;
        }
        else if (val<current->val)
        {
            parent = current;
            current = current ->left;
            isleft = true;
        }
        else
        {
            parent = current;
            current = current ->right;
            isleft = false;
        }
    }

    if (!found)
        return false;

    if (current->left == nullptr && current->right== nullptr)
    {
        if (current == root_)
        {
            delete *pT;
            *pT= nullptr;
            size_--;
            return true;
        }
        delete current;
        if (isleft)
            parent->left= nullptr;
        else
            parent->right= nullptr;
        size_--;
        return true;
    }

    if (current->left != nullptr && current->right== nullptr)
    {   if(current==root_)
        {
        Node *temp = root_;
        root_=root_->left;
        size_--;
        delete temp;
        temp= nullptr;
        return true;
        }
        if (isleft)
            parent ->left=current->left;
        else
            parent ->right=current->left;
        delete current;
        size_--;
        return true;
    }
    else if (current->left == nullptr && current->right!= nullptr)
    {
        if(current==root_)
        {
            Node *temp = root_;
            root_=root_->right;
            size_--;
            delete temp;
            temp= nullptr;
            return true;
        }
        if (isleft)
            parent ->left=current->right;
        else
            parent ->right=current->right;
        delete current;
        size_--;
        return true;
    }
    if (current->left != nullptr && current->right!= nullptr)
    {
        Node *predecessor = current->left;
        isleft = true;
        Node *predecessor_parent = current;

        while (predecessor ->right != nullptr)
        {
            predecessor_parent=predecessor;
            predecessor=predecessor->right;
            isleft=false;
        }
        current ->val = predecessor->val;

        if(predecessor->left== nullptr)
        {
            if (!isleft)
                predecessor_parent->right= nullptr;
            else
                predecessor_parent->left= nullptr;
        }
        else
        {
            if (!isleft)
                predecessor_parent->right= predecessor->left;
            else
                predecessor_parent->left= predecessor->left;
        }

        delete predecessor;
        size_--;
        return true;
    }

    return false;
}
