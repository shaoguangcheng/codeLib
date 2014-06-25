#include <iostream>
#include <stdlib.h>
#include <stdexcept>

template<class T>
stack<T>::stack(const int maxSize)
{
    size_ = 0;
    top  = -1;
    maxTop = maxSize - 1;

    data = new T[maxSize];
}

template<class T>
stack<T>::~stack()
{
    delete [] data;
}

template<class T>
inline bool stack<T>::isEmpty()
{
    return top == -1;
}

template<class T>
inline bool stack<T>::isFull()
{
    return top == maxTop;
}

template<class T>
inline int stack<T>::size()
{
    return size_;
}

template<class T>
void stack<T>::push(const T& x)
{
    if(isFull()){
        try{
           throw std::overflow_error("stack overflow\n");
        } catch(std::overflow_error err){
            std::cerr << "*********error*************"<<std::endl;
            std::cerr << "error info:"<< err.what()
                      << "file      :"<< __FILE__ << std::endl
                      << "line      :"<< __LINE__ << std::endl
                      << "data " << __DATE__ << " at " << __TIME__<<std::endl;
        }
    }

    size_++;
    top++;
    data[top] = x;
}

template<class T>
T stack<T>::pop()
{
    if(isEmpty()){
        try{
           throw std::underflow_error("stack underflow\n");
        } catch(std::underflow_error err){
            std::cerr << "*********error*************"<<std::endl;
            std::cerr << "error info:"<< err.what()
                      << "file      :"<< __FILE__ << std::endl
                      << "line      :"<< __LINE__ << std::endl
                      << "data " << __DATE__ << " at " << __TIME__<<std::endl;
        }
    }

    size_--;
    return data[top--];
}

