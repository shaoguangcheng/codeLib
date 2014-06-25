#ifndef CSG_MATH_H
#define CSG_MATH_H

#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <set>


namespace csg{
    /**
    * some	sort algorithms are implemented here.
    * including bubble sort, quick sort, insert sort, bucket sort, heap sort ,shell sort and so on.
    * I just write the bubble sort algorithm, others will be added in near future.
	*/
    //bubble sort
	template <class T>
	void bubbleSort(T* data,int* index,int length)
	{
		assert(data != NULL&&index != NULL&&length > 0);
		for(int i=0;i<length-1;i++)
            for(int j=i;j<length;j++)
		        if(data[i]>data[j]){
		            T d = data[i];
		            data[i] = data[j];
		            data[j] = d;

		            int t = index[i];
		            index[i] = index[j];
		            index[j] = t;
		        }
	}

    //bubble sort(ascend)
    template<class T>
    void bubbleSort(T* ptr,int size)
    {
        assert(ptr != NULL);
        for(int i=0;i<size-1;i++)
            for(int j=i;j<size;j++)
                if(ptr[i] > ptr[j])
                    swap(ptr+i,ptr+j);
    }

    //insert sort algorithm
    template <class T>
    void insertSort(T* ptr,int n)
    {
        assert(ptr != NULL);
        for(int i=1;i<n;i++){
            if(ptr[i] < ptr[i-1]){
                int temp = ptr[i];
                int j;
                for(j=i-1;i>=0;j--)
                    if(temp < ptr[j])
                        ptr[j+1] = ptr[j];
                    else
                        break;
                ptr[j+1] = temp;
            }
        }
    }

    //shell sort
    template <class T>
    void shellSort(T* ptr,int n)
    {
        assert(ptr != NULL);
        for(int step=n/2;step>=1;step/=2)
            for(int i=step;i<n;i+=step)
                if(ptr[i] < ptr[i-step]){
                    int temp = ptr[i];
                    int j;
                    for(j=i-step;j>=0;j-=step)
                        if(ptr[j] > temp)
                            ptr[j+step] = ptr[j];
                        else
                            break;

                    ptr[j+step] = temp;
                }
    }

   //quick sort
    template <class T>
    void quickSort(T* ptr,int left,int right)
    {
        if(left < right){
            int base = ptr[left];
            int i = left,j = right;
            while(i<j){
                while(i<j){
                    if(ptr[j] < base){
                        ptr[i] = ptr[j];
                        break;
                    }
                    else
                        j--;
                }

                while(i<j){
                    if(ptr[i] > base){
                        ptr[j] = ptr[i];
                        break;
                    }
                    else
                        i++;
                }
            }

            ptr[i] = base;
            quickSort(ptr,left,i-1);
            quickSort(ptr,i+1,right);
        }
    }

    //swap two variable
    template <class T>
    void swap(T *val1,T *val2)
    {
        T temp = *val1;
        *val1  = *val2;
        *val2  = temp;
    }

	//random shuffle
    /**
     * @brief randomShuffle  this function is used to rearrange the numbers in given array.
     *                       Ensure every order can be generated in the same propability
     * @param ptr  pointer to one dimision array
     * @param totalNum  the length of ptr
     */
	void randomShuffle(int* ptr,int totalNum);

    /**
     * @brief randomN  to generate n random numbers in range [begin,end)
     * @param result   return n random numbers using this array.
     * @param n
     * @param begin
     * @param end
     */
	void randomN(int* result,int n,int begin,int end);

    /**
	* reverse an iteger number
	* for example : input 120 ,output 21
	* input 123,output 321
	*/
	int reNumber(int x);

	/**
	 * @brief maxPublicFactor
	 * @param a
	 * @param b
	 * @return this function returns the max public factor of a and b
	 */
    int maxPublicFactor(int a,int b);

	/**
	 *  @unique compute the unique elements in src 
	 *  @len the length of src
	 *  @return the total number of elements in dest src[0] ... src[n-1]
	 */
	template<class T>
	int unique(T* src, int len)
	{
		assert(src != NULL);

		int index = 1, end = 0;
		for(;index < len; index++){
		    int k = 0;
		    for(;k <= end; k++)
		        if(src[index] == src[k])
		            break;
		    if(k > end){
		        end++;
				src[end] = src[index];
			}
		}
		
		return end+1;
	}
}//namespace end



#endif
