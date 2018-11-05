/***********************************************************************
* Header:
*    Set
* Summary:
*    This class contains a set which contains data arranged in order
*    but contains no more than one of each item. 
*
*    This will contain the class definition of:
*        Set               : A class that holds stuff
*        SetIterator       : An interator through Set
* Author
*    Nik Huff, Tyler Petersen, Keith Wheeler
************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>

// forward declaration for ContainerIterator
template <class T>
class SetIterator;

/************************************************
 * Set
 * A class that holds stuff
 ***********************************************/
template <class T>
class Set
{
public:
	// default constructor : empty and kinda useless
	Set() : numItems(0), sCapacity(0), data(NULL) {}

	// copy constructor : copy it
	Set(const Set & rhs) throw (const char *);

	// non-default constructor : pre-allocate
	Set(int capacity) throw (const char *);

	// destructor : free everything
	~Set() { if (sCapacity) delete[] data; }

	// is the Set currently empty
	bool empty() const { return numItems == 0; }

	// remove all the items from the Set
	void clear() { numItems = 0; }

	// how many items are currently in the Set?
	int size() const { return numItems; }

	// how many items can the set currently hold?
	int capacity() const { return sCapacity; }

	// add an item to the Set
	void insert(const T & t) throw (const char *);

	// erase an item from the set
	void erase(const SetIterator<T> index);

	// find an item in the set
	SetIterator <T> find(T element);

	//the assignment operator overloaded.
	Set & operator =(const Set <T> & rhs) throw (const char *);

	Set& operator &&(const Set<T>& rhs);

	Set& operator ||(const Set<T>& rhs);
   
   // return an iterator to the beginning of the Set
   SetIterator <T> begin() { return SetIterator<T>(data); }

   // return an iterator to the end of the Set
   SetIterator <T> end() { return SetIterator<T>(data + numItems);}
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int sCapacity;      // how many items can I put on the Container before full?
};

/**************************************************
 * Set ITERATOR
 * An iterator through Set
 *************************************************/
template <class T>
class SetIterator
{
  public:
   // default constructor
	  SetIterator() : p(NULL) {}

   // initialize to direct p to some item
	  SetIterator(T * p) : p(p) {}

   // copy constructor
	  SetIterator(const SetIterator & rhs) { *this = rhs; }

   // assignment operator
   SetIterator & operator = (const SetIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const SetIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator++(int postfix)
   {
	   SetIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/*******************************************
 * Set :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set<T>::Set(const Set<T> & rhs) throw (const char *)
{
   assert(rhs.sCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.sCapacity == 0)
   {
	  sCapacity = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.sCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.sCapacity);
   sCapacity = rhs.sCapacity;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < sCapacity; i++)
      data[i] = T();
}

/**********************************************
 * Set : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Set<T>::Set(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->sCapacity = this->numItems = 0;
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
   this->sCapacity = capacity;
   this->numItems = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * Set :: INSERT
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Set<T> :: insert(const T & t) throw (const char *)
{
	// set default value to end of set
	int index = numItems - 1;

   // find index of where item should be (or is)
	int begin = 0;
	int end = numItems - 1;
	int middle = int();

	while (begin <= end)
	{
		middle = (begin + end) / 2;
		// if element is found set index to element don't insert it
		if (t == data[middle])
			return;
		// if element is greater than the one below or less than the one above...
		// this is where it belongs
		else if (t < data[middle + 1] && t > data[middle - 1])
			index = middle;

		if (t < data[middle])
			end = middle - 1;
		else
			begin = middle + 1;
	}

	// increase the capacity to 1 if there is nothing in it yet
	if (sCapacity == 0)
	{
		sCapacity++;
		try
		{
			data = new T[sCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for vector";
		}
		index = 0;
	}
	// double the capacity if it is already reached
	else if (sCapacity == numItems)
	{
		sCapacity *= 2;
		T * temp;
		try
		{
			temp = new T[sCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for vector";
		}

		for (int i = 0; i < numItems; i++)
			temp[i] = data[i];

		for (int i = numItems; i < sCapacity; i++)
			temp[i] = T();

		delete[] data;
		data = temp;
	}

	for (int i = index; i < numItems; i++)
           data[i + 1] = data[i];	
	data[index] = t;
	numItems++;
}

template<class T>
void Set<T>::erase(const SetIterator<T> index)
{
	for (SetIterator<T> it = index; it != index + numItems; it++)
		*it = *(it + 1); 
}

template<class T>
SetIterator<T> Set<T>::find(T element)
{
	// using binary search to find element
	int begin = 0;
	int end = numItems - 1;
	int middle = int();

	while (begin <= end)
	{
		middle = (begin + end) / 2;
		if (element == data[middle])
			// return iterator of found element
			return SetIterator<T>(data + middle);
		
		if (element < data[middle])
			end = middle--;
		else
			begin = middle++;
	}

	// return end() if element is not in set
1	return Set<T>::end();
}

/***************************************************
* Set :: Assignment operator
* Allows different assignments to be equal.
**************************************************/
template <class T>
Set<T>& Set<T>::operator=(const Set <T> & rhs) throw (const char *)
{
	assert(rhs.sCapacity >= 0);
	// attempt to allocate
	try
	{
		data = new T[rhs.sCapacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the dCapacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.sCapacity);
	sCapacity = rhs.sCapacity;
	numItems = rhs.numItems;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		data[i] = rhs.data[i];

	// the rest needs to be filled with the default value for T
	for (int i = numItems; i < sCapacity; i++)
		data[i] = T();
}

/***************************************************
* Set :: Intersection
* Returns a set that includes intersecting elements
**************************************************/
template <class T>
Set<T>& Set<T>::operator&&(const Set <T> & rhs)
{
	int iRhs = 0;
	int iThis = 0;
	Set<T> intersection;

	while (iRhs < rhs.numItems || iThis < this->numItems)
	{
		if (iRhs == rhs.numItems)
			intersection.insert(this->data[iThis++]);
		else if (iThis == this->numItems)
			intersection.insert(rhs.data[iRhs++]);
		else if (rhs.data[iRhs] == this->data[iThis])
		{
			intersection.insert(rhs.data[iRhs]);
			iRhs++;
			iThis++;
		}
		else if (rhs.data[iRhs] < this->data[iThis])
			iRhs++;
		else
			iThis++;
	}

	return intersection;
}

/***************************************************
* Set :: Union
* Returns a set including all elements from both sets
**************************************************/
template <class T>
Set<T>& Set<T>::operator||(const Set <T> & rhs)
{
	int iRhs = 0;
	int iThis = 0;
	Set<T> u;

	while (iRhs < rhs.numItems || iThis < this->numItems)
	{
		if (iRhs == rhs.numItems)
			return u;
		else if (iThis == this->numItems)
			return u;
		else if (rhs.data[iRhs] == this->data[iThis])
		{
			u.insert(rhs.data[iRhs]);
			iRhs++;
			iThis++;
		}
		else if (rhs.data[iRhs] < this->data[iThis])
			u.insert(rhs.data[iRhs++]);
		else
			u.insert(this->data[iThis++]);
	}

	return u;
}


#endif // SET_H

