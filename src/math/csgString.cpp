#include "csgString.h"

//reverse a string
const string csg::reString(const string& s)
{
	string result;
	for(int i=s.size()-1;i>=0;i--){
		result.push_back(s[i]);
	}

	return result;
}

//KMP algorithm
//*1
void csg::getNext(const string& pattern,int *next)
{
	int j = 0,k = -1;
		
	next[0] = k;
	while(j < pattern.size()){
		if(k == -1||pattern[j] == pattern[k]){
			k++;
			j++;
			next[j] = k;
		}
		else
			k = next[k];
	}
}
//*2
int csg::fastFind(const string& target,const string& pattern,int k)
{
	int pSize = pattern.size(),tSize = target.size();
	int *next = new int [pSize];
	csg::getNext(pattern,next);

	int j = 0,posP = 0,posT = k;
	while(posP < pSize&&posT < tSize){
		if(posP == -1||pattern[posP] == pattern[posT]){
			posP++;
			posT++;
		}
		else
			posP = next[posP];
	}

	if(posP < pSize)return -1;
	return posT-pSize;
}
