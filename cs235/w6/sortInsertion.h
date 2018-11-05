/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Nik Huff, Tyler Peterson, Keith Wheeler
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <string>
#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   for (int i = 0; i < num; i++)
      for (int j = i + 1; j < num; j++)
      {
         T temp;
         if (array[i] > array[j])
         {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
         }
         
      }
   
}

#endif // INSERTION_SORT_H

