/***************************************************************************************************
* Author:						Tanna McClure
* File:							BinarySearchTree.h
* Date Created:					2/12/2015
*
* Modification Date: 			2/15/2015
* Modification: 				inherits from BinaryTree class
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: BinarySearchTree
*
*	Purpose: 
*		Binary Search Tree class
*
*	Manager Functions: 
*		BinarySearchTree();
*			Default Constructor
*		BinarySearchTree(const BinarySearchTree<T> & copy);
*			Copy Constructor
*		~BinarySearchTree();
*			Destructor
*		BinarySearchTree<T> & operator = (const BinarySearchTree<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		virtual void Insert(const T & data);
*		virtual void Insert(const T & data, BinaryTreeNode<T> & node);
*			inserts a node into the tree
*		virtual void Delete(const T & data);
*		virtual void Delete(BinaryTreeNode<T> *& node);
*		virtual void Delete(const T & data, BinaryTreeNode<T> *& node);
*			deletes a node from the tree
***************************************************************************************************/
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "BinaryTree.h"
template <typename T>
class BinarySearchTree: public BinaryTree<T>
{
public:
			//Default Constructor
	BinarySearchTree();
			//Copy Constructor
	BinarySearchTree(const BinarySearchTree<T> & copy);
			//Destructor
	~BinarySearchTree();
			//Assignment Operator
	BinarySearchTree<T> & operator = (const BinarySearchTree<T> & rhs);

			//inserts a node into the tree
	virtual void Insert(const T & data);
			//deletes a node from the tree
	virtual void Delete(const T & data);

protected:
			//1 arg constructor
	BinarySearchTree(BinaryTree<T> * ref);
			//deletes a node from the list using a pointer to a node
	virtual void Delete(BinaryTreeNode<T> *& node);
			//Deletes a node
	virtual void Delete(const T & data, BinaryTreeNode<T> *& node);
			//inserts a node into the tree using a node
	virtual void Insert(const T & data, BinaryTreeNode<T> & node);

};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/   
/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: initialized to null
***************************************************************************************************/
template <typename T>
BinarySearchTree<T>::BinarySearchTree(): BinaryTree(this)
{ }
/***************************************************************************************************
*	Purpose: 1 arg constructor
*
*	Entry: the pointer to the object
*
*	Exit: called base class ctor
***************************************************************************************************/
template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinaryTree<T> * ref): BinaryTree(ref)
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: tree to copy
*
*	Exit: copied entire tree
***************************************************************************************************/
template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> & copy): BinaryTree(this)
{
	*this = copy;
}
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: called parent destructor
***************************************************************************************************/
template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{ }
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the tree to copy
*
*	Exit: this tree is now a copy of the one passed in
***************************************************************************************************/
template <typename T>
BinarySearchTree<T> & BinarySearchTree<T>::operator=(const BinarySearchTree<T> & rhs)
{
	if (this != &rhs)
		BinaryTree::operator=(rhs);
	return *this;
}
/***************************************************************************************************
*	Purpose: inserts a node into the tree		PUBLIC
*
*	Entry: the data to put in the tree
*
*	Exit: data added to tree
***************************************************************************************************/
template <typename T>
void BinarySearchTree<T>::Insert(const T & data)
{
	if (!m_root) //if tree is empty
		m_root = new BinaryTreeNode<T>(data);
	else
		Insert(data, *m_root);
}
/***************************************************************************************************
*	Purpose: inserts a node into the tree		PROTECTED
*
*	Entry: the data to put in the tree and the node to insert to
*
*	Exit: data added to tree
***************************************************************************************************/
template <typename T>
void BinarySearchTree<T>::Insert(const T & data, BinaryTreeNode<T> & node)
{
	if (data < node.m_data) //go left
		if (node.m_left) //if something on the left already
			Insert(data, *node.m_left);
		else //if the left is empty
			node.m_left = new BinaryTreeNode<T>(data);

	else if (data > node.m_data) //go right
		if (node.m_right) //if something on the right
			Insert(data, *node.m_right);
		else //if right is empty
			node.m_right = new BinaryTreeNode<T>(data);
}
/***************************************************************************************************
*	Purpose: deletes a node in the tree		PUBLIC
*
*	Entry: the data of the node to delete and the node to search from
*
*	Exit: node deleted
***************************************************************************************************/
template <typename T>
void BinarySearchTree<T>::Delete(const T & data)
{
	if (!m_root)
		throw Exception("Exception:  BinarySearchTree - Delete:   Tree empty");
	Delete(data, m_root);
}
/***************************************************************************************************
*	Purpose: deletes a node in the tree		PROTECTED
*
*	Entry: the data of the node to delete and the node to search from
*
*	Exit: node deleted
***************************************************************************************************/
template <typename T>
void BinarySearchTree<T>::Delete(const T & data, BinaryTreeNode<T> *& node)
{
	if (!node)
		throw Exception("Exception:  BinarySearchTree - Delete:   Not Found");

	if (data < node->m_data)		//if on left
		Delete(data, node->m_left);
	else if (data > node->m_data)	//if on right
		Delete(data, node->m_right);
	else							//if it's what needs to get deleted
		Delete(node);
}
/***************************************************************************************************
*	Purpose: deletes the node
*
*	Entry: the pointer of the node
*
*	Exit: node deleted
***************************************************************************************************/
template <typename T>
void BinarySearchTree<T>::Delete(BinaryTreeNode<T> *& node)
{
	if (!node)
		throw Exception("Exception:  BinarySearchTree - DeleteFromTree:   Something Went Wrong");

	if (!node->m_left) //if left is empty
	{
		if (!node->m_right) //no children
		{
			delete node; 
			node = nullptr;
		}
		else //only has right child
		{
			BinaryTreeNode<T> * temp = node;
			node = node->m_right;
			delete temp;
		}
	}
	else //left is not empty
	{
		if (!node->m_right) //only has left child
		{
			BinaryTreeNode<T> * temp = node;
			node = node->m_left;
			delete temp;
		}
		else //has both children
		{
			BinaryTreeNode<T> * temp = node,
				* temp_child = node->m_left->m_right;
			node = node->m_left;
			node->m_right = temp->m_right;
			delete temp;
			temp = node->m_right;
			while (temp->m_left)
				temp = temp->m_left;
			temp->m_left = temp_child;
		}
	}
}
#endif