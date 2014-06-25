#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

template <class forewordIterator, class T>
void iota(forewordIterator begin, forewordIterator end, T value)
{
	while(begin != end){
		*begin++ = value;
		++value;
	}
}

void testIota()
{
	typedef list<int> intList;
	typedef list<int>::iterator intListIter;
	
	intList l(10);
	vector<intListIter> v(10);

	iota(l.begin(),l.end(),0);
	iota(v.begin(),v.end(),l.begin());

	random_shuffle(v.begin(),v.end());

	for(auto item: l){
		cout << item << " ";
	}
	cout << endl;
	for(auto item : v){
		cout << *item << " ";
	}
	cout << endl;
}

int main()
{
	testIota();

	return 0;
}
