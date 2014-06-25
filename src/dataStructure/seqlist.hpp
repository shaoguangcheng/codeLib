//#include "seqlist.h"
#include <assert.h>
#include <stdlib.h>


template <class T>
seqList<T>::seqList(int sz) : linearList<T>()
{
    assert(sz > 0);

    maxSize = sz;
    last = -1;
    data = new T [maxSize];
    assert(data != NULL);
}

template <class T>
seqList<T>::seqList(seqList<T> &list) : linearList<T>()
{
    assert(!list.isEmpty());
    maxSize = list.size();
    last = list.length() - 1;
    data = new T [maxSize];
    assert(data != NULL);

    for(int i=1;i<=last+1;i++)
        data[i-1] = list.getData(i);
}

template <class T>
T seqList<T>::getData(int i) const
{
    assert(i>0&&i<=last+1);
    return data[i-1];
}

template <class T>
void seqList<T>::resize(int newSize)
{
    if(newSize == maxSize)
        return;
    else
    {
        T *newArray = new T [newSize];
        assert(newArray != NULL);
        T *srcData = data;
        T *destData = newArray;

        if(last+1 > newSize)
            last = newSize - 1;

//        assert(last > 0);
        int n = last+1;
        while(n--){
            *destData++ = *srcData++;
        }

        delete [] data;
        data = newArray;
        maxSize = newSize;
    }
}

template <class T>
int seqList<T>::locate(int i) const
{}

template <class T>
int seqList<T>::search(T &x) const
{}

template <class T>
bool seqList<T>::setdata(int i, T x)
{
    assert(i>0&&i<=last+1);
    data[i-1] = x;
}

template <class T>
bool seqList<T>::remove(int i)
{}

template <class T>
bool seqList<T>::insert(int i, T x)
{
    assert(i>0&&i-1<=last+1&&last+1<maxSize);
    for(int j=last;j>=i-1;j--)
        data[j+1] = data[j];
    data[i-1] = x;
    last++;
}

template <class T>
void seqList<T>::input()
{}

template <class T>
void seqList<T>::output()
{
    assert(last>=0);
    for(int i=0;i<=last;i++){
        cout << "#" << i+1 << " : " << data[i] << endl;
    }
}

template <class T>
bool seqList<T>::remove(T &x)
{}

template <class T>
void seqList<T>::sort()
{}
