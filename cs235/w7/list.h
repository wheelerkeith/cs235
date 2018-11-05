/*******************************************************************
 *
 *     FILE: list.h
 *
 *  PURPOSE: Contains the class definition of a Node and a List
 *
 *******************************************************************/
#ifndef _LIST_H
#define _LIST_H
#include "node.h"

template <class T>
class ListIterator;

/**********************************************************************
 * NODE
 * This class holds one node of data, allowing it to point to another
 * creating a linked list
 ***********************************************************************/
template <class T>
class List
{

public:
  /*    CONSTRUCTORS && DESTRUCTORS    */
  // default constructor
  List() : head(NULL), tail(NULL), numItems(0), it(NULL) { }
  // non-default constructor, node
  List(List<T> *& rhs);
  // non-default constructor, data
  List(T item) : head(item), tail(item), numItems(1), it(head) {}


  /*           Methods                */
  void push_back(T item);
  void push_front(T item);
  void insert( ListIterator<T> & ptr, T &item);
  void remove( ListIterator<T> & ptr);
  void clear();
  T & front() const throw (const char *);
  T & back() const throw (const char *);
  ListIterator<T> & end();
  ListIterator<T> & rend();
  ListIterator<T> & begin();
  ListIterator<T> & rbegin();
  int size();
  bool empty();

  /*           Operators              */
  void operator =(List <T> *& rhs);

//private:
  Node<T> * head;
  Node<T> * tail;
  int numItems;
  ListIterator<T> it;


};
/**********************************************************************
 * ListIterator
 * This class Iterators through a list. It contains many Operator Overloads
 ***********************************************************************/
template <class T>
class ListIterator
{
  friend class List<T>;
public:
  ListIterator(): n(NULL){};
  ListIterator(Node<T> * passed): n(passed) {}
  ListIterator & operator ++();
  ListIterator & operator ++(int);
  ListIterator & operator --();
  ListIterator & operator --(int);
  ListIterator & operator =(ListIterator & it){std::swap(n, it.n); return * this;}
  T & operator*();
  bool operator !=(ListIterator & it);
  bool operator ==(ListIterator & it);
  Node<T> * n;
  private:
};



/*             Constructors              */
/**********************************************************************
 * NON-DEFAULT CONSTRUCTOR
 * Creates a structure mimicking another List.
 ***********************************************************************/
template <class T>
List<T> :: List(List<T> *& rhs)
{
  Node<T> * temp = rhs;
  Node<T> * temp2 = this;
  while(temp != NULL)
  {
    this->insert(temp->data, temp2);
    temp2 = this->pNext;
    temp =rhs->pNext;
  }
}


/*             Methods              */
/**********************************************************************
 * PUSH_BACK
 * Adds an item to the back
 ***********************************************************************/
template <class T>
void List<T> :: push_back(T item)
{
  //Is it empty?
	Node<T> * temp = new Node<T>(item);
	if(head == NULL)
	{
	  numItems++;
		head = temp;
		tail = temp;
	}
	//Alright, normal addition
	else
	{
	  numItems++;
		tail->pNext = temp;
		temp->pPrev = tail;
		tail = temp;
	}
}
/**********************************************************************
 * PUSH_FRONT
 * Adds an item to the front
 ***********************************************************************/
template <class T>
void List<T> :: push_front(T item)
{
  //First, check if it's empty.
	Node<T> * temp = new Node<T>(item);
	if(tail == NULL)
	{
	  numItems++;
		head = temp;
		tail = temp;
	}
	//Second, Then throw it at the front.
	else
	{
	  numItems++;
		head->pPrev = temp;
		temp->pNext = head;
		head = temp;
	}
}
/**********************************************************************
 * Insert
 * Adds an item where dictated
 ***********************************************************************/
template <class T>
void List<T> :: insert(ListIterator<T> & ptr, T & item)
{
  //First, make this node the lit.
	Node<T> * temp = new Node<T>(item);
	if(head == NULL)
	{
	  numItems++;
		head = temp;
		tail = temp;
	}
	//Second, is it at the end?
	else if (ptr.n == tail)
	{
	  numItems++;
		tail->pNext = temp;
		temp->pPrev = tail;
		tail = temp;
	}
	// Third, is it at the head?
	else if (ptr.n == head)
	{
	  numItems++;
		head->pPrev = temp;
		temp->pNext = head;
		head = temp;
	}
	//Fourth, if anything weird is put in,
	// as safety, put at end. Beats segfault.
	else if (ptr.n == NULL)
  {
    push_back(item);
  }
  //Lastly, a normal addition.
	else
	{
	  numItems++;
		temp->pNext = ptr.n;
		temp->pPrev = ptr.n->pPrev;
		ptr.n->pPrev = temp;
		if (ptr.n == head)
			head = temp;
		else
			temp->pPrev->pNext = temp;
	}
}

/**********************************************************************
 * REMOVE
 * Removes an item from the list
 ***********************************************************************/
