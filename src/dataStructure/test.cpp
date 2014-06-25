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
//    testQuene();
//    point p;
//    vector<point> v;
//    for(int i=0;i<10;i++)
//        for(int j=0;j<10;j++){
//            p.x = i;
//            p.y = j;
//            v.push_back(p);
//        }

//    list<point> l(v);

//    p.x = 9;
//    p.y = 9;
//    int pos = l.search(p);
//    l.print();
//    l.writeDataToFile("coor.txt");

//    std::cout << l.size() <<std::endl;
//    std::cout << pos <<std::endl;

    binaryTree<char> *tree = new binaryTree<char> ('#');
    tree->createBinTree(cin,tree->getRoot());if(tree->getRoot() == NULL)cout << "yes" << endl;
    tree->traverse(tree->getRoot(),cout);

    if(tree->parent('f') != NULL)
        cout << tree->parent('c')->value;
    else
        cout << "not found" << endl;
    tree->depth();

    return 0;
}
