/***************************************************************************************************
* Author:						Tanna McClure
* File:							BinaryTree.h
* Date Created:					2/15/2015
*
* Modification Date: 			2/15/2015
* Modification: 				created
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: BinaryTree
*
*	Purpose: 
*		Basic Binary Tree class
*
*	Manager Functions: 
*		BinaryTree();
*			Default Constructor
*		BinaryTree(BinaryTree<T> * ref);
*			1 arg constructor for derived classes
*		BinaryTree(const BinaryTree<T> & copy);
*			Copy Constructor
*		~BinaryTree();
*			Destructor
*		BinaryTree<T> & operator = (const BinaryTree<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		virtual void Insert(const T & data);
*			inserts a node into the tree	
*		int Height() const;
*			gets the height of the tree
*		void Purge();
*			empties the list
*		bool IsEmpty() const;
*			checks if the tree is empty
*		void Purge(BinaryTreeNode<T> *& ptr);
*			empties the list
*		virtual void Delete(const T & data)
*		virtual void Delete(BinaryTreeNode<T> *& node);
*		bool Delete(const T & data, BinaryTreeNode<T> *& node);
*			Deletes node
*		void TraverseInOrder(void(*visit)(const T & data)) const;
*		void TraverseInOrder(void(*visit) (const T & data), BinaryTreeNode<T> * node) const;
*			In order traversal of tree
*		void TraversePreOrder( void(*visit)(const T & data) ) const;
*		void TraversePreOrder(void(*visit) (const T & data), BinaryTreeNode<T> * node) const;
*			Pre order traversal
*		void TraversePostOrder( void(*visit)(const T & data) ) const;
*		void TraversePostOrder(void(*visit) (const T & data), BinaryTreeNode<T> * node) const;
*			Post Order Traversal
*		void TraverseBreadth( void(*visit)(const T & data) ) const;
*			Breadth first traversal
*
***************************************************************************************************/
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "BinaryTreeNode.h"
#include "Exception.h"
#include "Queue.h"

template <typename T>
class BinaryTree
{
public:
			//Default Constructor
	BinaryTree();
			//Copy Constructor
	BinaryTree(const BinaryTree<T> & copy);
			//Destructor
	~BinaryTree();
			//Assignment Operator
	BinaryTree<T> & operator = (const BinaryTree<T> & rhs);

			//inserts a node into the tree
	virtual void Insert(const T & data);
			//deletes a node from the tree
	virtual void Delete(const T & data);

			//gets the height of the tree
	int Height() const;
			//empties the list
	void Purge();
			//checks if the tree is empty
	bool IsEmpty() const;

			//in order traversal
	void TraverseInOrder(void(*visit)(const T & data)) const;
			//pre order traversal
	void TraversePreOrder( void(*visit)(const T & data) ) const;
			//post order traversal
	void TraversePostOrder( void(*visit)(const T & data) ) const;
			//breadth first traversal
	void TraverseBreadth( void(*visit)(const T & data) ) const;

protected:
	BinaryTreeNode<T> * m_root;
	BinaryTree<T> * m_ref;

			//1 arg constructor
	BinaryTree(BinaryTree<T> * ref);
			//empties the list
	void Purge(BinaryTreeNode<T> *& ptr);
			//deletes a node
	virtual void Delete(BinaryTreeNode<T> *& node);
	
