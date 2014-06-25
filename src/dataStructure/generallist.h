#ifndef GENERALLIST_H
#define GENERALLIST_H

/*
 *In this file,I try to implement the general list
 */

#include <iostream>
#include <vector>

using namespace std;

//the node definition of general list
template <class T>
class genListNode{
public:
    genListNode() : uType(additionalHeadNode),tLink(NULL){info.ref = 0;}
    genListNode(const genListNode<T> &node){
        uType = node.uType;tLink = node.tLink;
        switch (uType){
            case additionalHeadNode: info.ref = node.info.ref;break;
            case atomNode: info.value = node.info.value;break;
            case childList: info.hLink = node.info.hLink;break;
        }
    }

public:
    enum nodeType{additionalHeadNode = 0,
                 atomNode,
                 childList};
    nodeType uType;

    union{
        int ref;
        T value;
        genListNode<T> *hLink;
    }info; //information about node

    genListNode<T>* tLink; //the next node in the same level
};


template <class T>
class generalList
{
public:
    generalList();
    generalList(string str);
    generalList(const generalList<T> &gs);
    ~generalList();

    void print()const;
    int depth();
    int length() const;

    genListNode<T>* getHead() const{return head;}

    generalList<T> operator=(const generalList<T> gs);

private:
    T *s;
    genListNode<T> *head;

    vector<char> childListName;
    vector<genListNode<T>* > childListAdd;

    void create(genListNode<T> **ls);
    void print(genListNode<T>* ls,string str)const;
    int length(genListNode<T>* ls) const;
    int depth(genListNode<T>* ls);
    void remove(genListNode<T>* ls);

    genListNode<T>* copy(genListNode<T>* ls);
};

#include "generallist.hpp"
#endif // GENERALLIST_H
