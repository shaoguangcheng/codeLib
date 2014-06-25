#include "generallist.h"

#include <assert.h>
#include <string>
#include <string.h>
#include <algorithm>

template <class T>
generalList<T>::generalList(){
    head = new genListNode<T>;
    assert(head != NULL);

    s = NULL;
}

template <class T>
generalList<T>::generalList(string str)
{
    head = new genListNode<T>;
    assert(head != NULL);

    s = (char*)str.c_str();
    if(isalpha(s[0])&&isupper(s[0])){
        childListName.push_back(s[0]);
        childListAdd.push_back(head);

        s = subStr(s,strlen(s),2);
        create(&(head->tLink));
    }
    else{
        cout << "error input" << endl;
        exit(-1);
    }
}

template <class T>
generalList<T>::generalList(const generalList<T> &gs)
{
    this->head = copy(gs.getHead());
}

//return a string that start from n-th element in s
template <class T>
T* subStr(const T *s,int len,int n){
    assert(len >= n);
    T* result = new T[len-n];

    for(int i=0;i<len-n;i++)
        result[i] = s[i+n];

    return result;
}

template <class T>
void generalList<T>::create(genListNode<T> **ls)
{
    if(strlen(s) == 0) return;
    if(isalpha(s[0])&&isupper(s[0])||s[0] == '('){
        *ls = new genListNode<T>;
        (*ls)->uType = genListNode<T>::childList; //create a child list node
        (*ls)->info.hLink = NULL;

        if(isalpha(s[0])&&isupper(s[0])){
            vector<char>::iterator m = find(childListName.begin(),childListName.end(),s[0]);
            if(m != childListName.end()){
                genListNode<T> *p = *(m-childListName.begin()+childListAdd.begin());
                p->info.hLink->info.ref++;
            }
            else{
                childListName.push_back(s[0]);
                childListAdd.push_back(*ls);
            }

            if(m == childListName.end()&&s[1] != '('){
                cout << "error input\n" << endl;
                exit(-1);
            }

            s = subStr(s,strlen(s),2);//here must be modified when T is changed.I just think it is char by default.
        }
        else
            s = subStr(s,strlen(s),1);

        (*ls)->info.hLink = new genListNode<T>;//create an additional head node
        (*ls)->info.hLink->uType = genListNode<T>::additionalHeadNode;
        (*ls)->info.hLink->info.ref = 1;

        create(&((*ls)->info.hLink->tLink));//create child list node recursively
        create(&((*ls)->tLink));//create successor node
    }
    else if(isalpha(s[0])&&islower(s[0])){
        (*ls) = new genListNode<T>;
        (*ls)->uType = genListNode<T>::atomNode;
        (*ls)->info.value = s[0];

        s = subStr(s,strlen(s),1);
        create(&((*ls)->tLink));
    }
    else if(s[0] == ','){
        s = subStr(s,strlen(s),1);
        create(ls);
    }
    else if(s[0] == ')'){
        s = subStr(s,strlen(s),1);
        *ls = NULL;
    }
    else if(s[0] == '#'){
        s = subStr(s,strlen(s),1);
        *ls = NULL;
    }

    return;
}

template <class T>
void generalList<T>::print() const
{
    cout << "elements in general list : "<< endl;
    string str("");
    print(head,str);
}

template <class T>
void generalList<T>::print(genListNode<T> *ls,string str) const
{
    if(ls == NULL)return;
    if(ls->uType == 0){
        str += "-";
        print(ls->tLink,str);
    }
    if(ls->uType == 1){
        cout << "# : " << str << ls->info.value << endl;
        print(ls->tLink,str);
    }
    if(ls->uType == 2){
        print(ls->info.hLink,str);
        print(ls->tLink,str);
    }
}

template <class T>
int generalList<T>::length() const
{
    return length(head->tLink);
}

template <class T>
int generalList<T>::length(genListNode<T>* ls)const
{
    if(ls == NULL) return 0;
    return 1+length(ls->tLink);
}

template <class T>
int generalList<T>::depth()
{
    return depth(head->tLink);
}

template <class T>
int generalList<T>::depth(genListNode<T>* ls)
{
    if(ls == NULL) return 0;
    if(ls->uType == genListNode<T>::atomNode){
        return max(1,depth(ls->tLink));
    }

    if(ls->uType == genListNode<T>::childList){
        return max(depth(ls->info.hLink),depth(ls->tLink));
    }

    if(ls->uType == genListNode<T>::additionalHeadNode){
        return 1+depth(ls->tLink);
    }
}

template <class T>
generalList<T> generalList<T>::operator =(const generalList<T> gs)
{
    head = copy(gs.getHead());
    return *this;
}

template <class T>
genListNode<T>* generalList<T>::copy(genListNode<T> *ls)
{
    if(ls == NULL)return NULL;
    genListNode<T>* p = new genListNode<T>;
    p->uType = ls->uType;

    switch(p->uType){
    case genListNode<T>::additionalHeadNode:
        p->info.ref = ls->info.ref;
        break;
    case genListNode<T>::atomNode:
        p->info.value = ls->info.value;
        break;
    case genListNode<T>::childList:
        p->info.hLink = copy(ls->info.hLink);
        break;
    }

    p->tLink = copy(ls->tLink);

    return p;
}

template <class T>
generalList<T>::~generalList()
{
//    remove(head);
}

template <class T>
void generalList<T>::remove(genListNode<T> *ls)
{
    if(ls == NULL) return;
    genListNode<T> *p = new genListNode<T>;

    if(ls->uType == 0){
        if(ls->info.ref <= 0){
            p = ls->tLink;
            ls->tLink = p->tLink;
            delete p;
            remove(ls->tLink);
        }
        else
            ls->info.ref--;
    }
    else{
        p = ls->tLink;
        if(ls->uType ==2 ){
          remove(ls->info.hLink);
          if(ls->info.hLink->info.ref <= 0)
              delete ls->info.hLink;
        }

        ls->tLink = p->tLink;
        delete p;
        remove(ls->tLink);
    }
}

void testSubStr()
{
    char* s = "my name is chengshaoguang\n";
    s = subStr(s,strlen(s),20);
    cout << s << endl;
}
