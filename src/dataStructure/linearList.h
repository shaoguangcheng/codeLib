#ifndef LINEARLIST_H
#define LINEARLIST_H

template <class T>
class linearList
{
public:
    linearList(){}
    ~linearList(){}
    linearList(linearList<T> &list);

    virtual int size()const = 0;
    virtual int length()const = 0;

    virtual int locate(int i)const = 0;
    virtual int search(T &x)const = 0;
    virtual T getData(int i)const = 0;
    virtual bool setdata(int i,T x) = 0;
    virtual bool insert(int i,T x) = 0;
    virtual bool remove(int i) = 0;
    virtual bool remove(T &x) = 0;
    virtual void sort () = 0;
    virtual void input() = 0;
    virtual void output() = 0;

    virtual bool isEmpty()const = 0;
    virtual bool isFull()const = 0;
};

#endif // LINEARLIST_H
