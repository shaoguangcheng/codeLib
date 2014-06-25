#include <stdexcept>
#include <error.h>

template <class T>
quene<T>::quene(int maxSize)
{
    head_ = tail_ = 0;
    upBound = maxSize - 1;

    data = new T[maxSize];
}

template <class T>
void quene<T>::enter(const T &x)
{
    if(isFull()){
        try{
           throw std::overflow_error("quene overflow\n");
        } catch(std::overflow_error err){
            std::cerr << "*********error*************"<<std::endl;
            std::cerr << "error info:"<< err.what()
                      << "file      :"<< __FILE__ << std::endl
                      << "line      :"<< __LINE__ << std::endl
                      << "data " << __DATE__ << " at " << __TIME__<<std::endl;
        }
    }

    data[tail_++] = x;
    if(tail_ > upBound){
        tail_ = 0;
    }
}

template <class T>
 T quene<T>::pop()
 {
     if(isEmpty()){
         try{
            throw std::underflow_error("quene underflow\n");
         } catch(std::underflow_error err){
             std::cerr << "*********error*************"<<std::endl;
             std::cerr << "error info:"<< err.what()
                       << "file      :"<< __FILE__ << std::endl
                       << "line      :"<< __LINE__ << std::endl
                       << "data " << __DATE__ << " at " << __TIME__<<std::endl;
         }
     }

     T x = data[head_++];
     if(head_ > upBound){
        head_ = 0;
     }

     return x;
 }

 template <class T>
 int quene<T>::size()
 {
     if(tail_ >= head_){
        return tail_-head_;
     }
     else {
        return upBound-head_+1+tail_;
     }
 }

 template <class T>
 void quene<T>::clear()
 {
    head_ = tail_ = 0;
 }

 template <class T>
 void quene<T>::resize(int newSize)
 {
     delete [] data;

     data = new T[newSize];
     head_ = tail_ = 0;
     upBound = newSize - 1;
 }


