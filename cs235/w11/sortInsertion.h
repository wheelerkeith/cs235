/***********************************************************************
 * Module:
 *    Week 11, Sort Insertion
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>
#include <iostream>

/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   for (int start = 1; start < num; ++start) // use pre-increment to avoid unnecce ssary temorary object
        {
           T key= array[start]; //assign the number to be found
           int pos = start - 1;
           while((pos >= 0) && (array[pos] > key))//shift everything left of the number over
           {
              array[pos + 1] = array[pos];
              pos -= 1;
           }
           array[pos + 1]=key;//place number in correct spot
        }
}

#endif // SORT_INSERTION_H
