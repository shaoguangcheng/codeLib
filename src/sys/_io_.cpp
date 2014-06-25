#include "_io_.h"

template <class T>
void csg::print1d(T *p,int length , char *separator = ""){
    assert(p != NULL&&length >= 0);
    T *t = p;
    while(length--)
        std::cout << *(t++) << separator;
    std::cout << std::endl;
 }

template <class T>
void csg::print2d(T *p,int len1d,int len2d,char *separator = ""){
    assert(p != NULL&&len1d >=0 &&len2d >= 0);
    T *t = p;
    int len = len1d*len2d;
    while(len--)
        std::cout << *(t++) << separator;
    std::cout << std::endl;
}

template <class T>
void csg::printCon(const T &container, char *separator = "")
{
    typename T::const_iterator iterator;
    for(iterator = container.begin();iterator != container.end();iterator++)
        std::cout << *iterator << separator;
    std::cout << std::endl;
}

void testPrint()
{
    int a = 1,b = 2;
    PRINT "this is a test";
    PRINT "the sum of" , a , "and" , b , "is" , a+b;
}

void testPrint1d()
{
    char *s = "Linux code\n";
    csg::print1d(s,strlen(s));
}

void testPrint2d()
{
    int a[2][3] = {{1,2,3},{5,6,7}};
    csg::print2d(a[0],3,2," ");
}

void testPrintCon()
{
    std::list<int> l;
    for(int i=0;i<10;i++)
        l.push_front(i);

    csg::printCon(l," ");
}
