#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <math.h>
#include <string.h>

#include "classicProblem.h"

using namespace std;
using namespace csg;

    //josephus problem
    /** description:
    There are people standing in a circle waiting to be executed. The counting out begins at some point in the circle and proceeds around the circle in a fixed direction. In each step, a certain number of people are skipped and the next person is executed. The elimination proceeds around the circle (which is becoming smaller and smaller as the executed people are removed), until only the last person remains, who is given freedom.
    The task is to choose the place in the initial circle so that you are the last one remaining and so survive.
    */
void csg::josephus(int n,int m)
{
	cout << "slove josephus problem : " << endl;
	assert(m<n);
	vector<int> Js;
	for(int i=1;i<=n;i++)
		Js.push_back(i);

	int d = 0;
	for(int i=1;i<n;i++){
		d += m-1;
		if(d >= Js.size()) d %= Js.size();
		cout << "out : " << *(Js.begin()+d) << endl;
		Js.erase(Js.begin()+d);		
	}
	cout << "final : " << Js[0] << endl;
}

/*
    compute fibnacci number sequence
*/
/// method 1 : using recursive
long csg::Fib_r(long n)
{
	if(n<=1) return n;
	else
		return Fib_r(n-1)+Fib_r(n-2);
}

/// method 2 : using non-recursive
long csg::Fib_nr(long n)
{
	long F0 = 0,F1 = 1,temp;
	while(n-->=2){
		temp = F0+F1;
		F0   = F1;
		F1   = temp;
	}
	return temp;
}

/*
seek path in maze
*/
struct item{
	int x;
	int y;
	int dir; 
};

struct dmove{
	int dx;
	int dy;
};

ostream& operator << (ostream& out,stack<item> S)
{
	item it;
	while(!S.empty()){
		it = S.top();
		S.pop();
		out << "(" << it.x << "," << it.y << ")" << endl;
	}
	return out;
}

