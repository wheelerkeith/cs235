/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "stack.h"

namespace custom
{

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
   // constructors, destructor, assignment operator
   BST() : root(NULL)                {                                    }
   BST(const BST & rhs)               throw (const char *);
  ~BST()                             { clear();                           }
   BST & operator = (const BST & rhs) throw (const char *);

   // standard container interfaces
   bool empty() const                { return root == NULL;               }
   int  size() const                 { return empty() ? 0 : root->size(); }
   void clear()
   {
      if (root)
         deleteBinaryTree(root);
      assert(empty());
   }

   // nested node class
   class BinaryNode;

   // iterators
   class iterator;
   iterator begin();
   iterator end()             { return iterator (NULL); }
   iterator rbegin();
   iterator rend()            { return iterator (NULL); }

   // BST specific interfaces
   void insert(const T & t) throw (const char * );
   void remove(iterator  & it);
   iterator find(const T & t);

private:
   // delete a single node from the tree
   void deleteNode (BinaryNode * & pDelete, bool toRight);
   void deleteBinaryTree(BinaryNode * & pDelete);
   void copyBinaryTree(const BinaryNode * pSrc,
                       BinaryNode * pDest) throw (const char *);

   BinaryNode * root;
};


/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BST <T> :: BinaryNode
{
public:
   // constructor: set the pointers to NULL
   BinaryNode()            : pLeft(NULL), pRight(NULL), pParent(NULL),
      data()  {}
   BinaryNode(const T & t) : pLeft(NULL), pRight(NULL), pParent(NULL),
      data(t) {}

   // size
   int size() const
   {
      return 1 +
         (pLeft== NULL? 0 : pLeft->size()) +
         (pRight == NULL ? 0 : pRight->size());
   }

   // add a node the left/right
   void addLeft (BinaryNode * pNode);
   void addRight(BinaryNode * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);

   // since no validation is done, everything is public
   BinaryNode  * pLeft;
   BinaryNode  * pRight;
   BinaryNode  * pParent;

   // the data of unknown type: cannot validate so is public
   T data;
};

/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
void BST <T> :: BinaryNode :: addLeft (BinaryNode * pNode)
{
   pLeft = pNode;
   if (pNode)
      pNode->pParent = this;
}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
void BST <T> :: BinaryNode :: addRight (BinaryNode * pNode)
{
   pRight = pNode;
   if (pNode)
      pNode->pParent = this;
}


/******************************************************
 * BINARY NODE :: ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
void BST <T> :: BinaryNode :: addLeft (const T & t) throw (const char *)
{
   try
   {
      BinaryNode * pNode = new BinaryNode (t);
      pLeft = pNode;
      if (pNode)
         pNode->pParent = this;
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/******************************************************
 * BINARY NODE :: ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
void BST <T> :: BinaryNode :: addRight (const T & t) throw (const char *)
{
   try
   {
      BinaryNode * pNode = new BinaryNode (t);
      pRight = pNode;
      if (pNode)
         pNode->pParent = this;
   }
   catch (...)
   {
         throw "ERROR: Unable to allocate a node";
   }
}

/*****************************************************
 * DELETE BINARY TREE
 * Delete all the nodes below pThis including pThis
 * using postfix traverse: LRV
 ****************************************************/
template <class T>
void BST <T> :: deleteBinaryTree(BinaryNode * & pDelete)
{
   if (pDelete == NULL)
      return;
   deleteBinaryTree(pDelete->pLeft);
   deleteBinaryTree(pDelete->pRight);
   delete pDelete;
   pDelete = NULL;
}

/**********************************************
 * COPY BINARY TREE
 * Copy pSrc->pRight to pDest->pRight and
 * pSrc->pLeft onto pDest->pLeft
 *********************************************/
template <class T>
void BST <T> :: copyBinaryTree(const BinaryNode * pSrc,
                                     BinaryNode * pDest) throw (const char *)
{
   assert(pSrc && pDest);

   if (pSrc->pRight)
   {
      pDest->addRight(pSrc->pRight->data);
      copyBinaryTree(pSrc->pRight, pDest->pRight);
   }
   if (pSrc->pLeft)
   {
      pDest->addLeft(pSrc->pLeft->data);
      copyBinaryTree(pSrc->pLeft, pDest->pLeft);
   }
}

/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BST <T> :: iterator
{
public:
   // constructors and assignment
   iterator(BinaryNode * p = NULL)     { nodes.push(p);     }
   iterator(stack <BinaryNode  *> & s) { nodes = s;         }
   iterator(const iterator & rhs)      { nodes = rhs.nodes; }
   iterator & operator = (const iterator & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const iterator & rhs) const
   {
      // only need to compare the leaf node
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const iterator & rhs) const
   {
      // only need to compare the leaf node
      return rhs.nodes.const_top() != nodes.const_top();
   }

   // de-reference. Cannot change because it will invalidate the BST
   const T & operator * () const
   {
      return nodes.const_top()->data;
   }

   // iterators
   iterator & operator ++ ();
   iterator   operator ++ (int postfix)
   {
      iterator itReturn = *this;
      ++(*this);
      return itReturn;
   }
   iterator & operator -- ();
   iterator   operator -- (int postfix)
   {
      iterator itReturn = *this;
      --(*this);
      return itReturn;
   }

   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> :: remove(iterator & it);

private:

   // get the node pointer
   BinaryNode * getNode() { return nodes.top(); }

   // the stack of nodes
   stack < BinaryNode * > nodes;
};


