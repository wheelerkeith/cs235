/***********************************************************************
* Component:
*    Week 10, Map
*    Brother Helfrich, CS 235
* Author:
*
* Summary:
*
************************************************************************/

#ifndef MAP_H
#define MAP_H

#include "bst.h"
#include "pair.h"

template <class K , class V>
class MapIterator;

template <class K, class V>
class Map
{
public:
	/*    CONSTRUCTORS && DESTRUCTORS    */
	Map() {};
	Map(Map<K, V>& rhs) { this->tree = rhs.tree; }
	~Map() { clear(); }

	/*        OVERLOADED OPERATORS       */
	void operator=(Map<K, V>& rhs) { this->tree = rhs.tree; }
	V& operator[](const K& key);

	/*              METHODS              */
	bool empty() { return tree.root == NULL; }
	int size() { return tree.root->size(); }
	void clear() { deleteBinaryTree(tree.root); }
	MapIterator<K, V>& find(const K& key);
	MapIterator<K, V>& begin();
	MapIterator<K, V>& end();
	MapIterator<K, V>& rbegin();
	MapIterator<K, V>& rend();

private:
	/*               DATA                */
	BST<Pair<K, V> > tree;
	MapIterator<K, V> it;
};

template <class K, class V>
class MapIterator
{
public:
	MapIterator() { BSTIterator<Pair<K, V> > temp; it = temp; }
	MapIterator(BSTIterator<Pair<K, V> > rhs) { this->it = rhs; }

	MapIterator<K, V>& operator=(const MapIterator<K, V>& rhs) {	this->it = rhs.it; return *this; }
	MapIterator<K, V>& operator=(const BSTIterator<Pair<K, V> >& rhs) { this->it = rhs; return *this; }
	bool operator==(MapIterator<K, V>& rhs) { return this->it == it; }
	bool operator==(BSTIterator<Pair<K, V> >& rhs) { return this->it == it; }
	bool operator!=(MapIterator<K, V>& rhs) { return !(this->it == it); }
	V& operator*() { return (*it).second; }
	MapIterator<K, V>& operator--() { --it; return *this; }
	MapIterator<K, V>& operator--(int) { --it; return *this; }
	MapIterator<K, V>& operator++() { ++it; return *this; }
	MapIterator<K, V>& operator++(int) { ++it; return *this; }

private:
	BSTIterator<Pair<K, V> > it;
};

template <class K, class V>
V& Map<K, V>::operator[](const K& key)
{
	// create a pair (with a default value) that we will search for
	Pair<K,V> pair(key, V());

	// find the item
	BSTIterator<Pair<K,V> > it = tree.find(pair);

	// if it is not found, create a new node and put it there
	if (end() == it)
	{
		tree.insert(pair);
		it = tree.find(pair);
	}

	// return the second
	return (*it).second;
}

template<class K, class V>
MapIterator<K, V>& Map<K, V>::find(const K & key)
{
	Pair<K, V> pair(key, V());

	BSTIterator<Pair<K, V> > temp = tree.find(pair);
	it = temp;
	return it;
}

template<class K, class V>
MapIterator<K, V>& Map<K, V>::begin()
{
	BSTIterator<Pair<K, V> > temp = tree.begin();
	it = temp;
	return it;
}

template<class K, class V>
MapIterator<K, V>& Map<K, V>::end()
{
	BSTIterator<Pair<K, V> > temp = tree.end();
	it = temp;
	return it;
}

template<class K, class V>
MapIterator<K, V>& Map<K, V>::rbegin()
{
	BSTIterator<Pair<K, V> > temp = tree.rbegin();
	it = temp;
	return it;
}

template<class K, class V>
MapIterator<K, V>& Map<K, V>::rend()
{
	BSTIterator<Pair<K, V> > temp = tree.rend();
	it = temp;
	return it;
}

#endif //MAP_H
