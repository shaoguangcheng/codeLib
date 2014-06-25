/**
 *  @file io.h
 *  @brief In this file, I plan to rewrite some useful but simple I/O functions
 *
 *  @brief If you have any questions about this code,please contact me directly.
 *  @brief Email : chengshaoguang@gmail.com
 *
 *  @brief Write by Shaoguang Cheng at Northwest Polytechnical University
 */

#ifndef _IO_H_
#define _IO_H_

#include <iostream>
#include <cassert>

namespace csg{

/// define print class to output expressions like python
    class print{
    public:
        print() : space(false){}
        ~print() {
            std::cout << std::endl; // print enter after each recall
        }

        /// overload operator ','
        template <class T>
        print& operator , (const T &p) {
            if(space)
                std::cout << " ";
            else
                space = true;
            std::cout << p;

            return *this;
        }
    private:
        bool space;
    };

    /// output 1d array
    /**
     * This function is used to output one dimision array
     * @param p  the name of one dimidion array
     * @param length  the length of one dimision array
     * @param separator
     */
    template <class T>
    void print1d(T *p,int length , char *separator = "");

    /// output 2d array
    /**
     *  This function is used to output two dimision array
     *  @param p  the start address of the two dimision array. For example, if the two dimision array is a[M][N], then parameter p must be a[0] rather than a
     *  @param len1d  the first dimision length of the two dimision array
     *  @param len2d  the second dimision length of the two dimision array
     *  @param separator
      */
    template <class T>
    void print2d(T *p,int len1d,int len2d,char *separator = "");

    /// output container
    /**
     * This function is used to output container type data.
     * @param container  the container data you want to output. For example, vector, list, deque, set and so on.
     * @param separator
     */
    template <class T>
    void printCon(const T &container, char *separator = "");
}

#define PRINT csg::print(),

/// test print class
void testPrint();

/// test print1d function
#include <string.h>
void testPrint1d();

/// test print2d function
void testPrint2d();

/// test print container function
#include <list>
void testPrintCon();

#endif
