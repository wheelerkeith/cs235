/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 * Algorithm from cs124 textbook used
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
    int compare = 0;

    bool switched = true;

    // check every spot in the array and switch if needed
    for (int location = num - 1; location >= 1 && switched; location--)
        for (int check = 0, switched = false; check <= location - 1; check++)
        {
            compare++; // add one for every comparison
            if (array[check] > array[check + 1])
                {
                    T temp = array[check]; // swap if out of order
                    array[check] = array[check + 1];
                    array[check + 1] = temp;
                    switched = true; // swapped, kick to outer loop
                }
        }
}


#endif // SORT_BUBBLE_H
