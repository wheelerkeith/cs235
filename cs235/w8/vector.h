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

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// forward declaration for ContainerIterator
template <class T>
class VectorIterator;

/************************************************
 * CONTAINER
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), _capacity(0), data(NULL) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (_capacity) delete [] data; }

   // overload assignment operator
   Vector<T> & operator = (const Vector & rhs);

   // overload []
   T& operator [] (int index) { return data[index]; }

   // overload [] const
   T& operator [] (int index) const { return data[index]; }

   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // how many items can I put in the vector?
   int capacity() const { return _capacity;			   }

   // add an item to the container
   void push_back(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
   VectorIterator<T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator<T> end() { return VectorIterator<T>(data + numItems);}

   
private:
   int _capacity;      // how many items can I put on the Container before full?
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
  
};

/**************************************************
 * VectorIterator
 * An iterator through Vector
 *************************************************/
template <class T>
class VectorIterator
{
  public:
   // default constructor
	  VectorIterator() : p(NULL) {}

   // initialize to direct p to some item
	  VectorIterator(T * p) : p(p) {}

   // copy constructor
	  VectorIterator(const VectorIterator & rhs) { *this = rhs; }

   // assignment operator
	  VectorIterator & operator = (const VectorIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // equals operator
   bool operator == (const VectorIterator & rhs) const
   {
	   return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
	   VectorIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * CONTAINER :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> ::Vector(const Vector <T> & rhs) throw (const char *)
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
   
   // copy over the capacity and size
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

/**********************************************
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Vector <T> ::Vector(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->_capacity = this->numItems = 0;
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

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector & rhs)
{
	this->_capacity = rhs._capacity;
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

/***************************************************
 * CONTAINER :: INSERT
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
{
	// increase the capacity to 1 if there is nothing in it yet
	if (_capacity == 0)
	{
		_capacity++;
		try
		{
			data = new T[_capacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for vector";
		}
	}

	// double the capacity if it is already reached
	else if (_capacity == numItems)
	{
		_capacity *= 2;
		T * temp;
		try
		{
			temp = new T[_capacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for vector";
		}

		for (int i = 0; i < numItems; i++)
			temp[i] = data[i];

		for (int i = numItems; i < _capacity; i++)
			temp[i] = T();

		delete[] data;
		data = temp;
	}
   
   // add an item to the end
   data[numItems++] = t;
}


#endif // VECTOR_H

