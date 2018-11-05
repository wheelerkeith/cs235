/***********************************************************************
* Header:
*    Deque
* Summary:
*    This class builds a deque, letting the user dynamically store
*     data. It can be accessed front and back, pushing and popping
*     from either end
*
************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H
#include <iostream> //for error checking
#include <cassert>
#include <cstddef> // for NULL
#include <new> //for bad_alloc

/************************************************
 * Deque
 * A first in first out container
 ***********************************************/
template <class T>
class Deque
{
public:
  /*~~~~~~~~~CONSTRUCTORS~~~~~~~~~*/
  // default constructor//
  Deque() : numItems(0), dCapacity(0), dFront(0), dBack(-1), data(NULL) {}
  // copy constructor
  Deque(const Deque & rhs) throw (const char *);
  // non-default constructor : pre-allocate
  Deque(int dCapacity) throw (const char *);
  // destructor : free everything
  ~Deque() { if (dCapacity) delete [] data; }

  /*~~~~~~~~~~~Methods~~~~~~~~~~~~~*/
  //Does the equivalent of the push_back function, adds to back
  void push_front(const T & incomingData) throw (const char *);
  //Does the equivalent of the push_back function, adds to back
  void push_back(const T & incomingData) throw (const char *);
  //pops off the first data
  void pop_front() throw (const char *);
  //pops off the last data
  void pop_back() throw (const char *);
  //this will reallocate the stack, other functions need it.
  void reallocate() throw(const char *);

  // is the container currently empty?
  bool empty() const  { return numItems == 0;         }
  // remove all the items from the container
  void clear()        { dFront = 0; dBack = -1; numItems = 0; }
  // how many items are currently in the container?
  int size() const    { return numItems;              }
  //returns the potential capacity
  int capacity() const { return dCapacity;  }
  //returns the front value. Value is edittable
  T & front() throw(const char *)
  {
    if (numItems > 0) return data[dFront];
    else throw"ERROR: unable to access data from an empty deque";
  }
  //returns the back data. Value is edittable
  T & back() throw(const char *)
  {
    if (numItems > 0) return data[dBack];
    else throw"ERROR: unable to access data from an empty deque";
  }
  /*~~~~~~~~~~~~Assignment Operators~~~~~~~~~~~~~~~~~*/
  //The const version of returning data at one index
  T & operator [](const int & index) const throw (const char *);
  //the non-const version of above
  T & operator [](int & index) throw (const char *);
  //the assignment operator overloaded.
  Deque & operator =(const Deque <T> & rhs) throw (const char *);


private:
  int numItems;      // how many are in there.
  int dFront;        // where is the front of the deque?
  int dBack;         // where is the back of the deque?
   T * data;          // what is in the deque.
   int dCapacity;     // deque capacity, how many can it hold?

};

/*******************************************
 * Deque :: COPY CONSTRUCTOR
 * This just copies the data. Same we've been
 *  using
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
{
   assert(rhs.dCapacity >= 0);

   // do nothing if there is nothing to do
   if (rhs.dCapacity == 0)
   {
      dCapacity = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.dCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the dCapacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.dCapacity);
   dCapacity = rhs.dCapacity;
   numItems = rhs.numItems;
   dBack = rhs.dBack;
   dFront = rhs.dFront;

   // copy the items over one at a time using the assignment operator
   for (int i = dFront, j = 0; j < numItems; i = (i+1) % dCapacity, j++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = (dBack + 1) % dCapacity; i != dFront; i = (i+1)%dCapacity)
      data[i] = T();
}

/**********************************************
 * Deque : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container certain size
 **********************************************/
