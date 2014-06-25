#include "classicProblem.h"
#include "csgString.h"
#include <string.h>
#include <time.h>

void testAllRange()
{
    cout << "all range--method 1: " << endl;
    char str[] = "123";
    csg::allRange_1(str,0,strlen(str));
}

void testFib()
{
    cout << csg::Fib_r(10) << endl;
    cout << csg::Fib_nr(10) << endl;
}

void testPlace()
{
    csg::placePieces(0);
}

void testBing()
{
    const char* str = "myuuieiwniubbingbewnbwebibingbunuivbbubib";
    clock_t start = clock();
    cout << csg::countBing(str) << endl;
    clock_t end = clock();

    cout << (end-start) << endl;
}

void testMaxPalinder()
{
    const char* str = "adsgwergerhsddddffeadada";
    int start = 0,end = 0;
   csg::maxPalindrome(str,start,end);
   cout << start << " " << end << endl;
}

void testUnique()
{
	int src[10] = {1,2,3,2,1,4,3,2,4,6};

	int n = csg::unique(src, 10);
	for(int i=0;i<n;i++)
		cout << src[i] << " ";
	cout << endl;
}

int main()
{
//   testAllRange();
//    csg::seekPath(30,30);
//    testPlace();
//    testReString();
//    testBing();
//    testMaxPalinder();
	testUnique();
	return 0;
}
