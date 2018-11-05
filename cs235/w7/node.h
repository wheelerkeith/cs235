#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstddef>
#include <new>
using namespace std;

/**********************************************************************
 * NODE
 * This class holds one node of data, allowing it to point to another
 * creating a linked list
 ***********************************************************************/
template <class T>
class Node
{
public:
  /*    CONSTRUCTORS && DESTRUCTORS    */
  // default constructor
  Node() : data(NULL), pNext(NULL), pPrev(NULL) {}
  // non-default constructor
  Node(T nData) : data(nData), pNext(NULL),pPrev(NULL) {}

  /*                DATA               */
  T data;          // what is in the node.
  Node * pNext;       //what's the next node?
  Node * pPrev;   //what was the previous?
};
/**********************************************************************
 * NODE
 * This class holds one node of data, allowing it to point to another
 * creating a linked list
 ***********************************************************************/
template <class T>
class NodeIterator
{
public:
  /*    CONSTRUCTORS && DESTRUCTORS    */
private:

};
#endif // NODE_H
