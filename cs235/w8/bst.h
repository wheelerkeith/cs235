/*************************************************************************
 *
 *  File: bst.h
 *
 *  Author: Brother Cameron, 10/23/2001
 *
 *  Purpose: Defines the Binary Search Tree class
 *
 **************************************************************************/
#ifndef _BST_H
#define _BST_H

#include "tree.h"

class BST
{
 private:
  BTree *root;
  
 public:
  BST();
  int Empty(void);
  BTree *Search(int item);
  void Insert(int item);
  void Delete(int item);
  void BST_Infix(void);
};
#endif
