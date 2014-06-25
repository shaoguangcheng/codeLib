#ifndef CSG_STRING
#define CSG_STRING

#include <string>

using namespace std;

namespace csg{
	//reverse a string
	const string reString(const string& s);

    /**
    * pattern matching with KMP algorithm
    * return the position where pattern first match the target from k-position
	*/
	int fastFind(const string& target,const string& pattern,int k);

    void getNext(const string& pattern,int *next);	//can not use this function directly(assist function)

}//namespace end


#include "../sys/_io_.h"
void testReString()
{
    const string s("linux code");
    PRINT s;
}

#endif
