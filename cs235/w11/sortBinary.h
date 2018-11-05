/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
	BST<T> sorted;
	int i;

	for (i = 0; i < num; i++)
		sorted.insert(array[i]);

	BSTIterator <T> it;
	for (it = sorted.begin(), i = 0; it != sorted.end(); ++it, i++)
		array[i] = *it;
}


#endif // SORT_BINARY_H
