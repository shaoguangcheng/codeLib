#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>

using namespace std;

struct point{
    double x;
    double y;
};

template <class T>
struct node{
    T data;
    node *next;
    node *pre; 

//    constructure function
//    node(node<T> *next=NULL,node<T>*pre=NULL){this->next = next;this->pre = pre;}
//    node(const T &val,node<T> *next=NULL,node<T>*pre=NULL){data = val;this->next = next;this->pre = pre;}
};

template <class T>
class list
{
public:
    list();
    list(const vector<T> &data);
  //  list(const vector<node<T> > *data);
    ~list();

    void insert(const node<T> &data,int pos = -1);
    void insert(const T &data, int pos = -1);
    void del(const T& data);
    void del(const int pos);
    int  search(const T &data);
    T locate(int m);

    void writeDataToFile(const string &fileName);
    void readDataFromFile(const string &fileName);

    inline int size(){return size_;}

    void print();
    void clear();


private:
    node<T> *pHead;
    node<T> *pTail;

    int size_;
};

#include "list.hpp"
#endif // LIST_H
