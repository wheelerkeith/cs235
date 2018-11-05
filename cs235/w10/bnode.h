#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cstddef>
#include <new>
using namespace std;

enum Color { red, black };

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
	BinaryNode() : data(T()), pLeft(NULL), pRight(NULL), pParent(NULL),
		pGrandparent(NULL), pSibling(NULL), pAunt(NULL), nColor(red) {}
	// non-default constructor
	BinaryNode(T nData) : data(nData), pLeft(NULL), pRight(NULL), pParent(NULL),
		pGrandparent(NULL), pSibling(NULL), pAunt(NULL), nColor(red) {}

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

	/*         RED-BLACK METHODS         */
	/*int findDepth() const;
	int depth;
	void verifyBTree() const;
	void verifyRedBlack(int depth) const;
	bool isRed() { return nColor == red; }
	bool isBlack() { return nColor == black; }*/

	/*                DATA               */
	T data;          // what is in the node.
	int _size;
	BinaryNode * pLeft;	  //left child node
	BinaryNode * pRight;    //right child node
	BinaryNode * pParent;   //what was the previous?
	BinaryNode * pGrandparent;
	BinaryNode * pSibling;
	BinaryNode * pAunt;
	Color nColor;
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
	if (this->pParent != NULL)
	{
		node->pGrandparent = this->pParent;
		if (this == this->pParent->pLeft && this->pParent->pRight != NULL)
			node->pAunt = this->pParent->pRight;
		if (this == this->pParent->pRight && this->pParent->pLeft != NULL)
			node->pAunt = this->pParent->pLeft;
	}

	if (this->pRight != NULL)
		node->pSibling = this->pRight;

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
	if (this->pParent != NULL)
	{
		node->pGrandparent = this->pParent;
		if (this == this->pParent->pLeft && this->pParent->pRight != NULL)
			node->pAunt = this->pParent->pRight;
		if (this == this->pParent->pRight && this->pParent->pLeft != NULL)
			node->pAunt = this->pParent->pLeft;
	}

	if (this->pLeft != NULL)
		node->pSibling = this->pLeft;

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
		if (this->pParent != NULL)
		{
			node->pGrandparent = this->pParent;
			if (this == this->pParent->pLeft && this->pParent->pRight != NULL)
				node->pAunt = this->pParent->pRight;
			if (this == this->pParent->pRight && this->pParent->pLeft != NULL)
				node->pAunt = this->pParent->pLeft;
		}

		if (this->pRight != NULL)
			node->pSibling = this->pRight;

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
		if (this->pParent != NULL)
		{
			node->pGrandparent = this->pParent;
			if (this == this->pParent->pLeft && this->pParent->pRight != NULL)
				node->pAunt = this->pParent->pRight;
			if (this == this->pParent->pRight && this->pParent->pLeft != NULL)
				node->pAunt = this->pParent->pLeft;
		}

		if (this->pLeft != NULL)
			node->pSibling = this->pLeft;

		this->pRight = node;
	}
}

// you might want to put these methods into your BinaryNode class
// to help you debug your red-black balancing code

/****************************************************
* BINARY NODE :: FIND DEPTH
* Find the depth of the black nodes. This is useful for
* verifying that a given red-black tree is valid
* Author: Br. Helfrich
****************************************************
template <class T>
int BinaryNode <T> ::findDepth() const
{
	// if there are no children, the depth is ourselves
	if (pRight == NULL && pLeft == NULL)
		return (isRed ? 0 : 1);

	// if there is a right child, go that way
	if (pRight != NULL)
		return (isRed ? 0 : 1) + pRight->findDepth();
	else
		return (isRed ? 0 : 1) + pLeft->findDepth();
}

/****************************************************
* BINARY NODE :: VERIFY RED BLACK
* Do all four red-black rules work here?
* Author: Br. Helfrich
***************************************************
template <class T>
void BinaryNode <T> ::verifyRedBlack(int depth) const
{
	depth -= (isRed == false) ? 1 : 0;

	// Rule a) Every node is either red or black
	assert(isRed == true || isRed == false); // this feels silly

											 // Rule b) The root is black
	if (pParent == NULL)
		assert(isRed == false);

	// Rule c) Red nodes have black children
	if (isRed == true)
	{
		if (pLeft != NULL)
			assert(pLeft->isRed == false);
		if (pRight != NULL)
			assert(pRight->isRed == false);
	}

	// Rule d) Every path from a leaf to the root has the same # of black nodes
	if (pLeft == NULL && pRight && NULL)
		assert(depth == 0);
	if (pLeft != NULL)
		pLeft->verifyRedBlack(depth);
	if (pRight != NULL)
		pRight->verifyRedBlack(depth);
}

/******************************************************
* VERIFY B TREE
* Verify that the tree is correctly formed
* Author: Br. Helfrich
******************************************************
template <class T>
void BinaryNode <T> ::verifyBTree() const
{
	// check parent
	if (pParent)
		assert(pParent->pLeft == this || pParent->pRight == this);

	// check left
	if (pLeft)
	{
		assert(pLeft->data <= data);
		assert(pLeft->pParent == this);
		pLeft->verifyBTree();
	}

	// check right
	if (pRight)
	{
		assert(pRight->data >= data);
		assert(pRight->pParent == this);
		pRight->verifyBTree();
	}
}*/


#endif // BNODE_H