void csg::seekPath(int m,int p)
{
	bool **map = new bool* [m+2];
	bool **mark = new bool* [m+2];
	assert(map != NULL);
	assert(mark != NULL);

	map[0] = new bool[(m+2)*(p+2)];
	mark[0] = new bool[(m+2)*(p+2)];
	assert(map[0] != NULL);
	assert(mark[0] != NULL);

	for(int i=1;i<m+2;i++){
		map[i] = map[0] + (p+2)*i;
		mark[i] = mark[0] + (p+2)*i;
	}
	
	dmove move[8] = {{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};

//initialize the map
	map[0][0] =	map[m+1][p+1] = 0;
	map[0][p+1] = map[m+1][0] = 1;
	for(int i=1;i<m+1;i++)
		map[i][0] = map[i][p+1] = 1;
	for(int i=1;i<p+1;i++)
		map[0][i] = map[m+1][i] = 1;

	srand(time(NULL));
	for(int i=1;i<m+1;i++)
		for(int j=1;j<p+1;j++)
			map[i][j] = rand()%2;	

	cout << "map : " << endl;
	for(int i=0;i<m+2;i++){
		for(int j=0;j<p+2;j++)
			cout << map[i][j] << " ";
	cout << endl;
	}
	cout << endl; 

//initialize stack
	stack<item> S;
	item it;
	it.x = 0;it.y = 0;it.dir = 0; 	
	S.push(it);

//seek path using basic search tactic
	int i,j,g,h,d;
	while(!S.empty()){
		it = S.top();
		S.pop();
		i = it.x;j = it.y;d = it.dir;
		while(d < 8){
			g = i+move[d].dx;h = j+move[d].dy;
			if(g == m+1&&h == p+1){
				cout << "the path from entrance to exit :" << endl;
				cout << "(" << i << "," << j << ")" << endl;
				cout << S << endl;
				cout << "complete" << endl;
				return;
			}

			if(g<0||h<0){d++;continue;};
			if(!map[g][h]&&!mark[g][h]){
				mark[g][h] = 1;
				it.x = i;it.y = j;it.dir = d;
				S.push(it);
				i = g;j = h;d = 0;
			}
			else
				d++;
		}
	}
	
	cout << "no path to reach terminal" << endl;
	return;
}

/**
 * @brief solve N queen problems. N is the minimum of cols and rows by default, but you can define the N in line 210
 */
#define cols 8
#define rows 8

struct point{
	int x;
	int y;
	point(){}
	point(int x_,int y_) : x(x_),y(y_){}
	point(const point &p) : x(p.x),y(p.y){}
};
int number = 0;
int method = 0;

vector<point> position;

bool isSafe(int row,int col)
{
	point p;
	vector<point>::iterator it = position.begin();
	for(;it!=position.end();it++){
		p = *it;
		if(p.x == row    //row condition
			||p.y == col //col condition
			||fabs(p.x-row)==fabs(p.y-col))          //diagnoal condition
			return false;
	}
	
	return true;
}

ostream& operator << (ostream& out,const vector<point> &position)
{
	point p;
    vector<point>::const_iterator it = position.begin();
	for(;it!=position.end();it++){
		p = *it;
		out << " (" << p.x << "," << p.y << ") " ;
	}
	return out;
}

void csg::placePieces(int n)
{
    if(number == min(rows,cols)){ // you can replace min() function with a fixed number to solve N queens numbers
		cout << "method " << ++method << " : "<< endl;
		cout << position << endl;
		return;
	}

	int c = 0;
	while(c < cols){
		if(isSafe(n,c)){
			number++;
			position.push_back(point(n,c));
			csg::placePieces(n+1);
			position.pop_back();
			number--;
		}
		c++;
	}
	
	return;	
}

////////////////////////////////////////////////////////////////////////////////////
int csg::countBing(const char *strBing)
{
    assert(strBing != NULL);

    struct B{
        short pos;
        short next;
    };

#if 0
#define MAX_BING
#endif

    int len = strlen(strBing);

    B* listB = new B [len];
    B* listI = new B [len];
    B* listN = new B [len];
    B* listG = new B [len];

    int numB = 0;
    int numI = 0;
    int numN = 0;
    int numG = 0;

    for(int i=0;i<len;i++){
        if(*(strBing+i) == 'B'||*(strBing+i) == 'b'){
            listB[numB].pos = (short)i;
            numB++;
        }
        else if(*(strBing+i) == 'I'||*(strBing+i) == 'i'){
            listI[numI].pos = (short)i;
            numI++;
        }
        else if(*(strBing+i) == 'N'||*(strBing+i) == 'n'){
            listN[numN].pos = (short)i;
            numN++;
        }
        else if(*(strBing+i) == 'G'||*(strBing+i) == 'g'){
            listG[numG].pos = (short)i;
            numG++;
        }
    }

    int t = 0;
    for(int i=0;i<numB;i++){
        for(int j=t;j<numI;j++){
            if(listB[i].pos < listI[j].pos){
                listB[i].next = j;
                t = j;
                break;
            }
        }
    }

    t = 0;
    for(int i=0;i<numI;i++){
        for(int j=t;j<numN;j++){
            if(listI[i].pos < listN[j].pos){
                listI[i].next = j;
                t = j;
                break;
            }
        }
    }

    t = 0;
    for(int i=0;i<numN;i++){
        for(int j=t;j<numG;j++){
            if(listN[i].pos < listG[j].pos){
                listN[i].next = j;
                t = j;
                break;
            }
        }
    }

    int count = 0;
    for(int i=0;i<numB;i++){
        for(int j=listB[i].next;j<numI;j++){
            for(int k=listI[j].next;k<numN;k++){
                for(int p=listG[k].next;p<numG;p++){
                    count++;
#if 0
                    if(count > MAX_BING)
                        cout -= MAX_BING;
#endif
                }
            }
        }
    }

    delete [] listB;
    delete [] listI;
    delete [] listN;
    delete [] listG;

    return count;
}

////////////////////////////////////////////////////////////////////
void csg::maxPalindrome(const char* str,int& start,int &end)
{
    int len = strlen(str);
    char* realStr = new char [len];
    int* pos = new int [len];

    int index = 0;
    for(int i=0;i<len;i++){
        if(isalpha(str[i])){
            pos[index] = i;
            realStr[index++] = str[i];
        }
    }

    int max = 0;
    bool flag = 0;
    for(int i=1;i<len;i++){
        if(realStr[i] == realStr[i+1])
            flag = 1;
        for(int j=0;i>=j&&i+j<len;j++){
            if(flag == 1){
                if(realStr[i-j] != realStr[i+1+j])break;
                if(2*j+2 >max){
                    max = 2*j+2;
                    start = pos[i-j];
                    end   = pos[i+j+1];
                }
                flag = 0;
            }
            else{
                if(realStr[i-j] != realStr[i+j])break;
                if(2*j+1>max){
                    max = 2*j+1;
                    start = pos[i-j];
                    end = pos[i+j];
                }
            }
        }
    }

    delete [] pos;
    delete [] realStr;
}
