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
  Node() : data(NULL), pNext(NULL) {}
  // non-default constructor
  Node(T nData) : data(nData), pNext(NULL) {}

  /*                DATA               */
  T data;          // what is in the node.
  Node * pNext;       //what's the next node?
};
/**********************************************************************
 * OPERATOR <<
 * overloads << to display the entire linked list.
 ***********************************************************************/
template <class T>
ostream & operator << (ostream & out, Node <T> *& n)
{
  Node<T> * tempNode = n;
  while(tempNode != NULL)
  {
    out << tempNode->data;
    if (tempNode ->pNext != NULL)
      out << ", ";
    tempNode = tempNode->pNext;
  }
  return out;
}

/**********************************************************************
 * FREEDATA
 * destroys a list, freeing the memory (EXTERMINATE)
 ***********************************************************************/
template <class T>
void freeData (Node<T> *& n1)
{
  if (n1->pNext != NULL)
  {
    freeData(n1->pNext);
  }
  //both likely aren't needed, but better to go for overkill.
  n1 = NULL;
  delete n1;
}
/**********************************************************************
 * COPY
 * copies one Node's data
 ***********************************************************************/
template <class T>
Node<T> * copy(Node<T> * n1)
{
  Node<T> * n2 = new Node<T>(n1->data);
  if (n1->pNext != NULL)
  {
    n2->pNext = copy(n1->pNext);
  }
  return n2;
}
/**********************************************************************
 * INSERT (2 parameters)
 * puts in a new Node into the list not at the head
 ***********************************************************************/
template <class T>
void insert(T nData, Node<T> *& n)
{
  //if the node's not blank, needs to use it to point to this new one
  if(n != NULL)
  {
    Node<T> * n2 = new Node<T>(nData);
    n2->pNext = n->pNext;
    n->pNext = n2;
    return;
  }
  //if it is blank, it can take the place
  else
  {
    n = new Node<T>(nData);
    return;
  }
}
/**********************************************************************
 * INSERT (3 parameters)
 * puts in a new Node into the list maybe at the head
 ***********************************************************************/
template <class T>
void insert(T nData, Node<T> *& n, bool head)
{
  //basically do the above.
  if (head ==false)
  {
    Node<T> * n2 = new Node<T>(nData);
    n2->pNext = n->pNext;
    n->pNext = n2;
    return;
  }
  // or we add a new node infront
  if (head == true)
  {
    Node<T> * newNode = n;
    Node<T> * newHead = new Node<T> (nData);
    newHead->pNext = newNode;
    n = newHead;
  }
}
/**********************************************************************
 * FIND
 * Searches the Nodes for a value
 ***********************************************************************/
template <class T>
Node<T> * find(Node<T> *& n, T & nData)
{
  if (n->data == nData)
  {
    return n;
  }
  else if (n->pNext == NULL)
  {
    cerr << "NOT FOUND\n";
    return n->pNext;
  }
  else
    find(n->pNext, nData);
}
#endif // NODE_H
