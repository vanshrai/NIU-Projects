/*********************
Vansh Rai Z1877949
CSCI 340
Assignment 07
10/28/2020
I certify that this is my own work and where appropriate an extension of the starter code provided for the assignment.
*********************/
#ifndef H_BINARYTREE
#define H_BINARYTREE
#include "node.h"
template <typename T>
class BinaryTree
{
public:
    BinaryTree() { root = NULL; };     // default constructor
    unsigned getSize() const;          // returns size of tree
    unsigned getHeight() const;        // returns height of tree
    virtual void Insert(const T &);    // inserts node in tree
    void Inorder(void (*)(const T &)); // inorder traversal of tree
    typedef enum
    {
        left_side,
        right_side
    } SIDE;
    SIDE rnd()
    {
        return rand() % 2 ? right_side : left_side;
    } // End of rnd()

protected:
    Node<T> *root; // root of tree

private:
    unsigned _getSize(Node<T> *) const;            // private version of getSize()
    unsigned _getHeight(Node<T> *) const;          // private version of getHeight()
    void _Insert(Node<T> *&, const T &);           // private version of Insert()
    void _Inorder(Node<T> *, void (*)(const T &)); // private version of Inorder()
};

//Public functions-------------------------------------------------------------------

template <typename T>
unsigned BinaryTree<T>::getSize() const
{
    return _getSize(root); //Calling private function.
}

template <typename T>
unsigned BinaryTree<T>::getHeight() const
{
    return _getHeight(root); //Calling private function.
}

template <typename T>
void BinaryTree<T>::Insert(const T &a)
{
    _Insert(root, a); //Calling private function.
}

template <typename T>
void BinaryTree<T>::Inorder(void (*c)(const T &))
{
    _Inorder(root, c); //Calling private function.
}

//Private functions-------------------------------------------------------------------

template <typename T>
unsigned BinaryTree<T>::_getSize(Node<T> *n) const
{
    if (n == NULL)
        return 0;

    return (_getSize(n->left) + 1 + _getSize(n->right)); //Recursive function to get the size.
}

template <typename T>
unsigned BinaryTree<T>::_getHeight(Node<T> *n) const
{
    if (!n)
        return 0;
    return 1 + max(_getHeight(n->left), _getHeight(n->right)); //Recursive function to get the height.
}

template <typename T>
void BinaryTree<T>::_Insert(Node<T> *&n, const T &a)
{
    if (n == NULL)
    { //If null make a new node and adding data.
        n = new Node<T>();
        n->right = NULL;
        n->left = NULL;
        n->data = a;
    }
    else if (rnd() == right_side)
    {
        _Insert(n->right, a); //
    }
    else
    {
        _Insert(n->left, a);
    }
}

template <typename T>
void BinaryTree<T>::_Inorder(Node<T> *n, void (*c)(const T &))
{
    if (n != NULL)
    {
        _Inorder(n->left, c);
        c(n->data);
        _Inorder(n->right, c);
    }
}

#endif // End of H_BINARYTREE
