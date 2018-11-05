/*******************************************************************
 *
 *     FILE: list.h
 *
 *  PURPOSE: Contains the class definition of a Node and a List
 *
 *******************************************************************/
#ifndef _LIST_H
#define _LIST_H
using namespace std;
#include <iostream>
#include <cstdlib>

class Node
{
 private:
  int item;                      // --- data in each node
  Node *pnext;                   // --- pointer to next node

 public:
  Node();                        // Default constructor
  Node(bool x) { pNext = x; };   // Non default constructor
  Node *next() { return pNext; };                  // returns next pointer of a node
  int getData() { return item; };                 // returns data of a node
  void setData(int item);        // stores item in data member of current node
  void setNext(Node *node);      // sets next to point to node
};

class List
{
 private:
  int numItems;
  Node *listItems;
  
 public:
  List();
  void insert(int item, int pos);
  List<int> copy(List this);
  int find(int item);
  int freeData();
  int getNumitems(void);
};



#endif


