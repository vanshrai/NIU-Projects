/*********************
Vansh Rai Z1877949
CSCI 340
Assignment 08
11/02/2020
I certify that this is my own work and where appropriate an extension of the starter code provided for the assignment.
*********************/
#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include "binarytree.h"
template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    void Insert(const T &x);       // inserts node with value x
    bool Search(const T &x) const; // searches leaf with value x
    bool Remove(const T &x);       // removes leaf with value x
private:
    void _Insert(Node<T> *&, const T &);      // private version of insert
    bool _Search(Node<T> *, const T &) const; // private version of search
    void _Remove(Node<T> *&, const T &);      // private version of remove
    bool _Leaf(Node<T> *node) const;          // checks if node is leaf
};

//Public functions-------------------------------------------------------------------
template < typename T >
void BinarySearchTree < T > ::Insert(const T & x) {
    _Insert(this -> root, x);
}
template < typename T >
bool BinarySearchTree < T > ::Search(const T & x) const {
    return _Search(this -> root, x);
}
template < typename T >
bool BinarySearchTree < T > ::Remove(const T & x) {
    if (Search(x)) { //If the the val is in the tree, remove it.
        _Remove(this -> root, x);
        return true;
    }
    return false;
}
//Private functions-------------------------------------------------------------------
template < typename T >
void BinarySearchTree < T > ::_Insert(Node < T > * & ptr,
    const T & val) {
    if (ptr == NULL) { //If ptr is empty, insert a new node with null values.
        ptr = new Node < T > ();
        ptr -> data = val;
        ptr -> left = NULL;
        ptr -> right = NULL;
    } 
    //Call the functions again till a reached end of the tree.
    else if (val < ptr -> data) { 
        _Insert(ptr -> left, val);
    } 
    else if (val > ptr -> data) {
        _Insert(ptr -> right, val);
    }
}
template < typename T >
bool BinarySearchTree < T > ::_Search(Node < T > * ptr, const T & val) const {
    while (ptr != NULL) { //Do while the loop reaches end
        if (val > ptr -> data) //Take right as the new tree.
            ptr = ptr -> right;
        else if (val < ptr -> data) //Take left as the new right.
            ptr = ptr -> left;
        else
            return true; //Key is found.
    }
    return false;
}
template < typename T >
void BinarySearchTree < T > ::_Remove(Node < T > * & ptr, const T & x) {
    if (ptr -> data < x) //If data is less than x, then call the function with right child as the ptr.
        _Remove(ptr -> right, x);
    else if (ptr -> data > x) { //If data is greater than x, then call the function with left child as the ptr.
        _Remove(ptr -> left, x);
    } 
    else {
        if (_Leaf(ptr)) { //If ptr is a leaf, only then delete!
            ptr = nullptr;
            delete ptr;
        }
    }
}
template < typename T >
bool BinarySearchTree < T > ::_Leaf(Node < T > * ptr) const { 
    if (ptr -> left == nullptr && ptr -> right == nullptr) { //If ptr doesn't have a let node and right it is a leaf.
        return true;
    } 
    else
        return false;
}

#endif // End of BINARYSEARCHTREE_H_