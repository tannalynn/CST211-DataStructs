/***************************************************************************************************
* Author:						Tanna McClure
* File:							AVLTree.h
* Date Created:					2/16/2015
*
* Modification Date: 			2/17/2015
* Modification: 				Completed delete functions
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: AVLTree
*
*	Purpose: 
*		AVL tree class
*
*	Manager Functions: 
*		AVLTree();
*			Default Constructor
*		AVLTree(const AVLTree<T> & copy);
*			Copy Constructor
*		~AVLTree();
*			Destructor
*		AVLTree<T> & operator = (const AVLTree<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		void Insert(const T & data);
*			inserts a node into the tree	  
*		void Delete(const T & data);
*			deletes a node
*		void Delete(const T & data, BinaryTreeNode<T> *& node);
*			Deletes a node
*		void Delete(BinaryTreeNode<T> *& node);
*			overrides base class way of deleting a node
*		void Insert(BinaryTreeNode<T> *& node, const T & data, bool & taller);
*			inserts a node into the tree
*		void BalanceLeft(BinaryTreeNode<T> *& node, bool & taller);
*			Balances the tree for left
*		void BalanceRight(BinaryTreeNode<T> *& node, bool & taller);
*			Balances the tree for right
*		void RotateRR(BinaryTreeNode<T> *& node);
*		void RotateLL(BinaryTreeNode<T> *& node);
*		void RotateRL(BinaryTreeNode<T> *& node);
*		void RotateLR(BinaryTreeNode<T> *& node);
*			rotation functions
*		void BalanceFactor(BinaryTreeNode<T> *& node);
*			recalculates the balance factor for the node
***************************************************************************************************/
#ifndef AVLTREE_H
#define AVLTREE_H
#include "BinarySearchTree.h"

template <typename T>
class AVLTree: public BinarySearchTree<T>
{
public:
			//Default Constructor
	AVLTree();
			//Copy Constructor
	AVLTree(const AVLTree<T> & copy);
			//Destructor
	~AVLTree();
			//Assignment Operator
	AVLTree<T> & operator = (const AVLTree<T> & rhs);

			//inserts a node into the tree
	void Insert(const T & data);
			//deletes a node
	void Delete(const T & data);

protected:
			//Deletes a node
	void Delete(const T & data, BinaryTreeNode<T> *& node);
			//overrides base class way of deleting a node
	void Delete(BinaryTreeNode<T> *& node);

			//inserts a node into the tree
	void Insert(BinaryTreeNode<T> *& node, const T & data, bool & taller);
			//Balances the tree for left
	void BalanceLeft(BinaryTreeNode<T> *& node, bool & taller);
			//Balances the tree for right
	void BalanceRight(BinaryTreeNode<T> *& node, bool & taller);

			//rotation functions
	void RotateRR(BinaryTreeNode<T> *& node);
	void RotateLL(BinaryTreeNode<T> *& node);
	void RotateRL(BinaryTreeNode<T> *& node);
	void RotateLR(BinaryTreeNode<T> *& node);

