#include <stack>
//#include "binaryTree.h"

using namespace std;

template <class T>
binaryTree<T>::binaryTree(binaryTree<T> *binTree)
{}

template <class T>
void binaryTree<T>::destroy(binaryTreeNode<T> *subTree)
{
    if(subTree != NULL){
        destroy(subTree->leftChild);
        destroy(subTree->rightChild);
        delete subTree;
    }
}

template <class T>
void binaryTree<T>::createBinTree(istream &in, binaryTreeNode<T> *subTree)
{
    cout << "please input data in this format : A(B(c,d),C)" << endl;

    binaryTreeNode<T> *p,*t;
    std::stack<binaryTreeNode<T>* > s;
    int k = 0;

    subTree = NULL;

    T ch;
    in >> ch;
    while(ch != endFlag){
        switch(ch){
        case '(' :
            s.push(p);
            k = 1;
            break;
        case ')' :
            s.pop();
            break;
        case ',' :
            k = 2;
            break;
        default :
            p = new binaryTreeNode<T>(ch);
            if(subTree == NULL){
                subTree = p;
                root = p;
            }
            else if(k == 1){
                t = s.top();
                t->leftChild = p;
            }
            else{
                t = s.top();
                t->rightChild = p;
            }
        }
        in >> ch;
    }
}

template <class T>
void binaryTree<T>::traverse(binaryTreeNode<T> *subTree, std::ostream &out) const
{
    if(subTree != NULL){
        out << subTree->value << " ";
        traverse(subTree->leftChild,out);
        traverse(subTree->rightChild,out);
    }
}

template <class T>
binaryTreeNode<T>* binaryTree<T>::parent(const T &val) const
{
    return parent(val,root);
}

template <class T>
binaryTreeNode<T>* binaryTree<T>::parent(const T &val,binaryTreeNode<T> *current) const
{
    if(current->leftChild == NULL || current->rightChild == NULL)
        return NULL;

    if(current->leftChild->value == val || current->rightChild->value == val) {return current;}

    binaryTreeNode<T> *p;
    if((p = parent(val,current->leftChild)) != NULL){
        return p;
    }
    else
        return parent(val,current->rightChild);
}

template <class T>
int binaryTree<T>::depth() const
{
   return depth(root);
}

template <class T>
int binaryTree<T>::depth(binaryTreeNode<T>* node)const
{
}



