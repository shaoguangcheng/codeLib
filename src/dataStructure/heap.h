#ifndef HEAP_H
#define HEAP_H

template <class T>
class maxHeap
{
public:
    maxHeap();
    maxHeap(T *dat);
    ~maxHeap(){ delete [] data;}

    void sort();
    void insert(const T &dat);
    T extractMax();
    void increaseKey(const T &x,const T &k);

    T operator [](const int index);

    inline void size(){return size_;}
    inline void clear();
    inline T max(){return data[0];}

private:
    T *data;

    void maxHeapIFY(T *dat,int index);
    void buildMaxHeap(T *dat);

    inline int parent(const int index){return index/2;}
    inline int left(const int index){return 2*index;}
    inline int right(const int index){return 2*index + 1;}

    int size_;
};

#endif // HEAP_H
