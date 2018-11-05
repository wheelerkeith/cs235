/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Helfrich, CS 235
 * Author:
 *    
 * Summary:
 *    
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"
#include "stack.h"

// forward definition of iterator
template <class T>
class BSTIterator;

template <class T>
class BST
{
public:
	/*    CONSTRUCTORS && DESTRUCTORS    */
	BST() : root(NULL) {};
	BST(BST<T>& rhs);
	~BST() { deleteBinaryTree(root); }

	/*        OVERLOADED OPERATORS       */
	void operator=(BST<T>& rhs);

	/*              METHODS              */
	bool empty() { return root == NULL; }
	int size() { return root->size(); }
	void clear() { deleteBinaryTree(root); }
	void insert(const T& data);
	void remove(BSTIterator<T>& it) { removeAux(it.node(), it.node()->pParent); }
	BSTIterator<T>& find(const T& data) 
	{ 
		Stack<BinaryNode<T>*> nodes; 
		nodes.push(NULL);
		return findAux(root, nodes, data); 
	}
	BSTIterator<T>& begin();
	BSTIterator<T>& end();
	BSTIterator<T>& rbegin();
	BSTIterator<T>& rend();
	BinaryNode<T>* root;
private:
	/*                DATA               */
	
	BSTIterator<T> it;

	/*          PRIVATE METHODS          */
	BSTIterator<T>& findAux(BinaryNode<T>* subroot, Stack<BinaryNode<T>*>& nodes, const T& data);
	void removeAux(BinaryNode<T>* x, BinaryNode<T>* parent);
};

template <class T>
class BSTIterator
{
public:
	/*    CONSTRUCTORS && DESTRUCTORS    */
	BSTIterator()
	{
		BinaryNode<T>* n = new BinaryNode<T>;
		n = NULL;
		nodes.push(n);
	}
	BSTIterator(BinaryNode<T>* node) { nodes.push(node); }
	BSTIterator(Stack<BinaryNode<T>*> n) { nodes = n; }
	BSTIterator(BSTIterator<T>*& rhs) { this = rhs; }

	/*        OVERLOADED OPERATORS       */
	BSTIterator<T>& operator=(const BSTIterator<T>& rhs) { this->nodes = rhs.nodes; return *this; }
	bool operator==(BSTIterator<T>& rhs) { return (this->nodes.top() == rhs.nodes.top()); }
	bool operator!=(BSTIterator<T>& rhs) { return !(this->nodes.top() == rhs.nodes.top()); }
	const T& operator*() { return nodes.top()->data; }
	BSTIterator<T>& operator--();
	BSTIterator<T>& operator--(int);
	BSTIterator<T>& operator++();
	BSTIterator<T>& operator++(int);

	/*              METHODS              */
	BinaryNode<T>* node() { return nodes.top(); }

private:
	Stack<BinaryNode<T>*> nodes;
};

template<class T>
BST<T>::BST(BST<T>& rhs)
{
	clear();

	BSTIterator <T> it;
	for (it = rhs.begin(); it != rhs.end(); ++it)
		this->insert(*it);
}

template<class T>
void BST<T>::operator=(BST<T>& rhs)
{
	clear();

	BSTIterator <T> it;
	for (it = rhs.begin(); it != rhs.end(); ++it)
		this->insert(*it);
}

template <class T>
void BST<T>::insert(const T& data)
{
	BinaryNode<T>* locptr = root;
	BinaryNode<T>* parent = 0;
	bool found = false;

	while (!found && locptr != 0)
	{
		parent = locptr;
		if (data < locptr->data)
			locptr = locptr->pLeft;
		else if (locptr->data < data)
			locptr = locptr->pRight;
		else
			found = true;
	}

	locptr = new BinaryNode<T>(data);
	if (parent == 0)
		root = locptr;
	else if (data <= parent->data)
		parent->addLeft(locptr);
	else
		parent->addRight(locptr);
}

template<class T>
BSTIterator<T>& BST<T>::findAux(BinaryNode<T>* subroot, Stack<BinaryNode<T>*>& nodes, const T& data)
{
	if (subroot == NULL)
		return end();
	else if (data < subroot->data)
	{
		nodes.push(subroot);
	    findAux(subroot->pLeft, nodes, data);
	}
	else if (subroot->data < data)
	{
		nodes.push(subroot);
		findAux(subroot->pRight, nodes, data);
	}
	else
	{
		nodes.push(subroot);
		BSTIterator<T> temp(nodes);
		it = temp;
		return it;
	}
}