			//in order traversal
	void TraverseInOrder(void(*visit) (const T & data), BinaryTreeNode<T> * node) const;
			//pre order traversal
	void TraversePreOrder(void(*visit) (const T & data), BinaryTreeNode<T> * node) const;
			//post order traversal
	void TraversePostOrder(void(*visit) (const T & data), BinaryTreeNode<T> * node) const;

private:
			//deletes a node
	bool Delete(const T & data, BinaryTreeNode<T> *& node);
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
BinaryTree<T>::BinaryTree(): m_root(nullptr), m_ref(this)
{ }
/***************************************************************************************************
*	Purpose: 1 arg constructor - for derived classes only
*
*	Entry: reference to object
*
*	Exit: initialized to null
***************************************************************************************************/
template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T> * ref):m_ref(ref), m_root(nullptr)
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: tree to copy
*
*	Exit: copied entire tree
***************************************************************************************************/
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> & copy): m_root(nullptr), m_ref(this)
{
	*this = copy;
}
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: tree purged
***************************************************************************************************/
template <typename T>
BinaryTree<T>::~BinaryTree()
{
	Purge(m_root);
	m_ref = nullptr;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the tree to copy
*
*	Exit: this tree is now a copy of the one passed in
***************************************************************************************************/
template <typename T>
BinaryTree<T> & BinaryTree<T>::operator=(const BinaryTree<T> & rhs)
{
	if (this != &rhs)
	{
		Purge();
		if (rhs.m_root)
		{
			Queue<BinaryTreeNode<T> *> traverse;
			traverse.Enqueue(rhs.m_root);
			while (!traverse.IsEmpty())
			{
				BinaryTreeNode<T> * ptr = traverse.Dequeue();
				if (ptr->m_left)
					traverse.Enqueue(ptr->m_left);
				if (ptr->m_right)
					traverse.Enqueue(ptr->m_right);
				m_ref->Insert(ptr->m_data); //calls the overridden function for child classes
			}
		}
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: inserts into tree
*
*	Entry: data to insert
*
*	Exit: new node added to tree
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::Insert(const T & data)
{
	if (!m_root)
		m_root = new BinaryTreeNode<T>(data);
	else
	{
		Queue<BinaryTreeNode<T> *> traverse;
		traverse.Enqueue(m_root);

		bool inserted = false;
		do
		{
			BinaryTreeNode<T> * ptr = traverse.Dequeue();

			if (!ptr->m_left)//insert into left
			{
				inserted = true;
				ptr->m_left = new BinaryTreeNode<T>(data);
			}
			else if (!ptr->m_right)//insert into right
			{
				inserted = true;
				ptr->m_right = new BinaryTreeNode<T>(data);
			}
			else
			{
				traverse.Enqueue(ptr->m_left);
				traverse.Enqueue(ptr->m_right);
			}
		} while (!inserted);
	}
}
/***************************************************************************************************
*	Purpose: searches and deletes a node
*
*	Entry: the data to delete
*
*	Exit: data deleted
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::Delete(const T & data)
{
	if (!m_root)
		throw Exception("Exception:  BinaryTree - Delete:   Tree empty");

	if (!Delete(data, m_root))
		throw Exception("Exception:  BinaryTree - Delete:   Not Found");

}
/***************************************************************************************************
*	Purpose: finds the node to delete
*
*	Entry: the node to search from
*
*	Exit: true if node was found and deleted
***************************************************************************************************/
template <typename T>
bool BinaryTree<T>::Delete(const T & data, BinaryTreeNode<T> *& node)
{
	bool found = false;
	if (node)
	{
		if (node->m_data == data)
		{
			Delete(node);
			found = true;
		}
		else
		{
			found = Delete(data, node->m_left);
			if (!found)
				found = Delete(data, node->m_right);
		}
	}
	return found;
}
/***************************************************************************************************
*	Purpose: searches and deletes a node
*
*	Entry: the data to delete
*
*	Exit: data deleted
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::Delete(BinaryTreeNode<T> *& node)
{
	Queue<BinaryTreeNode<T> *&> traverse;
	traverse.Enqueue(m_root);
	bool done = false;

	if (node == m_root && !m_root->m_left) //root is whats getting deleted and there is nothing else
	{
		delete m_root;
		m_root = nullptr;
	}
	else
		while (!done)
		{
			BinaryTreeNode<T> * ptr = traverse.Dequeue();
			if (ptr->m_left)
				traverse.Enqueue(ptr->m_left);
			if (ptr->m_right)
				traverse.Enqueue(ptr->m_right);
			else if (traverse.Size() == 1)
			{
				done = true;
				BinaryTreeNode<T> *& last = traverse.Dequeue();
				BinaryTreeNode<T> * temp = last;
				last = node;
				node = temp;
				node->m_right = last->m_right;
				node->m_left = last->m_left;
				delete last;
				last = nullptr;
			}
		}

}
/***************************************************************************************************
*	Purpose: gets the height of the tree
*
*	Entry: none
*
*	Exit: returns height
***************************************************************************************************/
template <typename T>
int BinaryTree<T>::Height() const
{
	return m_root->Height();
}
/***************************************************************************************************
*	Purpose: checks if tree is empty
*
*	Entry: none
*
*	Exit: true if root is null
***************************************************************************************************/
template <typename T>
bool BinaryTree<T>::IsEmpty() const
{
	return m_root == nullptr;
}
/***************************************************************************************************
*	Purpose: purges the tree	PUBLIC
*
*	Entry: none
*
*	Exit: tree purged
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::Purge()
{
	Purge(m_root);
}
/***************************************************************************************************
*	Purpose: purges the tree	PROTECTED
*
*	Entry: the ptr a node to delete(along with everything under it)
*
*	Exit: tree purged
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::Purge(BinaryTreeNode<T> *& ptr)
{
	if (ptr)
	{
		Purge(ptr->m_left);
		Purge(ptr->m_right);
		delete ptr;
		ptr = nullptr;
	}
}
/***************************************************************************************************
*	Purpose: traverses the tree starting with the lowest and going to the highest PUBLIC
*
*	Entry: the function used to visit
*
*	Exit: tree has been traversed
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::TraverseInOrder(void(*visit)(const T & data)) const
{
	if (!m_root)
		throw Exception("Exception:  BinaryTree - TraverseInOrder:   Tree empty");
	TraverseInOrder(visit, m_root);
}
/***************************************************************************************************
*	Purpose: traverses the tree starting with the lowest and going to the highest PROTECTED
*
*	Entry: the function used to visit and the node to visit
*
*	Exit: tree has been traversed
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::TraverseInOrder(void(*visit) (const T & data), BinaryTreeNode<T> * node) const
{
	if (node)
	{
		TraverseInOrder(visit, node->m_left);
		visit(node->m_data);
		TraverseInOrder(visit, node->m_right);
	}
}
/***************************************************************************************************
*	Purpose: traverses the tree in pre order	PUBLIC
*
*	Entry: the function used to visit
*
*	Exit: tree has been traversed
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::TraversePreOrder(void(*visit)(const T & data)) const
{
	if (!m_root)
		throw Exception("Exception:  BinaryTree - TraversePreOrder:   Tree empty");
	TraversePreOrder(visit, m_root);
}
/***************************************************************************************************
*	Purpose: traverses the tree in pre order	PROTECTED
*
*	Entry: the function used to visit and node to visit
*
*	Exit: tree has been traversed
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::TraversePreOrder(void(*visit) (const T & data), BinaryTreeNode<T> * node) const
{
	if (node)
	{
		visit(node->m_data);
		TraversePreOrder(visit, node->m_left);
		TraversePreOrder(visit, node->m_right);
	}
}
/***************************************************************************************************
*	Purpose: traverses the tree in post order	PUBLIC
*
*	Entry: the function used to visit
*
*	Exit: tree has been traversed
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::TraversePostOrder(void(*visit)(const T & data)) const
{
	if (!m_root)
		throw Exception("Exception:  BinaryTree - TraversePostOrder:   Tree empty");
	TraversePostOrder(visit, m_root);
}
/***************************************************************************************************
*	Purpose: traverses the tree in post order	PROTECTED
*
*	Entry: the function used to visit and node to visit
*
*	Exit: tree has been traversed
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::TraversePostOrder(void(*visit) (const T & data), BinaryTreeNode<T> * node) const
{
	if (node)
	{
		TraversePostOrder(visit, node->m_left);
		TraversePostOrder(visit, node->m_right);
		visit(node->m_data);
	}
}
/***************************************************************************************************
*	Purpose: traverses the tree in breadth first order	PUBLIC
*
*	Entry: the function used to visit
*
*	Exit: tree has been traversed
***************************************************************************************************/
template <typename T>
void BinaryTree<T>::TraverseBreadth(void(*visit)(const T & data)) const
{
	if (!m_root)
		throw Exception("Exception:  BinaryTree - TraverseBreadth:   Tree empty");

	Queue<BinaryTreeNode<T> *> traverse;
	traverse.Enqueue(m_root);
	while (!traverse.IsEmpty())
	{
		BinaryTreeNode<T> * ptr = traverse.Dequeue();
		if (ptr->m_left)
			traverse.Enqueue(ptr->m_left);
		if (ptr->m_right)
			traverse.Enqueue(ptr->m_right);
		visit(ptr->m_data);
	}
}
#endif