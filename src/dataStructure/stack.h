#ifndef STACK_H
#define STACK_H

template<class T>
class stack
{
public:
    stack(const int maxSize = 10);
    ~stack();

    void push(const T &x);
    T pop();

    int size();
    bool isEmpty();
    bool isFull();

private:
    int size_;
    int top;
    int maxTop;

    T   *data;
};

#include "stack.hpp"
#endif // STACK_H
