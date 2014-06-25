#ifndef CLASSIC_PROBLEM_
#define CLASSIC_PROBLEM_

#include <iostream>
#include <assert.h>
#include <algorithm>
#include <iterator>

#include "csgMath.h"

using namespace std;

namespace csg{

/**
     * @brief maxPalindrome 输入一个字符串，求出其中最长的回文子串。子串的含义是：在原串连续出现的字符串片段。
         *回文的含义是：正着看和倒着看是相同的，如abba和abbebba。在判断是要求忽略所有的标点和空格，且忽略大小写，
         *但输出时按原样输出（首尾不要输出多余的字符串）
     * @param str
     * @param start
     * @param end
     * @return maximum palindrome
     */
    void maxPalindrome(const char* str,int &start,int &end);

    /**
     * @brief countBing 例如有一个字符串"iinbinbing"，截取不同位置的字符‘b’、‘i’、‘n’、‘g’组合成单词"bing"。
                        若从1开始计数的话，则‘b’ ‘i’ ‘n’ ‘g’这4个字母出现的位置分别为(4,5,6,10) (4,5,9,10),
                        (4,8,9,10)和(7,8,9,10)，故总共可以组合成4个单词”bing“。
                        问题是：现给定任意字符串，只包含小写‘b’ ‘i’ ‘n’ ‘g’这4种字母，请问一共能组合成多少个单词bing?

                        字符串长度不超过10000，由于结果可能比较大，请输出对10^9 + 7取余数之后的结果。
     * @param strBing input string
     * @return  the total number
     */
    int countBing(const char* strBing);


    /**
     * @brief josephus There are people standing in a circle waiting to be executed. The counting out begins at some point in the circle and proceeds around the circle in a fixed direction. In each step, a certain number of people are skipped and the next person is executed. The elimination proceeds around the circle (which is becoming smaller and smaller as the executed people are removed), until only the last person remains, who is given freedom.
                       The task is to choose the place in the initial circle so that you are the last one remaining and so survive.
     * @param n   all people in circle
     * @param m   the number of people to skip
     */
	void josephus(int n,int m);

    /**
     * @brief  The swap function have been defined in math.h. So I enable this code fragment
     */
#if 0
	template <class T>
	void swap(T* val1,T* val2)
	{
		assert(val1 != NULL&&val2 != NULL);
		T temp = *val2;
		*val2  = *val1;
		*val1  = temp; 
    }
#endif


    /// output ptr in reverse from k-th element to end element
    /**
        @brief  for example, when ptr = "abcde",k = 2,totalNum = 5, then the output is ptr = "aedcb"
        @param  ptr  a pointer point to a C-like style string
        @param  k  from which character to reverse the string
        @param  totalNum  the length of the string
    */
    template <class T>
    void reverse(T* ptr,int k,int totalNum)
    {
        T *temp;

        if(k == totalNum-1)
            return ;

        temp = new T [totalNum-k];

        for(int i=0;i<totalNum-k;i++)
            temp[i] = ptr[totalNum-i-1];
        int j = 0;
        for(int i=k;i<totalNum;i++)
            ptr[i] = temp[j++];

        delete [] temp;
    }

    /// slove all range problems
    /// method one
	static int size = 0;
	template <class T>
    void allRange_1(T *ptr,int currentNum,int totalNum)
	{
		assert(ptr != NULL);
		if(currentNum == totalNum){
			size++;
			cout << size << "-th all range :"; 
			for(int i=0;i<totalNum;i++)
				cout << ptr[i] << " ";
			cout << endl; 
		}
		else{
				for(int i=currentNum;i<totalNum;i++){
					swap(ptr+currentNum,ptr+i);			
                    allRange_1(ptr,currentNum+1,totalNum);
					swap(ptr+i,ptr+currentNum);
			}
		}
	}

    /// method two
    template <class T>
    void allRange_2(T* ptr,int totalNum)
    {
        bool isRight;
        bubbleSort(ptr,totalNum);
        print_(ptr,totalNum);

        T* temp = new T[totalNum];
        strcpy(temp,ptr);
        do{
            isRight = next_permutation(ptr,ptr+totalNum);

            if(strcmp(temp,ptr) != 0)
                print_(ptr,totalNum);

        }while(isRight);
    }


    /// method three
    template <class T>
    bool nextPermutation(T* ptr,int totalNum)
    {
        bool isRight = true;
        for(int i=0;i<totalNum-1;i++)
            if(ptr[i] < ptr[i+1]){
                isRight = false;
                break;
            }
            if(isRight)return false;


        int p = totalNum-1,q = totalNum-2;
        while(p != 0){
            int index;
            if(*(ptr+p) <= *(ptr+q)){
                q--;
                p--;
                continue;
            }

            for(int i=totalNum-1;i>=p;i--){
                if(*(ptr+i) > *(ptr+q)){
                    index = i;
                    break;
                }
            }

            swap(ptr+index,ptr+q);
            reverse(ptr,p,totalNum);

            p--;
            q--;
            print_(ptr,totalNum);
            break;
        }

        return true;
    }

    template <class T>
    void allRange_3(T* ptr,int totalNum)
    {
        bool isRight;
        bubbleSort(ptr,totalNum);
        print_(ptr,totalNum);

        T* temp = new T[totalNum];
        strcpy(temp,ptr);
        do{
            isRight = nextPermutation(ptr,totalNum);

        }while(isRight);
    }

    /**
     *  Because of the time reason, the function print has the same name with the class print in _io_.h file. So I rename it
     *  print_. The funtion print1d in _io_.h can replace print_ and has more robustness. This part will be rewrite iin near future.
     */
	template <class T>
    void print_(T* ptr,int length)
	{
        for(int i=0;i<length;i++)
            cout << ptr[i] << " ";
        cout << endl;

    //	copy(ptr,ptr+length,ostream_iterator<T>(cout," "));
    //	cout << endl;
	}

    /**
     * @brief matchPairs  this function is used to check the matched pairs in given expression
     * @param expression   the string you want to check
     */
    void matchPairs(char* expression);

    /**
     * @brief seekPath  seek path in a self-defined map. Obstacle in the map is generated randomly.
     * @param m  width of map
     * @param p  height of map
     */
	void seekPath(int m,int p);

    /**
     * @brief placePieces  this function is used to solve N queens problem
     * @param n
     */
    /// note : this function need to be modified to make it looks comfortable
    void placePieces(int n);

    /// calculate
	long Fib_r(long n);
	long Fib_nr(long n);
}//namespace end

#endif
