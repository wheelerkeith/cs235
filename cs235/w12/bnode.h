#ifndef BNODE_H
#define BNODE_H

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
class BinaryNode
{
public:
	/*    CONSTRUCTORS && DESTRUCTORS    */
	// default constructor
	BinaryNode() : data(T()), pLeft(NULL), pRight(NULL), pParent(NULL) {}
	// non-default constructor
	BinaryNode(T nData) : data(nData), pLeft(NULL), pRight(NULL), pParent(NULL) {}

	/*              METHODS              */
	void addLeft(T nData);
	void addRight(T nData);
	void addLeft(BinaryNode<T> * n1);
	void addRight(BinaryNode<T> * n1);
	int size() const
	{
		if (this == NULL)
			return 0;
		else 
			return 1 +
				(pLeft == NULL ? 0 : pLeft->size()) +
				(pRight == NULL ? 0 : pRight->size());
	}

	/*                DATA               */
	T data;          // what is in the node.
	int _size;
	BinaryNode * pLeft;	  //left child node
	BinaryNode * pRight;    //right child node
	BinaryNode * pParent;   //what was the previous?
};

/**********************************************************************
* OPERATOR <<
* overloads << to display the entire linked list.
***********************************************************************/
template <class T>
ostream& operator << (ostream & out, BinaryNode<T>* n)
{
	if (n != NULL) //anchor
	{
		out << n->pLeft;
		out << n->data << " ";
		out << n->pRight;
	}

	return out;
}

/**********************************************************************
* DELETEBINARYTREE
* destroys a binary tree, freeing the memory (EXTERMINATE)
***********************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode<T>*& n1)
{
	if (n1 != NULL)
	{
		deleteBinaryTree(n1->pLeft);
		deleteBinaryTree(n1->pRight);
		n1 = NULL;
		delete n1;
	}
}

/**********************************************************************
* ADDLEFT
* Adds a new node to the left of the parent
***********************************************************************/
template <class T>
void BinaryNode<T>::addLeft(T nData)
{
	BinaryNode<T> * node = new  BinaryNode<T>(nData);
	node->pParent = this;
	this->pLeft = node;
}
/**********************************************************************
* ADDRIGHT
* Adds a new node to the right of the parent
***********************************************************************/
template <class T>
void BinaryNode<T>::addRight(T nData)
{
	BinaryNode<T> * node = new  BinaryNode<T>(nData);
	node->pParent = this;
	this->pRight = node;
}

/**********************************************************************
* ADDLEFT
* Adds a new node to the left of the parent
***********************************************************************/
template <class T>
void BinaryNode<T>::addLeft(BinaryNode<T> * node)
{
	if (node == NULL)
	{
		this->pLeft = NULL;
	}
	else
	{
		node->pParent = this;
		this->pLeft = node;
	}
}
/**********************************************************************
* ADDRIGHT
* Adds a new node to the right of the parent
***********************************************************************/
template <class T>
void BinaryNode<T>::addRight(BinaryNode<T> * node)
{
	if (node == NULL)
	{
		this->pRight = NULL;
	}
	else
	{
		node->pParent = this;
		this->pRight = node;
	}
}

#endif // BNODE_H