			//recalculates the balance factor for the node
	void BalanceFactor(BinaryTreeNode<T> *& node);
};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: initialized to parent object reference to this
***************************************************************************************************/
template <typename T>
AVLTree<T>::AVLTree(): BinarySearchTree(this)
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: tree to copy
*
*	Exit: copied entire tree
***************************************************************************************************/
template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T> & copy): BinarySearchTree(this)
{
	*this = copy;
}
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: calls parent destructor
***************************************************************************************************/
template <typename T>
AVLTree<T>::~AVLTree()
{ }
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the tree to copy
*
*	Exit: this tree is now a copy of the one passed in
***************************************************************************************************/
template <typename T>
AVLTree<T> & AVLTree<T>::operator=(const AVLTree<T> & rhs)
{
	if (this != &rhs)
		BinarySearchTree::operator=(rhs);
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
void AVLTree<T>::Insert(const T & data)
{
	bool taller = false;
	Insert(m_root, data, taller);
}
/***************************************************************************************************
*	Purpose: inserts a node into the tree		PRIVATE
*
*	Entry: the data to put in the tree and the node to insert to
*
*	Exit: data added to tree and rebalanced if needed
***************************************************************************************************/
template <typename T>
void AVLTree<T>::Insert(BinaryTreeNode<T> *& node, const T & data, bool & taller)
{
	if (!node) //node is empty
	{
		node = new BinaryTreeNode<T>(data);
		if (node != m_root)
			taller = true;
	}
	else if (data < node->m_data) //go left
	{
		Insert(node->m_left, data, taller);
		if (taller)
		{
			switch (node->m_balance)
			{
				case BinaryTreeNode<T>::LEFT:
					BalanceLeft(node, taller);
					break;
				case BinaryTreeNode<T>::RIGHT:
					node->m_balance = BinaryTreeNode<T>::EQUAL;
					taller = false;
					break;
				case BinaryTreeNode<T>::EQUAL:
					node->m_balance = BinaryTreeNode<T>::LEFT;
					break;
			}
		}
	}
	else if (data > node->m_data) //go right
	{
		Insert(node->m_right, data, taller);
		if (taller)
		{
			switch (node->m_balance)
			{
				case BinaryTreeNode<T>::LEFT:
					node->m_balance = BinaryTreeNode<T>::EQUAL;
					taller = false;
					break;
				case BinaryTreeNode<T>::RIGHT:
					BalanceRight(node, taller);
					break;
				case BinaryTreeNode<T>::EQUAL:
					node->m_balance = BinaryTreeNode<T>::RIGHT;
					break;
			}
		}
	}
}
/***************************************************************************************************
*	Purpose: Balances the tree if gets off balance from the left
*
*	Entry: the node that has the imbalance 
*
*	Exit: tree balanced
***************************************************************************************************/
template <typename T>
void AVLTree<T>::BalanceLeft(BinaryTreeNode<T> *& node, bool & taller)
{

	switch (node->m_left->m_balance)
	{
		case BinaryTreeNode<T>::LEFT:
			node->m_balance = BinaryTreeNode<T>::EQUAL;
			node->m_left->m_balance = BinaryTreeNode<T>::EQUAL;
			RotateLL(node);
			
			break;
		case BinaryTreeNode<T>::RIGHT:
			
			if (node->m_left->m_right->m_balance == BinaryTreeNode<T>::LEFT)
			{
				node->m_balance = BinaryTreeNode<T>::RIGHT;
				node->m_left->m_balance = BinaryTreeNode<T>::EQUAL;
			}
			else if (node->m_left->m_right->m_balance == BinaryTreeNode<T>::EQUAL)
			{
				node->m_left->m_balance = BinaryTreeNode<T>::EQUAL;
				node->m_balance = BinaryTreeNode<T>::EQUAL;
			}
			else
			{
				node->m_balance = BinaryTreeNode<T>::EQUAL;
				node->m_left->m_balance = BinaryTreeNode<T>::LEFT;
			}
			node->m_left->m_right->m_balance = BinaryTreeNode<T>::EQUAL;
			RotateLR(node);
			break;
	}
	taller = false;
}
/***************************************************************************************************
*	Purpose: Balances the tree if gets off balance from the right
*
*	Entry: the node that has the imbalance
*
*	Exit: tree balanced
***************************************************************************************************/
template <typename T>
void AVLTree<T>::BalanceRight(BinaryTreeNode<T> *& node, bool & taller)
{
	switch (node->m_right->m_balance)
	{
		case BinaryTreeNode<T>::RIGHT:
			node->m_balance = BinaryTreeNode<T>::EQUAL;
			node->m_right->m_balance = BinaryTreeNode<T>::EQUAL;
			RotateRR(node);
			break;
		case BinaryTreeNode<T>::LEFT:
			if (node->m_right->m_left->m_balance == BinaryTreeNode<T>::RIGHT)
			{
				node->m_balance = BinaryTreeNode<T>::LEFT;
				node->m_right->m_balance = BinaryTreeNode<T>::EQUAL;
			}
			else if (node->m_right->m_left->m_balance == BinaryTreeNode<T>::EQUAL)
			{
				node->m_right->m_balance = BinaryTreeNode<T>::EQUAL;
				node->m_balance = BinaryTreeNode<T>::EQUAL;
			}
			else
			{
				node->m_balance = BinaryTreeNode<T>::EQUAL;
				node->m_right->m_balance = BinaryTreeNode<T>::RIGHT;
			}
			node->m_right->m_left->m_balance = BinaryTreeNode<T>::EQUAL;
			RotateRL(node);
			break;
	}
	taller = false;
}
/***************************************************************************************************
*	Purpose: Performs a RR rotation on the node
*
*	Entry: the node to perform the rotation on
*
*	Exit: tree has been rotated
***************************************************************************************************/
template <typename T>
void AVLTree<T>::RotateRR(BinaryTreeNode<T> *& node)
{
	BinaryTreeNode<T> * new_child = node;

	node = node->m_right; //new parent
	new_child->m_right = node->m_left;
	node->m_left = new_child;
}
/***************************************************************************************************
*	Purpose: Performs a LL rotation on the node
*
*	Entry: the node to perform the rotation on
*
*	Exit: tree has been rotated
***************************************************************************************************/
template <typename T>
void AVLTree<T>::RotateLL(BinaryTreeNode<T> *& node)
{
	BinaryTreeNode<T> * new_child = node;

	node = node->m_left;
	new_child->m_left = node->m_right;
	node->m_right = new_child;
}
/***************************************************************************************************
*	Purpose: Performs a RL rotation on the node
*
*	Entry: the node to perform the rotation on
*
*	Exit: tree has been rotated
***************************************************************************************************/
template <typename T>
void AVLTree<T>::RotateRL(BinaryTreeNode<T> *& node)
{
	RotateLL(node->m_right);
	RotateRR(node);
}
/***************************************************************************************************
*	Purpose: Performs a LR rotation on the node
*
*	Entry: the node to perform the rotation on
*
*	Exit: tree has been rotated
***************************************************************************************************/
template <typename T>
void AVLTree<T>::RotateLR(BinaryTreeNode<T> *& node)
{
	RotateRR(node->m_left);
	RotateLL(node);
}
/***************************************************************************************************
*	Purpose: deletes a node in the tree		PUBLIC
*
*	Entry: the data of the node to delete and the node to search from
*
*	Exit: node deleted
***************************************************************************************************/
template <typename T>
void AVLTree<T>::Delete(const T & data)
{
	if (!m_root)
		throw Exception("Exception:  BinarySearchTree - Delete:   Tree empty");
	Delete(data, m_root);
}
/***************************************************************************************************
*	Purpose: deletes a node
*
*	Entry: the node to search from and the data to delete
*
*	Exit: node deleted and tree
***************************************************************************************************/
template <typename T>
void AVLTree<T>::Delete(const T & data, BinaryTreeNode<T> *& node)
{
	if (!node)
		throw Exception("Exception:  AVLTree - Delete:   Not Found");
	if (node->m_data == data)//actually delete the node
		Delete(node);
	else
	{
		if (node->m_data > data)
			Delete(data, node->m_left); //keep searching
		else if (node->m_data < data)
			Delete(data, node->m_right); //keep searching 

		int balance = (node->m_left ? node->m_left->Height() : 0) - 
			          (node->m_right ? node->m_right->Height() : 0);

		if (abs(balance) > 1)//re-balance tree
		{
			if (balance > 0) //unbalanced to the left
				RotateLL(node);
			else //unbalanced to the right
				RotateRR(node);
		}
		else
			node->m_balance = BinaryTreeNode<T>::BALANCE(balance); //reset balance factor
	}
}
/***************************************************************************************************
*	Purpose: deletes a node
*
*	Entry: the node to delete
*
*	Exit: node deleted and tree 
***************************************************************************************************/
template <typename T>
void AVLTree<T>::Delete(BinaryTreeNode<T> *& node)
{
	if (!node)
		throw Exception("Exception:  AVLTree - DeleteFromTree:   Something Went Wrong");

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
		else //has 2 children
		{
			if (node->m_left->Height() >= node->m_right->Height()) //swap in left   
			{
				BinaryTreeNode<T> * temp = node,
					*temp_child = node->m_left->m_right;
				node = node->m_left;
				node->m_right = temp->m_right;
				delete temp;
				temp = node->m_right;
				while (temp->m_left)
					temp = temp->m_left;
				temp->m_left = temp_child;
			}
			else //swap in right
			{
				BinaryTreeNode<T> * temp = node,
					*temp_child = node->m_right->m_left;
				node = node->m_right;
				node->m_left = temp->m_left;
				delete temp;
				temp = node->m_left;
				while (temp->m_right)
					temp = temp->m_right;
				temp->m_right = temp_child;
			}
		}
	}
}
#endif