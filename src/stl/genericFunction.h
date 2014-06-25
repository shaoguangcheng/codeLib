#ifndef GENERICFUNCTION_H
#define GENERICFUNCTION_H

#include <iostream>

template <class T>
inline void printElement(const T& container,const char* option = "")
{
    typename T::const_iterator pos;

    std::cout << option;
    for(pos = container.begin();pos != container.end();pos++){
        std::cout << *pos << " ";
    }

    std::cout << std::endl;
}

template<class T>
class addAdjacent
{
private:
    int factor;
public:
    addAdjacent(int _factor) : factor(_factor){}

    T operator () (T elem1,T elem2)const
    {
        return (elem1+elem2)*factor;
    }
};

template<class T>
T add(T elem1,T elem2)
{
    return (elem1+elem2);
}

namespace testSTL {
template <class iterator1,class iterator2,class iterator3,class operation>
iterator3 transform(iterator1 begin1,iterator1 end,iterator2 begin2,
               iterator3 result,operation op)
{
    while(begin1!=end){
        *result = op (*begin1,*begin2);
        begin1++;
        begin2++;
        result++;
    }

    return result;
}
}

namespace testSTL {
template <class T>
class greater
{
private:
    T factor;
public:
    greater(T _factor):factor(_factor){}
 //   greater();

    bool operator ()(const T& elem) const
    {
        return elem > factor;
    }
};

template<class T>
void print(T elem)
{
    std::cout << elem << " ";
}

}
#endif // GENERICFUNCTION_H
