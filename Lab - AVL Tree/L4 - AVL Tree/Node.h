/***************************************************************************************************
* Author:						Tanna McClure
* File:							Node.h
* Date Created:					1/6/2015
*
* Modification Date: 			1/6/2015
* Modification: 				Wrote functions
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Node
*
*	Purpose:
*		Holds data and pointers to other nodes
*
*	Manager Functions:
*		Node();
*			default constructor sets pointers to null
*		Node(const T & element);
*			1 arg constructor sets the node to contain the data that is passed in
*		Node(const Node & copy)
*			copy constructor - copies another node
*		Node & operator = (const Node & rhs)
*			assignment operator
*		~Node();
*			destructor - does nothing
*
*	Methods:
*		T GetData() const;
*			returns m_data
*		Node * GetNext() const;
*			returns m_next
*		Node * GetPrev() const;
*			returns m_prev
*		void SetData(const T & data);
*			sets m_data
*		void SetNext(const Node * next);
*			sets m_next
*		void SetPrev(const Node * prev);
*			sets m_prev
*
***************************************************************************************************/
#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
	template <typename T>
	friend class DoubleLinkedList;
private:
			//default constructor
	Node();
			//1 arg constructor
	Node(const T & element);
			//Copy Constructor
	Node(const Node & copy);
			//destructor
	~Node();
			//assignment operator
	Node & operator = (const Node & rhs);

			//Getters
	T GetData() const;
	Node * GetNext() const;
	Node * GetPrev() const;

			//Setters
	void SetData(const T & data);
	void SetNext(const Node * next);
	void SetPrev(const Node * prev);

	T m_data;
	Node * m_next;
	Node * m_prev;

};

/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/

/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: next is nullptr and num_created is incremented
***************************************************************************************************/
template <typename T>
Node<T>::Node() : m_next(nullptr), m_prev(nullptr)
{ }
/***************************************************************************************************
*	Purpose: 1 arg constructor
*
*	Entry: element to put in the node
*
*	Exit: the element is in the node and next is nullptr and num_created is incremented
***************************************************************************************************/
template <typename T>
Node<T>::Node(const T & element) : m_next(nullptr), m_prev(nullptr), m_data(element)
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the node to copy
*
*	Exit: they are the same and num_created is incremented
***************************************************************************************************/
template <typename T>
Node<T>::Node(const Node & copy) : m_next(nullptr), m_prev(nullptr)
{
	*this = copy;
}
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: next is nullptr
***************************************************************************************************/
template <typename T>
Node<T>::~Node()
{
	m_next = nullptr;
	m_prev = nullptr;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the node to copy
*
*	Exit: this is the same as rhs
***************************************************************************************************/
template <typename T>
Node<T> & Node<T>::operator = (const Node<T> & rhs)
{
	m_data = rhs.m_data;
	m_next = nullptr;
	m_prev = nullptr;
	return *this;
}

/***************************************************************************************************
*	Purpose: gets the data in the node
*
*	Entry: none
*
*	Exit: returns m_data
***************************************************************************************************/
template <typename T>
T Node<T>::GetData() const
{
	return m_data;
}
/***************************************************************************************************
*	Purpose: gets the pointer to the next node
*
*	Entry:none
*
*	Exit: returns m_next
***************************************************************************************************/
template <typename T>
Node<T> * Node<T>::GetNext() const
{
	return m_next;
}
/***************************************************************************************************
*	Purpose: gets the pointer to the previous node
*
*	Entry: none
*
*	Exit:returns m_prev
***************************************************************************************************/
template <typename T>
Node<T> * Node<T>::GetPrev() const
{
	return m_prev;
}
/***************************************************************************************************
*	Purpose: sets the data in the node
*
*	Entry: the new data
*
*	Exit: m_data is now equal to data
***************************************************************************************************/
template <typename T>
void Node<T>::SetData(const T & data)
{
	m_data = data;
}
/***************************************************************************************************
*	Purpose: changes the pointer to the next element
*
*	Entry: the new next pointer
*
*	Exit: m_next is changed
***************************************************************************************************/
template <typename T>
void Node<T>::SetNext(const Node * next)
{
	m_next = next;
}
/***************************************************************************************************
*	Purpose: changes the pointer to the previous element
*
*	Entry: the new previous pointer
*
*	Exit: m_prev is changed
***************************************************************************************************/
template <typename T>
void Node<T>::SetPrev(const Node * prev)
{
	m_prev = prev;
}

#endif