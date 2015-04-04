/***************************************************************************************************
* Author:						Tanna McClure
* File:							TreeNode.h
* Date Created:					2/12/2015
*
* Modification Date: 			2/16/2015
* Modification: 				added balance factor
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: BinaryTreeNode
*
*	Purpose: 
*		Holds data and right left pointers for the tree
*
*	Manager Functions: 
*		TreeNode();
*			Default Constructor
*		BinaryTreeNode(const T & data);
*			1 arg constructor
*		TreeNode(const TreeNode<T> & copy);
*			Copy Constructor
*		~TreeNode();
*			Destructor
*		TreeNode<T> & operator = (const TreeNode<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		int Height() const;
*			Gets the height of the subtree of this node
*
***************************************************************************************************/
#ifndef TREENODE_H
#define TREENODE_H

template <typename T>
class BinaryTreeNode
{
	template <typename T>
	friend class BinaryTree;	
	template <typename T>
	friend class BinarySearchTree;
	template <typename T>
	friend class AVLTree;

	enum BALANCE { RIGHT = -1, EQUAL = 0, LEFT = 1 };

			//Default Constructor
	BinaryTreeNode();
			//1 arg constructor
	BinaryTreeNode(const T & data);
			//Copy Constructor
	BinaryTreeNode(const BinaryTreeNode<T> & copy);
			//Destructor
	~BinaryTreeNode();
			//Assignment Operator
	BinaryTreeNode<T> & operator = (const BinaryTreeNode<T> & rhs);

			//Gets the height of the subtree of the node
	int Height() const;

	T m_data;
	BinaryTreeNode<T> * m_left;
	BinaryTreeNode<T> * m_right;
	BALANCE m_balance;

};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: objects created
***************************************************************************************************/
template <typename T>
BinaryTreeNode<T>::BinaryTreeNode():m_right(nullptr), m_left(nullptr), m_balance(EQUAL)
{ }
/***************************************************************************************************
*	Purpose: 1 arg constructor
*
*	Entry: the data for the node
*
*	Exit: created
***************************************************************************************************/
template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T & data): m_data(data), m_right(nullptr), m_left(nullptr), m_balance(EQUAL)
{ }
/***************************************************************************************************
*	Purpose:copy constructor
*
*	Entry:the node to copy
*
*	Exit: created and copied
***************************************************************************************************/
template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T> & copy): m_data(copy.m_data), m_right(copy.m_right),
m_left(copy.m_left), m_balance(copy.m_balance)
{ }
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: set back to nullptr
***************************************************************************************************/
template <typename T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
	m_left = nullptr;
	m_right = nullptr;
	m_balance = EQUAL;
}
/***************************************************************************************************
*	Purpose:assignment operator
*
*	Entry: node to copy
*
*	Exit: copied node
***************************************************************************************************/
template <typename T>
BinaryTreeNode<T> & BinaryTreeNode<T>::operator=(const BinaryTreeNode<T> & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_right = rhs.m_right;
		m_left = rhs.m_left;
		m_balance = rhs.m_balance;
	}
	return *this;
}
/***************************************************************************************************
*	Purpose:gets the height of the subtree of the node
*
*	Entry: none
*
*	Exit: returns height
***************************************************************************************************/
template <typename T>
int BinaryTreeNode<T>::Height() const
{
	int left(m_left ? m_left->Height() : -1),
		right(m_right ? m_right->Height() : -1);
	return (right > left ? right : left) + 1;
}
#endif