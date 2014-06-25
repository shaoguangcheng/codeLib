//#include "list.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

template <class T>
list<T>::list()
{
    pHead = new node<T>;
    pTail = new node<T>;
    pHead->pre = NULL;
    pTail->next = NULL;
    pHead->next = pTail;
    pTail->pre = pHead;
    size_ = 0;
}

template <class T>
list<T>::list(const vector<T> &data)
{
    pHead = new node<T>;
    pTail = new node<T>;
    pHead->pre = NULL;
    pTail->next = NULL;
    pHead->next = pTail;
    pTail->pre = pHead;
    size_ = 0;

    node<T> *pCurrent = pHead;
    pTail->pre = pCurrent;
    for(int i=0;i<data.size();i++){
        node<T> *pTemp = new node<T>;
        pTemp->data = data[i];
        pTemp->next = NULL;
        pCurrent->next = pTemp;
        pTemp->pre  = pCurrent;

        pCurrent = pTemp;
        pTail->pre = pCurrent;

        size_++;
    }
}

template <class T>
list<T>::~list()
{
//    delete pTail;
//    delete pHead;
    node<T> *pCurrent;
    pCurrent = pHead->next;
    while(pCurrent->next != NULL){
        pHead = pCurrent->next;
        pCurrent->next->pre = pHead;
        delete pCurrent;
        pCurrent = pHead;
    }
}

template <class T>
void list<T>::print()
{
    node<T> *pCurrent = pHead;
    if(pCurrent->next == NULL)
        std::cout << "list is NULL" << std::endl;
    while(pCurrent->next != NULL){
        pCurrent = pCurrent->next;
        std::cout << pCurrent->data << std::endl;//here must be modified if data is a struct type.
//        std::cout << "(" << pCurrent->data.x << "," << pCurrent->data.y << ")" <<std::endl;
    }
}

template <class T>
void list<T>::insert(const T &data, int pos)
{
    if(pos <-1||pos ==0||pos > size_){
        try{
           throw std::out_of_range("No such position in list\n");
        } catch(std::out_of_range err){
            std::cerr << "*********error*************"<<std::endl;
            std::cerr << "error info:"<< err.what()
                      << "file      :"<< __FILE__ << std::endl
                      << "line      :"<< __LINE__ << std::endl
                      << "date " << __DATE__ << " at " << __TIME__<<std::endl;
        }
    }

    node<T> *pTemp = new node<T>;
    pTemp->data = data;

    //we add data to tail by default.
    if(pos == -1||pos == size_){
        pTemp->next = NULL;
        pTemp->pre  = pTail->pre;
        pTail->pre->next = pTemp;
        pTail->pre = pTemp;

        size_++;
        return;
    }

    //add data to head
    if(pos == 1){
        pTemp->next = pHead->next;
        pHead->next->pre = pTemp;
        pTemp->pre  = NULL;
        pHead->next = pTemp;

        size_++;
        return;
    }

    int i=0;
    node<T> *pCurrent = new node<T>;
    pCurrent = pHead;
    while(pCurrent->next != NULL){
        pCurrent = pCurrent->next;
        i++;
        if(i == pos){
            pTemp->next = pCurrent;
            pTemp->pre  = pCurrent->pre;
            pCurrent->pre->next = pTemp;
            pCurrent->pre = pTemp;

            size_++;
            break;
        }
    }
    return;
}

template <class T>
void list<T>::del(const int pos)
{
    if(pos < 1||pos > size_){
        try{
           throw std::out_of_range("No such position in list\n");
        } catch(std::out_of_range err){
            std::cerr << "*********error*************"<<std::endl;
            std::cerr << "error info:"<< err.what()
                      << "file      :"<< __FILE__ << std::endl
                      << "line      :"<< __LINE__ << std::endl
                      << "date " << __DATE__ << " at " << __TIME__<<std::endl;
        }
    }

    if(pos == 1){
        pHead->next = pHead->next->next;
        pHead->next->next->pre = NULL;

        size_--;
        return;
    }

    if(pos == size_){
        pTail->pre = pTail->pre->pre;
        pTail->pre->next = NULL;

        size_--;
        return;
    }

    node<T> *pCurrent = new node<T>;
    pCurrent = pHead;

    int i=0;
    while(pCurrent->next != NULL){
        pCurrent = pCurrent->next;
        i++;
        if(i == pos){
            pCurrent->pre->next = pCurrent->next;
            pCurrent->next->pre = pCurrent->pre;

            size_--;
            break;
        }
    }
    return;
}

template <class T>
void list<T>::del(const T &data)
{
    int pos = 0;
    node<T> *pCurrent = new node<T>;

    pCurrent = pHead;
    while(pCurrent->next != NULL){
        pos++;
        pCurrent = pCurrent->next;
        if(pCurrent->data == data){//here data must be modidied to appropriate type
            if(pos == 1||pos == size_)
                del(pos);
            else{
                pCurrent->pre->next = pCurrent->next;
                pCurrent->next->pre = pCurrent->pre;

                size_--;
            }
            break;
        }
    }

    return;
}

template <class T>
T list<T>::locate(int m)
{
    T val;
    int index=0;
    node<T> *pCurrent = pHead;
    if(pCurrent->next == NULL ) exit(-1);//empty list,exit
    while(pCurrent->next != NULL){
        pCurrent = pCurrent->next;
        index++;
        if(index == m){
            val = pCurrent->data;
            break;
        }
    }

    return val;
}

template <class T>
int list<T>::search(const T &data)
{
    int index = 0;
    node<T> *pCurrent = new node<T>;

    pCurrent = pHead;
    while(pCurrent->next != NULL){
        index++;
        pCurrent = pCurrent->next;
        if(pCurrent->data.x == data.x&&pCurrent->data.y == data.y){//here data must be modidied to appropriate type
            return index;
        }
    }

    std::cout << "No such data in list" << std::endl;
    return -1;
//    throw std::out_of_range("No such data in list\n");
}

template <class T>
void list<T>::clear()
{
    pHead->next = NULL;
    pTail->pre = NULL;
    size_ = 0;
}

template <class T>
void list<T>::writeDataToFile(const string &fileName)
{
    std::ofstream out;
    out.open(fileName.c_str());
    node<T> *pCurrent = pHead;

    int lineNumber = 0;
    while(pCurrent->next != NULL){
        lineNumber++;
        pCurrent = pCurrent->next;

        //here must be modified when data type changed
        out << lineNumber << ":  "
            <<pCurrent->data.x<<","
           <<pCurrent->data.y<<std::endl;
    }

    out.close();
}

template <class T>
void list<T>::readDataFromFile(const string &fileName)
{
    std::ifstream in;
}



