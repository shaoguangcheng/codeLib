#ifndef POLYNOMAL_H
#define POLYNOMAL_H

#include <iostream>
#include <ostream>

using namespace std;
struct term{
    float coef;
    int   exp;
    term  *next;
    term(float c,int e,term *n=NULL) : coef(c),exp(e),next(n){}
    term* insertAfter(float c,int e){
        next = new term(c,e,this->next);
        return this;
    }
    friend ostream& operator <<(ostream& out,const term& t);
};


class polynomal
{
public:
    polynomal();
    polynomal(const polynomal& p);
    int maxOrder() const;
    term* getHead() const;
    polynomal operator +(const polynomal& p);
    polynomal operator *(const polynomal& p);
    polynomal operator =(const polynomal& p);
    friend ostream& operator <<(ostream& out,const polynomal& p);
    friend istream& operator >>(istream& in,polynomal p);
private:
    term *head;
};

#endif // POLYNOMAL_H
