#ifndef HASH_H
#define HASH_H

#include <list>
#include <vector>

using namespace std;


template <class T>
class Hash
{
public:
	Hash() : _size(0) { table(0); }
	Hash(int size);
	Hash(const Hash& rhs) { table = rhs.table; _size = rhs._size; }
	~Hash() {};

	Hash<T>& operator=(Hash& rhs);

	bool empty() { return _size == 0; }
	int size() { return _size; }
	int capacity() const { return table.capacity(); }
	void clear() { table.clear(); }
	bool find(const T& value);
	void insert(const T& value);
    virtual int hash(const T& value) const = 0;

private:
	vector<list<T> > table;
	int _size;
};

template<class T>
Hash<T>::Hash(int size)
{
	vector<list<T> > temp(size);
	table = temp;
	_size = 0;
}

template <class T>
Hash<T>& Hash<T>::operator=(Hash& rhs)
{
	// reset size of container - will increase with insert
	_size = 0;
	// clear of current contents
	for (int i = 0; i < capacity(); i++)
		table[i].clear();

	// put rhs contents into temporary vector
	vector<T> temp;
	for (int i = 0; i < rhs.capacity(); i++)
	{
		// iterate through each list and retrieve all values
		typename list<T>::iterator it;
		for (it = rhs.table[i].begin(); it != rhs.table[i].end(); it++)
			temp.push_back(*it);
	}

	// insert temp contents into this
	for (int i = 0; i < temp.size(); i++)
		insert(temp[i]);

	return *this;
}

template<class T>
bool Hash<T>::find(const T & value)
{
	int index = hash(value);
	bool found = false;
	typename list<T>::iterator it;
	for (it = table[index].begin(); it != table[index].end(); it++)
		if (*it == value)
			found = true;

	return found;
}

template<class T>
void Hash<T>::insert(const T & value)
{
	int index = hash(value);
	table[index].insert(table[index].end(), value);
	_size++;
}

#endif
