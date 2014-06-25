#ifndef SEQLIST_H
#define SEQLIST_H

#include "linearList.h"

template<class T>
class seqList : public linearList<T>
{
public:
    seqList(int sz = 10);
    seqList(seqList<T> &list);
    ~seqList(){delete [] data;}

    int size() const{return maxSize;}
    int length() const{return last+1;}
    int locate(int i) const;
    int search(T &x) const;
    T getData(int i) const;
    bool setdata(int i, T x);
    bool insert(int i, T x);
    bool remove(int i);
    bool remove(T &x);
    void input();
    void output();
    void sort();

    bool isEmpty() const{return (last == -1) ? true : false;}
    bool isFull() const{return (last == maxSize-1) ? true : false;}

    void resize(int newSize);
protected:
    T *data;
    int maxSize;
    int last;
};

template <class T>
struct node_{
  T data;
  node_<T>* next;
  node_(const T &val,node_<T>* n =NULL){data = val;this->next = n;}
  node_* insertAfter(const T &val){next = new node_<T>(val,next);return next;}//be careful with this auto link method
};

void testNode_()
{
    node_<int> *p =  new node_<int>(0);
    p->insertAfter(2);
    cout << p->next->data << endl;
}

#include "seqlist.hpp"

#endif // SEQLIST_H