/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
typename BST <T> :: iterator custom :: BST <T> :: begin()
{
   stack < BinaryNode * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);

   return iterator (nodes);
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
typename BST <T> :: iterator  BST <T> :: rbegin()
{
   stack < BinaryNode * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return iterator (nodes);
}

/*********************************************
 * BST :: COPY CONSTRUCTOR
 * Copy one tree to another
 ********************************************/
template <class T>
BST <T> :: BST ( const BST <T> & rhs) throw (const char *) : root(NULL)
{
   *this = rhs;
}

/**********************************************
 * BST :: COPY
 * Make a copy of a binary search tree
 **********************************************/
template <class T>
BST <T> & BST <T> :: operator = (const BST <T> & rhs) throw (const char *)
{
   clear();
   if (rhs.root != NULL)
   {
      try
      {
         this->root = new BinaryNode (rhs.root->data);
         copyBinaryTree(rhs.root, this->root);
      }
      catch (...)
      {
         throw "ERROR: Unable to allocate a node";
      }
   }
   return *this;
}

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
   try
   {
      // if we are at a trivial state (empty tree), then create a new root
      if (root == NULL)
      {
         root = new BinaryNode (t);
         return;
      }

      // otherwise, go a searching for the correct spot
      BinaryNode * node = root;
      bool done = false;
      while (!done)
      {
         // if the center node is larger, go left
         if (node->data > t)
         {
            // if there is a node to the left, follow it
            if (node->pLeft)
               node = node->pLeft;
            // if we are at the leaf, then create a new node
            else
            {
               node->addLeft(t);
               done = true;
            }

         }

         // if the center node is smaller, go right
         else
         {
            // if there is a node to the right, follow it
            if (node->pRight)
               node = node->pRight;
            // if we are at the left, then create a new node.
            else
            {
               node->addRight(t);
               done = true;
            }
         }
      }
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: remove(iterator & it)
{
   // find the node
   BinaryNode * pNode = it.getNode();

   // do nothing if there is nothing to do
   if (pNode == NULL)
      return;

   // if there is only one child (right) or no children (how sad!)
   if (pNode->pLeft == NULL)
      deleteNode(pNode, true /* goRight */);

   // if there is only one child (left)
   else if (pNode->pRight == NULL)
      deleteNode(pNode, false /* goRight */);

   // otherwise, swap places with the in-order successor
   else
   {
      // find the in-order successor
      BinaryNode * pNodeIOS = pNode->pRight;
      while (pNodeIOS->pLeft != NULL)
         pNodeIOS = pNodeIOS->pLeft;

      // copy its data
      pNode->data = pNodeIOS->data;

      // if there are any children under the in-order successor, fix them
      assert(pNodeIOS->pLeft == NULL); // there cannot be a left child or
                                       // I would not be the IOS
      deleteNode(pNodeIOS, true /*goRight*/);

      // prepare for deletion
      pNode = pNodeIOS;
   }

   delete pNode;
}

/****************************************************
 * DELETE NODE
 * Delete a single node (pDelete) from the tree indicated
 * by a node (pDelete).
 *    pDelete     the node to be deleted
 *    toRight     should the right branch inherit our place?
 ****************************************************/
template <class T>
void BST <T> :: deleteNode(BinaryNode * & pDelete, bool toRight)
{
   // shift everything up
   BinaryNode * pNext = (toRight ? pDelete->pRight : pDelete->pLeft);

   // if we are not the parent, hook ourselves into the existing tree
   if (pDelete != root)
   {
      if (pDelete->pParent->pLeft == pDelete)
      {
         pDelete->pParent->pLeft = NULL;
         pDelete->pParent->addLeft(pNext);
      }
      else
      {
         pDelete->pParent->pRight = NULL;
         pDelete->pParent->addRight(pNext);
      }
   }

   // otherwise, the pNext is the new root
   else
   {
      root = pNext;
      pNext->pParent = NULL;
   }
}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: find(const T & t)
{
   stack < BinaryNode * > nodesFound;

   nodesFound.push(root);

   // non-recurive solution
   while (nodesFound.top() != NULL)
   {
      if (nodesFound.top()->data == t)
         return nodesFound;
      if (nodesFound.top()->data > t)
         nodesFound.push(nodesFound.top()->pLeft);
      else
         nodesFound.push(nodesFound.top()->pRight);
   }

   return iterator ();
}

/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator ++ ()
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
   BinaryNode * pSave = nodes.top();
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

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
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
   BinaryNode * pSave = nodes.top();
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

} // namespace custom

#endif // BST_H
