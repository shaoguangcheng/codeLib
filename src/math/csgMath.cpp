#include "csgMath.h"
#include <math.h>

//reverse number
int csg::reNumber(const int x)
{
	int n,temp,result = 0,i=0;

	temp = x;
	while(temp > 0){
		temp /= 10;
		n++;	
	}

	temp = x;
	while(temp > 0){
		int m = temp%10;
		temp /= 10;
		i++;
		result += m*pow(10,n-i);
	}
	
	return result;
}


/**
 * @brief maxPublicFactor
 * @param a
 * @param b
 * @return this function returns the max public factor of a and b
 */
int csg::maxPublicFactor(int a,int b)
{
    if(b == 0){
        return a;
    }

    return maxPublicFactor(b,a%b);
}

//random shuffle
//ensure every order can be generated in the same propability
void csg::randomShuffle(int* ptr,int totalNum)
{
    assert(ptr != NULL&&totalNum > 1);
	srand(time(NULL));
	for(int i=1;i<totalNum;i++){
        csg::swap(ptr+i,ptr+rand()%(i+1));
	}
}

/// @brief: generate N number randomly in region [begin,end)
void csg::randomN(int* result,int n,int begin,int end)
{
	assert(end > begin&&n>0&&result != NULL);
	std::set<int> randN;
	
	srand(time(NULL));
	while(randN.size()<n){
		randN.insert(begin+rand()%(end-begin));
	}

	int i=0;
	std::set<int>::iterator pos = randN.begin();
	for(;pos != randN.end();pos++)	
		result[i++] = *pos;
}
