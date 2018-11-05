

/***********************************************************************
* Header:
*    Queue
* Summary:
*    This class builds a queue, letting the user dynamically store
*     data. It has problems with strings.
*
*    This will contain the class definition of:
*        queue         : A class that holds stuff
*        queueIterator : An interator through Queue
* Author
*    Tyler Petersen
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream> //for error checking
#include <cassert>
#include <cstddef> // for NULL
#include <new> //for bad_alloc

/************************************************
 * Queue
 * A first in first out container
 ***********************************************/
template <class T>
class Queue
{
public:
  // default constructor
  Queue() : numItems(0), _capacity(0), _front(0), _back(-1), data(NULL) {}
  // copy constructor
  Queue(const Queue & rhs) throw (const char *);
  // non-default constructor : pre-allocate
  Queue(int _capacity) throw (const char *);
  // destructor : free everything
  ~Queue() { if (_capacity) delete [] data; }


  //Does the equivalent of the push function, adds to back
  void push(const T & incomingData) throw (const char *);
  //pops off the first data
  void pop() throw (const char *);
  //this will reallocate the stack, other functions need it.
  void reallocate() throw(const char *);


  // is the container currently empty?
  bool empty() const  { return numItems == 0;         }
  // remove all the items from the container
  void clear()        { _front = 0; _back = -1; numItems = 0; }
  // how many items are currently in the container?
  int size() const    { return numItems;              }
  //returns the potential capacity
  int capacity() const { return _capacity;  }

  //returns the front value
  T & front() throw(const char *)
  {
    if (numItems > 0) return data[_front];
    else throw"ERROR: attempting to access an item in an empty queue";
  }
  //returns the back data
  T & back() throw(const char *)
  {
    if (numItems > 0) return data[_back];
    else throw"ERROR: attempting to access an item in an empty queue";
  }
  //The const version of returning data at one index
  T & operator [](const int & index) const throw (const char *);
  //the non-const version of above
  T & operator [](int & index) throw (const char *);
  //the assignment operator overloaded.
  Queue & operator =(const Queue <T> & rhs) throw (const char *);

  int _front;        // where is the front of the queue?
  int _back;         // where is the back of the queue?
  int numItems;      // how many are in there.

private:
   T * data;          // what is in the queue.
   int _capacity;     // queue capacity, how many can it hold?

};

/*******************************************
 * Queue :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
   assert(rhs._capacity >= 0);

   // do nothing if there is nothing to do
   if (rhs._capacity == 0)
   {
      _capacity = numItems = 0;
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

   // copy over the _capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs._capacity);
   _capacity = rhs._capacity;
   numItems = rhs.numItems;
   _back = rhs._back;
   _front = rhs._front;

    // copy the items over one at a time using the assignment operator
   for (int i = _front, j = 0; j < numItems; i = (i+1) % _capacity, j++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = (_back + 1) % _capacity; i != _front; i = (i+1) % _capacity)
      data[i] = T();
}

/**********************************************
 * Queue : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "_capacity"
 **********************************************/
template <class T>
Queue <T> :: Queue(int newCapacity) throw (const char *)
{
   assert(newCapacity >= 0);

   // do nothing if there is nothing to do
   if (newCapacity == 0)
   {
      this->_capacity = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   // copy over the stuff
   this->_capacity = newCapacity;
   this->numItems = 0;

   //set front and back
   this->_front = 0;
   this->_back = -1;

   // initialize the container by calling the default constructor
   for (int i = 0; i < _capacity; i++)
      data[i] = T();
}

/***************************************************
 * Queue :: Push
 * adds an item to the back of the queue. Should
 * there be no room, the queue is reallocated
 **************************************************/
template <class T>
void Queue <T> :: push(const  T &incomingData) throw (const char *)
{
  //if it's a default queue, can't multiply zero
  if (_capacity == 0)
  {
    _capacity ++;
    try
    {
      data = new T[_capacity];
    }
    catch (std::bad_alloc)
    {
      throw "ERROR: Unable to allocate buffer";
    }
  }
  //if at capacity, double
  else if (_capacity == numItems)
  {
    reallocate();
  }
  //queue starts at zero, so it needs to skip doing this once.
  _back++;
  numItems++;
  _back %= _capacity;
  data[_back] = incomingData;
  //error checking below
  //  std::cout << "\n_front = " << _front<< "\n_back = " << _back<< "\n_capacity = " << _capacity<< "\nNumItems = " << numItems;
}
/***************************************************
 * Queue :: Pop
 * removes and item from list.
 **************************************************/
template <class T>
void Queue <T> :: pop() throw (const char *)
{
  if (numItems == 0)
    throw "ERROR: attempting to pop from an empty queue";
  //if it's empty after this, reset it.
  else
  {
    //normal procedure
    _front++;
    _front %= _capacity;
    numItems--;
  }
}

/***************************************************
 * Queue :: Reallocate
 * reorders the list, adds memory if needed
 **************************************************/
template <class T>
void Queue <T> :: reallocate() throw(const char *)
{
  //make a temp array to shift everything around if needed.
  T * tempData;
  //expand if needed.
  if (_capacity == numItems)
    tempData = new T[_capacity * 2];
  else
    tempData = new T [_capacity];
  // copies the front now at 0. i is where in the queue
  // j is where in the new array.
  for(int i = _front, j = 0; j != numItems;
      i = (i + 1) % _capacity, j++)
  {
    tempData[j] = data[i];
  }
  delete [] data;
  data = tempData;
  _front = 0;
  _back = numItems - 1;
  //did we change the size? Then capacity is bigger
  if (_capacity == numItems)
    _capacity *= 2;
}
/***************************************************
 * Queue :: Bracket operator
 * Allows brackets to be used. Does use const
 **************************************************/
template <class T>
T & Queue<T>:: operator [](const int & index) const throw (const char *)
{
  if (index <= _capacity)
  {
    return data[index];
  }
  else
  {
    throw ("ERROR: Invalid index");
  }
}
/***************************************************
 * Queue :: Bracket operator
 * Allows brackets to be used. Doesn't use const
 **************************************************/
template <class T>
T & Queue<T>:: operator [](int & index) throw (const char *)
{
  if (index <= _capacity)
  {
    return data[index];
  }
  else
  {
    throw ("ERROR: Invalid index");
  }
}
/***************************************************
 * Queue :: Assignment operator
 * Allows different assignments to be equal.
 **************************************************/
template <class T>
Queue<T> & Queue<T>:: operator =(const Queue <T> & rhs) throw (const char *)
{
  assert(rhs._capacity >= 0);
  // attempt to allocate
  try
  {
    data = new T[rhs._capacity];
  }
  catch (std::bad_alloc)
  {
    throw "ERROR: Unable to allocate buffer";
  }

  // copy over the _capacity and size
  assert(rhs.numItems >= 0 && rhs.numItems <= rhs._capacity);
  _capacity = rhs._capacity;
  numItems = rhs.numItems;

  // copy the items over one at a time using the assignment operator
  for (int i = 0; i < numItems; i++)
    data[i] = rhs.data[i];

     // the rest needs to be filled with the default value for T
  for (int i = numItems; i < _capacity; i++)
    data[i] = T();
}

#endif // CONTAINER_H