template <class T>
Deque <T> :: Deque(int newCapacity) throw (const char *)
{
   assert(newCapacity >= 0);

   // do nothing if there is nothing to do
   if (newCapacity == 0)
   {
      this->dCapacity = this->numItems = 0;
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
   this->dCapacity = newCapacity;
   this->numItems = 0;

   //set front and back
   this->dFront = 0;
   this->dBack = -1;

   // initialize the container by calling the default constructor
   for (int i = 0; i < dCapacity; i++)
      data[i] = T();
}

/***************************************************
 * Deque :: Push_back
 * adds an item to the back of the deque. Should
 * there be no room, the deque is reallocated
 **************************************************/
template <class T>
void Deque <T> :: push_back(const  T &incomingData) throw (const char *)
{
  //if it's a default deque, can't multiply zero
  if (dCapacity == 0)
  {
    dCapacity ++;
    try
    {
      data = new T[dCapacity];
    }
    catch (std::bad_alloc)
    {
      throw "ERROR: Unable to allocate buffer";
    }
  }
  //if at capacity, double
  else if (dCapacity == numItems)
  {
    reallocate();
  }
  //deque starts at zero, so it needs to skip doing this once.
  dBack++;
  numItems++;
  dBack %= dCapacity;
  data[dBack] = incomingData;
}

/***************************************************
 * Deque :: Push_front
 * adds an item to the front of the deque. Should
 * there be no room, the deque is reallocated
 **************************************************/
template <class T>
void Deque <T> :: push_front(const  T &incomingData) throw (const char *)
{
  //if it's a default deque, can't multiply zero
  if (dCapacity == 0)
  {
    dCapacity ++;
    try
    {
      data = new T[dCapacity];
    }
    catch (std::bad_alloc)
    {
      throw "ERROR: Unable to allocate buffer";
    }
  }
  //if at capacity, double
  else if (dCapacity == numItems)
  {
    reallocate();
  }
  //deque starts at zero, so it needs to skip doing this once.
  dFront--;
  numItems++;
  //front can't dip below zero
  if (dFront < 0)
    dFront = dCapacity - 1;
  data[dFront] = incomingData;
}
/***************************************************
 * Deque :: Pop_Front
 * removes and item from front of the list.
 **************************************************/
template <class T>
void Deque <T> :: pop_front() throw (const char *)
{
  if (numItems == 0)
    throw "ERROR: unable to pop from the front of empty deque";
  //if it's empty after this, reset it.
  else
  {
    dFront++;
    dFront %= dCapacity;
    numItems--;
  }
}
/***************************************************
 * Deque :: Pop_Back
 * removes and item from the back list.
 **************************************************/
template <class T>
void Deque <T> :: pop_back() throw (const char *)
{
  if (numItems == 0)
    throw "ERROR: unable to pop from the back of empty deque";
  else
  {
    dBack--;
    if (dBack < 0)
      dBack = dCapacity - 1;
    numItems--;
  }
}

/***************************************************
 * Deque :: Reallocate
 * reorders the list, adds memory if needed
 **************************************************/
template <class T>
void Deque <T> :: reallocate() throw(const char *)
{
  //make a temp array to shift everything around if needed.
  T * tempData;
  //expand if needed.
  if (dCapacity == numItems)
    tempData = new T[dCapacity * 2];
  else
    tempData = new T [dCapacity];
  // copies the front now at 0. i is where in the deque
  // j is where in the new array.
  for(int i = dFront, j = 0; j != numItems;
      i = (i + 1) % dCapacity, j++)
  {
    tempData[j] = data[i];
  }
  delete [] data;
  data = tempData;
  dFront = 0;
  dBack = numItems - 1;
  //did we change the size? Then capacity is bigger
  if (dCapacity == numItems)
    dCapacity *= 2;
}
/***************************************************
 * Deque :: Bracket operator
 * Allows brackets to be used. Does use const
 **************************************************/
template <class T>
T & Deque<T>:: operator [](const int & index) const throw (const char *)
{
  if (index <= dCapacity)
  {
    return data[index];
  }
  else
  {
    throw ("ERROR: Invalid index");
  }
}
/***************************************************
 * Deque :: Bracket operator
 * Allows brackets to be used. Doesn't use const
 **************************************************/
template <class T>
T & Deque<T>:: operator [](int & index) throw (const char *)
{
  if (index <= dCapacity)
  {
    return data[index];
  }
  else
  {
    throw ("ERROR: Invalid index");
  }
}
/***************************************************
 * Deque :: Assignment operator
 * Allows different assignments to be equal.
 **************************************************/
template <class T>
Deque<T> & Deque<T>:: operator =(const Deque <T> & rhs) throw (const char *)
{
  assert(rhs.dCapacity >= 0);
  // attempt to allocate
  try
  {
    data = new T[rhs.dCapacity];
  }
  catch (std::bad_alloc)
  {
    throw "ERROR: Unable to allocate buffer";
  }

  // copy over the dCapacity and size
  assert(rhs.numItems >= 0 && rhs.numItems <= rhs.dCapacity);
  dCapacity = rhs.dCapacity;
  numItems = rhs.numItems;

  // copy the items over one at a time using the assignment operator
  for (int i = 0; i < numItems; i++)
    data[i] = rhs.data[i];

     // the rest needs to be filled with the default value for T
  for (int i = numItems; i < dCapacity; i++)
    data[i] = T();
}
#endif // CONTAINER_H
