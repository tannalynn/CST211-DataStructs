/***************************************************************************************************
* Author:						Tanna McClure
* File:							ListIterator.h
* Date Created:					2/11/2015
*
* Modification Date: 			2/12/2015
* Modification: 				finished commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: ListIterator
*
*	Purpose: 
*		abstract base class for list iterators
*
*	Manager Functions: 
*		ListIterator(DoubleLinkedList<T> * list);
*			1 arg Constructor
*		ListIterator(const ListIterator<T> & copy);
*			Copy Constructor
*		~ListIterator();
*			Destructor
*		ListIterator<T> & operator = (const ListIterator<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		virtual void Reset() = 0;
*			starts at the beginning of the list
*		virtual void MoveNext() = 0;
*			moves to the next item
*		virtual bool IsDone() = 0;
*			  checks if at the end
*		virtual T & GetCurrent() = 0;
*			gets the data and can change it
*
***************************************************************************************************/
#ifndef LISTITERATOR_H
#define LISTITERATOR_H
#include "AbstractIterator.h"
#include "DoubleLinkedList.h"
template <typename T>
class ListIterator: public AbstractIterator<T>
{
public:
			//Default constructor
	ListIterator();
			//1 arg ctor
	ListIterator(const DoubleLinkedList<T> * list);
			//Copy Constructor
	ListIterator(const ListIterator<T> & copy);
			//Destructor
	~ListIterator();
			//Assignment Operator
	ListIterator<T> & operator = (const ListIterator<T> & rhs);

			//starts at the beginning of the list
	virtual void Reset() = 0;
			//moves to the next item
	virtual void MoveNext() = 0;
			//checks if at the end
	virtual bool IsDone() = 0;
			//gets the data and can change it
	virtual T & GetCurrent() = 0;

protected:
	const DoubleLinkedList<T> * m_list;
	Node<T> * m_current;
};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: everything is null
***************************************************************************************************/
template <typename T>
ListIterator<T>::ListIterator(): m_current(nullptr), m_list(nullptr)
{ }
/***************************************************************************************************
*	Purpose: 1 arg ctor
*
*	Entry: the linked list the iterator will go through
*
*	Exit: object created
***************************************************************************************************/
template <typename T>
ListIterator<T>::ListIterator(const DoubleLinkedList<T> * list): m_list(list), m_current(nullptr)
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the list to copy
*
*	Exit: this is the same as copy
***************************************************************************************************/
template <typename T>
ListIterator<T>::ListIterator(const ListIterator<T> & copy):m_current(copy.m_current), m_list(copy.m_list)
{ }
/***************************************************************************************************
*	Purpose: destructor 
*
*	Entry: none
*
*	Exit: object destroyed
***************************************************************************************************/
template <typename T>
ListIterator<T>::~ListIterator()
{ 
	m_list = nullptr;
	m_current = nullptr;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the iterator to copy
*
*	Exit: this = rhs
***************************************************************************************************/
template <typename T>
ListIterator<T> & ListIterator<T>::operator=(const ListIterator<T> & rhs)
{
	if (this != &rhs)
	{
		m_list = rhs.m_list;
		m_current = rhs.m_current;
	}
	return *this;
}
#endif