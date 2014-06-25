#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iterator>
#include <stdlib.h>

#define GOAL 24
using namespace std;

double op(double n,char operator_,double m)
{	
	double result = 0;
	switch (operator_){
	case '+':
		result = n+m;
		break;
	case '-':
		if(n > m){
			result = n-m;
			break;
		}
		else 
			return -9999;
	case '*':
		result = n*m;
		break;
	case '/':
		if(m < 1e-6) 
			return -9999;
		else{
			result = n/m;
			break;
		}
	}

	return result;
}

void nextPermutation(int array[],int n)
{
    next_permutation(array, array+n);
}

int factorial(int n)
{
	if(n == 1) return n;
	return n*factorial(n-1);
}

bool computer24DotSingle(int a,int
						 b,int c,int
						 d,char
						 operations[]){
	double x = a,y =b,z =c,w =d;
 	char oper[] = {'+','-','*','/'};
	bool isFind = 0;

	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				if((i==1&&j==1&&k==1)||(i==3&&j==3&k==3))continue;
				
				if(fabs(op(op(a,oper[i],b),oper[j],op(c,oper[k],d))-GOAL)
				   < 1e-6){

					operations[0] = oper[i];
					operations[1] = oper[j];
					operations[2] = oper[k];
					operations[3] = '\0';
					isFind = 1;
				}

				if(fabs(op(op(op(a,oper[i],b),oper[j],c),oper[k],d)-GOAL)<
				   1e-6){
					cout << "(("<< a
						 << oper[i]
						 << b <<
						")"<<oper[j] <<
						c<<")" <<
						oper[k] << d
						 << "=" << GOAL
						 << endl;					
					isFind = 1;
				}

				if(fabs(op(op(a,oper[i],op(b,oper[j],c)),oper[k],d)-GOAL)<
				   1e-6){
					cout << "("<<
						a <<
						oper[i] << "("<<
						b <<oper[j] << c
						 << "))"<< oper[k]
						 <<d << "=" <<
						GOAL<<endl;
					isFind = 1;
				}

				if(fabs(op(a,oper[i],op(op(b,oper[j],c),oper[k],d))-GOAL)
				   < 1e-6){
					cout << a <<
						oper[i]<<
						"((" << b
						 <<oper[j]
						 << c<<
						")"<<
						oper[k] <<
						d<< ")=" <<
						GOAL <<endl;
					isFind = 1;
				}

				if(fabs(op(a,oper[i],op(b,oper[j],op(c,oper[k],d)))-GOAL)
				   < 1e-6){
					cout << a <<
						oper[i] <<
						"(" << b <<
						oper[j]
						 <<"(" << c
						 << oper[k]
						 << d
						 <<"))=" <<
						GOAL <<endl;
					isFind = 1;
				}
			}
		}
	}

	return isFind;
}

int computer24Dot(int array[],int n)
{	char oper[4];
	int type = 0;

	int arrange = factorial(n);
	for(int i=0;i<arrange;i++){
		if(computer24DotSingle(array[0],array[1],array[2],array[3],oper)){
			if(!strcmp(oper,"+++")||!strcmp(oper,"***")){
					cout << array[0] <<
				oper[0] << array[1]
				 << oper[0] <<
				array[2] <<oper[0]
				 << array[3] <<
						"="<< GOAL<<
						  endl;
					break;
			}
		}
		nextPermutation(array,n);
	}

	return 0;
}


int main(int argc, char *argv[])
{
	int array [4];

	while(1){
		cout << "this programe simulate the 24 dot game"<< endl;
		cout << "fisrt input four numbers,then end with a character that isn't a number and type enter key.Ctrl+c to exit this programe"<<endl;
		cout << "please input four numbers between 0-100 :";

//		copy(istream_iterator<int>
//			 (cin),istream_iterator<int>(),array);
		for(int i=0;i<4;i++){
			array[i] = -1;
			cin >> array[i];
			if(array[i]<0||array[i]>100){
				cout << "input error" << endl;
				return -1;
			}
		}

		system("clear");

		cout << "************************"<<endl;
		computer24Dot(array,4);
		cout << "************************"<<endl;
	}	
	
    return 0;
}

