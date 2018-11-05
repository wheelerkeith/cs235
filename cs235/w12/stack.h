/***********************************************************************
* Header:
*    Container
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Container         : A class that holds stuff
*        ContainerIterator : An interator through Container
* Author
*    Br. Helfrich
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>

/************************************************
 * CONTAINER
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
   Stack() : _top(-1), _capacity(0), numItems(0), data(NULL) {}

   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Stack(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Stack()        { if (_capacity) delete [] data; }

   // overload assignment operator
   Stack & operator = (const Stack & rhs);

   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear() { _top = -1; numItems = 0; }

   // how many items are currently in the container?
   int size() const    { return numItems;               } 

   // how many items can I put in the vector?
   int capacity() const { return _capacity;		   }

   // add an item to the container
   void push(const T & t) throw (const char *);

   void pop() throw (const char*);

   T& top() const throw (const char *);
   
private:
   int numItems;
   int _capacity;      // how many items can I put on the Container before full?
   T * data;          // dynamically allocated array of T
   int _top;           // index of the top item in the stack
  
};

template<class T>
Stack<T>::Stack(const Stack & rhs) throw(const char *)
{
	assert(rhs._capacity >= 0);

	// do nothing if there is nothing to do
	if (rhs._capacity == 0)
	{
		_capacity = numItems = 0;
		_top = -1;
		data = NULL;
		return;
	}

	// attempt to allocate
	try
	{
		data = new T[rhs._capacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the capacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs._capacity);
	_capacity = rhs._capacity;
	_top = rhs._top;
	numItems = rhs.numItems;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		data[i] = rhs.data[i];

	// the rest needs to be filled with the default value for T
	for (int i = numItems; i < _capacity; i++)
		data[i] = T();
}

/**********************************************
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Stack <T> ::Stack(int capacity) throw (const char *)
{
   assert(_capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->_capacity = this->numItems = 0;
	  this->_top = -1;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->_capacity = capacity;
   this->numItems = 0;
   this->_top = -1;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack & rhs)
{
	if (data != NULL)
		delete[] data;

	this->_capacity = rhs._capacity;
	this->_top = rhs._top;
	this->numItems = rhs.numItems;

	try
	{
		data = new T[rhs._capacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new buffer for vector";
	}

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		data[i] = rhs.data[i];

	// the rest needs to be filled with the default value for T
	for (int i = numItems; i < _capacity; i++)
		data[i] = T();

	return *this;
}

template<class T>
T & Stack<T>::top() const throw(const char *)
{
	if (_top == -1)
		throw "ERROR: Unable to reference the element from an empty Stack";
	else
		return data[_top];
}

/***************************************************
 * CONTAINER :: INSERT
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Stack <T> :: push(const T & t) throw (const char *)
{
	// increase the capacity to 1 if there is nothing in it yet
	if (_capacity == 0)
	{
		data = new T[++_capacity];
	}

	// double the capacity if it is already reached
	else if (_capacity == numItems) 
	{								
		_capacity *= 2;
		T * temp = new T[_capacity];
		for (int i = 0; i < numItems; i++)
			temp[i] = data[i];

		for (int i = numItems; i < _capacity; i++)
			temp[i] = T();

		delete[] data;
		data = temp;
	}
   
   // add an item to the end
   data[++_top] = t;
   numItems++;
}

template<class T>
void Stack<T>::pop() throw(const char *)
{
	if (_top == -1)
		throw "ERROR: Unable to pop from an empty Stack";
	else
	{
		_top--;
		this->numItems--;
	}
}


#endif // STACK_H

