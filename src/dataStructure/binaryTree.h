/*
* In this file, I try to implement the most commonly used data structure -- binary tree
*
* Written by chengshaoguang, Northwest Ploytechnical University
* If you have any question with this code, please contact me directly
* Email : chengshaoguang@mail.nwpu.edu.cn
*/

#include <iostream>

// Node defination in binary tree
template <class T>
class binaryTreeNode
{
public:
    T value;
    binaryTreeNode<T> *leftChild;
    binaryTreeNode<T> *rightChild;

    binaryTreeNode() : leftChild(NULL),rightChild(NULL){}
    binaryTreeNode(T value_,binaryTreeNode<T> *leftChild_ = NULL,binaryTreeNode<T> *rightChild_ = NULL) :
    value(value_), leftChild(leftChild_), rightChild(rightChild_){}
};

template <class T>
class binaryTree
{
public:
    binaryTree() : root(NULL){}
    binaryTree(T endFlag_) : endFlag(endFlag_), root(NULL){}
    binaryTree(binaryTree<T> *binTree); //copy construct
    ~binaryTree(){
        destroy(root);
    }

    inline binaryTreeNode<T>* getRoot() const {return root;}
    binaryTreeNode<T>* parent(const T &val) const;
    inline binaryTreeNode<T>* leftChild(binaryTreeNode<T> *node){node == NULL ? NULL : node->leftChild;}
    inline binaryTreeNode<T>* rightChild(binaryTreeNode<T> *node){node == NULL ? NULL : node->rightChild;}

    void createBinTree(std::istream &in, binaryTreeNode<T> *subTree);
    void traverse(binaryTreeNode<T> *subTree, ostream &out) const;
    int depth() const;

    friend istream& operator >>(istream& in,const binaryTree<T> &binTree);
private:
    binaryTreeNode<T> *root;
    T endFlag;

    void destroy(binaryTreeNode<T> *subTree);
    binaryTreeNode<T> *parent(const T &val,binaryTreeNode<T> * current) const;
    int depth(binaryTreeNode<T>* node)const;
};

//here fix me ? question : how to overload '<<' operator in template class
template <class T>
istream& operator >> (istream& in,const binaryTree<T>& binTree)
{
    createBinTree(in,binTree.root);
    return in;
}

#include "binaryTree.hpp"
\