template <class T>
void List<T> :: remove(ListIterator<T> & ptr)
{
  //if empty, do nothing
  if (ptr.n == NULL)
  {
    return;
  }
  //If it's about to be empty.
  else if (numItems == 1)
  {
    head = NULL;
    tail = NULL;
    ptr.n = NULL;
    delete ptr.n;
    numItems--;
    return;
  }
  //If it's at the beginning.
  else if (ptr.n-> pPrev == NULL)
  {
    ptr++;
    ptr.n -> pPrev = NULL;
    head = ptr.n;
    numItems--;
  }
  //If it's at the end.
  else if ( ptr.n->pNext == NULL)
  {
    ptr--;
    ptr.n -> pNext = NULL;
    delete ptr.n->pNext;
    tail = ptr.n;
    numItems--;
  }
  //in the middle
  else
  {
    //temp is needed to find what to delete
    ListIterator<T> temp (ptr.n);
    ptr.n->pPrev->pNext = ptr.n->pNext;
    ptr.n->pNext->pPrev = ptr.n->pPrev;
    //so we don't delete and lose ptr.
    ptr ++;
    temp.n -> pPrev = NULL;
    delete temp.n;
    numItems--;
  }
}
/**********************************************************************
 * CLEAR
 * clears the list, calls remove til done.
 ***********************************************************************/
template <class T>
void List<T> :: clear()
{
  ListIterator <T> temp(head);
  while(numItems != 0)
  {
    head = head->pNext;
    remove(temp);
  }
  //as safety
  numItems = 0;
}
/**********************************************************************
 * FRONT
 * Returns front item by reference, allowing it to be changed
 ***********************************************************************/
template <class T>
T & List<T> :: front() const throw (const char *)
{
  if(head != NULL)
    return head->data;
  else
    throw "";
}

/**********************************************************************
 * BACK
 * Returns back item by reference, allowing it to be changed
 ***********************************************************************/
template <class T>
T & List<T> :: back() const throw (const char *)
{
  if(tail != NULL)
    return tail->data;
  else
     throw "";
}
/**********************************************************************
 * END
 * Returns last Iterator, which should be NULL
 ***********************************************************************/
template <class T>
ListIterator<T> & List<T> :: end()
{
  ListIterator<T> temp(NULL);
  it = temp;
  return it;
}
/**********************************************************************
 * REND
 * Returns Reverse last Iterator, which should be NULL
 ***********************************************************************/
template <class T>
ListIterator<T> & List<T> :: rend()
{
  ListIterator<T> temp(NULL);
  it = temp;
  return it;
}
/**********************************************************************
 * Begin
 * Returns the first Iterator
 ***********************************************************************/
template <class T>
ListIterator<T> & List<T> :: begin()
{
  ListIterator<T> temp(head);
  it = temp;
  return it;
}
/**********************************************************************
 * Begin
 * Returns the reverse first Iterator
 ***********************************************************************/
template <class T>
ListIterator<T> & List<T> :: rbegin()
{
  ListIterator<T> temp(tail);
  it = temp;
  return it;
}
/**********************************************************************
 * SIZE
 * Returns the size of the list
 ***********************************************************************/
template <class T>
int List<T> :: size()
{
  return numItems;
}
/**********************************************************************
 * EMPTY
 * Returns true or false if there are items in it.
 ***********************************************************************/
template <class T>
bool List<T> :: empty()
{
  if(numItems == 0)
    return true;
  else
    return false;
}



/*           Operators              */
/**********************************************************************
 * OPERATOR =
 * Assignment operator
 ***********************************************************************/
template <class T>
void List<T> :: operator =(List <T> *& rhs)
{
  //remove all nodes first.
  clear();
  Node<T> * temp = rhs;
  Node<T> * temp2 = this;
  while(temp != NULL)
  {
    this->insert(temp->data, temp2);
    temp2= this->pNext;
    temp =rhs->pNext;
  }
}
/**********************************************************************
 * OPERATOR ++
 * Progresses the iterator
 ***********************************************************************/
template <class T>
ListIterator<T> & ListIterator<T> :: operator ++()
{
  if(n == NULL)
  {
    return *this;
  }
  this->n = this->n->pNext;
  return *this;
}
/**********************************************************************
 * OPERATOR ++
 * Progresses the iterator
 ***********************************************************************/
template <class T>
ListIterator<T> & ListIterator<T> :: operator ++(int)
{
  if(n == NULL)
  {
    return *this;
  }
  this->n = this->n->pNext;
  return *this;
}
/**********************************************************************
 * OPERATOR --
 * Regresses the iterator
 ***********************************************************************/
template <class T>
ListIterator<T> & ListIterator<T> :: operator -- ()
{
  if(n == NULL)
  {
    return *this;
  }
  this->n = this->n->pPrev;
  return *this;
}
/**********************************************************************
 * OPERATOR --
 * Regresses the iterator
 ***********************************************************************/
template <class T>
ListIterator<T> & ListIterator<T> :: operator -- (int)
{
  if(n == NULL)
  {
    return *this;
  }
  this->n = this->n->pPrev;
  return *this;
}
/**********************************************************************
 * OPERATOR !=
 * Checks and returns true if the two Iterators are not equal
 ***********************************************************************/
template <class T>
bool ListIterator<T>:: operator !=(ListIterator & it)
{
  if(it.n == this->n)
  {
    return false;
  }
  return true;
}
/**********************************************************************
 * OPERATOR ==
 * Checks and returns true if the two Iterators are equal
 ***********************************************************************/
template <class T>
bool ListIterator<T>:: operator ==(ListIterator & it)
{
  if(it.n == this->n)
  {
    return true;
  }
  return false;

}
/**********************************************************************
 * OPERATOR *
 * Returns the data of a Node
 ***********************************************************************/
template <class T>
T & ListIterator<T>:: operator *()
{
  return this->n->data;
}


#endif