template<class T>
void BST<T>::removeAux(BinaryNode<T>* x, BinaryNode<T>* parent)
{
	// node to be deleted has two children
	if (x->pLeft != NULL && x->pRight != NULL)
	{
		// find x's in order successor and its parent
		BinaryNode<T>* xSucc = x->pRight;
		parent = x;
		while (xSucc->pLeft != NULL) 
		{
			parent = xSucc;
			xSucc = xSucc->pLeft;
		}

		// move contents of xSucc to x and change x
		// to point to successor
		x->data = xSucc->data;
		x = xSucc;
	}

	// case where node has 0 or 1 child
	BinaryNode<T>* subtree = x->pLeft;
	if (subtree == NULL)
		subtree = x->pRight;
	if (parent == NULL)
		root = subtree;
	else if (parent->pLeft == x)
		parent->pLeft = subtree;
	else
		parent->pRight = subtree;
	delete x;
}

template<class T>
BSTIterator<T>& BST<T>::begin()
{
	BinaryNode<T>* n = root;
	Stack<BinaryNode<T>*> nodes;
	nodes.push(NULL);

	while (n != NULL)
	{
		nodes.push(n);
		n = n->pLeft;
	}

	BSTIterator<T> temp(nodes);
	it = temp;
	return it;
}

template<class T>
BSTIterator<T>& BST<T>::end()
{
	BSTIterator<T> temp(NULL);
	it = temp;
	return it;
}

template<class T>
BSTIterator<T>& BST<T>::rbegin()
{
	BinaryNode<T>* n = root;
	Stack<BinaryNode<T>*> nodes;
	nodes.push(NULL);

	while (n != NULL)
	{
		nodes.push(n);
		n = n->pRight;
	}

	BSTIterator<T> temp(nodes);
	it = temp;
	return it;
}

template<class T>
BSTIterator<T>& BST<T>::rend()
{
	BSTIterator<T> temp(NULL);
	it = temp;
	return it;
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
BSTIterator<T>& BSTIterator<T>::operator--()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

template <class T>
BSTIterator<T>& BSTIterator<T>::operator--(int)
{
	// do nothing if we have nothing
	if (nodes.top() == NULL)
		return *this;

	// if there is a left node, take it
	if (nodes.top()->pLeft != NULL)
	{
		nodes.push(nodes.top()->pLeft);

		// there might be more right-most children
		while (nodes.top()->pRight)
			nodes.push(nodes.top()->pRight);
		return *this;
	}

	// there are no left children, the right are done
	assert(nodes.top()->pLeft == NULL);
	BinaryNode <T> * pSave = nodes.top();
	nodes.pop();

	// if the parent is the NULL, we are done!
	if (NULL == nodes.top())
		return *this;

	// if we are the right-child, got to the parent.
	if (pSave == nodes.top()->pRight)
		return *this;

	// we are the left-child, go up as long as we are the left child!
	while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
	{
		pSave = nodes.top();
		nodes.pop();
	}

	return *this;
}

template <class T>
BSTIterator<T>& BSTIterator<T>::operator++()
{
	// do nothing if we have nothing
	if (nodes.top() == NULL)
		return *this;

	// if there is a right node, take it
	if (nodes.top()->pRight != NULL)
	{
		nodes.push(nodes.top()->pRight);

		// there might be more left-most children
		while (nodes.top()->pLeft)
			nodes.push(nodes.top()->pLeft);
		return *this;
	}

	// there are no right children, the left are done
	assert(nodes.top()->pRight == NULL);
	BinaryNode <T> * pSave = nodes.top();
	nodes.pop();

	// if the parent is the NULL, we are done!
	if (NULL == nodes.top())
		return *this;

	// if we are the left-child, got to the parent.
	if (pSave == nodes.top()->pLeft)
		return *this;

	// we are the right-child, go up as long as we are the right child!
	while (nodes.top() != NULL && pSave == nodes.top()->pRight)
	{
		pSave = nodes.top();
		nodes.pop();
	}

	return *this;
}

template <class T>
BSTIterator<T>& BSTIterator<T>::operator++(int)
{
	// do nothing if we have nothing
	if (nodes.top() == NULL)
		return *this;

	// if there is a right node, take it
	if (nodes.top()->pRight != NULL)
	{
		nodes.push(nodes.top()->pRight);

		// there might be more left-most children
		while (nodes.top()->pLeft)
			nodes.push(nodes.top()->pLeft);
		return *this;
	}

	// there are no right children, the left are done
	assert(nodes.top()->pRight == NULL);
	BinaryNode <T> * pSave = nodes.top();
	nodes.pop();

	// if the parent is the NULL, we are done!
	if (NULL == nodes.top())
		return *this;

	// if we are the left-child, got to the parent.
	if (pSave == nodes.top()->pLeft)
		return *this;

	// we are the right-child, go up as long as we are the right child!
	while (nodes.top() != NULL && pSave == nodes.top()->pRight)
	{
		pSave = nodes.top();
		nodes.pop();
	}

	return *this;
}

#endif // BST_H