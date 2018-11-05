/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
   for (int start = num - 1; start >= 1; start--)
   {
      int largest = 0;
      for (int check = 1; check <= start - 1; check++)//search array for largest number
         if (array[largest] <= array[check])
            largest = check;//when number is found set largest to its location
      if (array[largest] > array[start])//swap largest number to back
      {
         T temp = array[largest];
         array[largest] = array[start];
         array[start] = temp;
      }
   }
}

template <class T>
bool operator <= (const T & lhs, const T & rhs)
{
   return !(lhs <= rhs);
}

#endif // SORT_SELECTION_H
