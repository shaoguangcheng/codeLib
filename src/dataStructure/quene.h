#ifndef QUENE_H
#define QUENE_H

template <class T>
class quene
{
public:
    quene(int maxSize = 10);
    ~quene(){delete [] data;}

    inline bool isFull(){return head_ == tail_ +1;}
    inline bool isEmpty(){return head_ == tail_;}

    int size();
    int volume(){return upBound+1;}

    void clear();
    void resize(int newSize);

    inline int head(){return head_;}
    inline int tail(){return tail_;}

    void enter(const T &x);
    T pop();

private:
    int head_;
    int tail_;
    int upBound;

    T *data;
};

#include "quene.hpp"
#endif // QUENE_H
