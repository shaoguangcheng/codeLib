#include <iostream>
#include <fstream>
#include <string>

#include <list>
#include <set>
#include <utility>
#include <map>
#include <algorithm>
#include <iterator>
#include <vector>

#include "genericFunction.h"


using namespace std;

int main()
{
    list<char> charList;

    for(char i='a';i<'z';i++){
        charList.push_back(i);
    }

    list<char>::iterator it = charList.begin();
    for(;it!=charList.end();it++){
        cout << *it;
    }

    cout << endl;


    map<string,int> strIntMap;

    strIntMap["csg"] = 2;
    strIntMap["kfc"] = 3;

    map<string,int>::iterator it_ = strIntMap.begin();
    for(;it_!=strIntMap.end();it_++){
        cout << it_->first << " " << (*it_).second << endl;
    }

    ofstream out;
    out.open("out.txt");
    ostream_iterator<int> output(out,"\n");
    istream_iterator<int> input(cin),eof;

    copy(input,eof,output);

 //   copy(input,eof,back_inserter(intList));
 //   copy(intList.begin(),intList.end(),output);

    list<char>::reverse_iterator r_it = charList.rbegin();
    while(r_it!=charList.rend()){
        cout << *r_it << " ";
        r_it++;
    }

    copy(charList.rbegin(),charList.rend(),ostream_iterator<char> (cout," "));
    cout << endl;
    printElement(charList,"all:");

    vector<int> intVec;
    for(int i=0;i<9;i++)
        intVec.push_back(i);

    testSTL::transform(intVec.begin(),intVec.end(),
              intVec.begin(),intVec.begin(),
                       multiplies<int>());

    for_each(intVec.begin(),intVec.end(),testSTL::greater<int> (12));
    copy(intVec.begin(),intVec.end(),ostream_iterator<int> (cout," "));
    cout << endl;

    replace_if(intVec.begin(),intVec.end(),testSTL::greater<int> (40),40);
    copy(intVec.begin(),intVec.end(),ostream_iterator<int>(cout," "));
    cout << endl;

    intVec.erase(remove_if(intVec.begin(),intVec.end(),bind2nd(equal_to<int> (),40)),
                 intVec.end());
    copy(intVec.begin(),intVec.end(),ostream_iterator<int>(cout," "));
    cout << endl;

    char str[] = "i love c++\n";

    return 0;
}

