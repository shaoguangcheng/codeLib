#include "stack.h"
#include "quene.h"
#include "list.h"
#include "binaryTree.h"

#include <vector>

void testQuene()
{
    quene<int> intStack(11);
    for(int i=0;i<10;i++)
        intStack.enter(i);

    std::cout << "head:" << intStack.head()<<std::endl;
    std::cout << "tail:" << intStack.tail()<<std::endl;
    std::cout << "size:" << intStack.size()<<std::endl;
    for(int i=0;i < 10;i++){
        std::cout << intStack.pop() <<std::endl;
    }

    std::cout << "head:" << intStack.head()<<std::endl;
    std::cout << "tail:" << intStack.tail()<<std::endl;
    std::cout << "size:" << intStack.size()<<std::endl;
    for(int i=0;i<3;i++)
        intStack.enter(i);
    std::cout << "head:" << intStack.head()<<std::endl;
    std::cout << "tail:" << intStack.tail()<<std::endl;
    std::cout << "size:" << intStack.size()<<std::endl;

    intStack.resize(20);
    std::cout << "head:" << intStack.head()<<std::endl;
    std::cout << "tail:" << intStack.tail()<<std::endl;
    std::cout << "size:" << intStack.volume()<<std::endl;
}

int main()
{

    return 0;
}
