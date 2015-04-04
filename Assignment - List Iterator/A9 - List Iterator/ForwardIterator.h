/***************************************************************************************************
* Author:						Tanna McClure
* File:							ForwardIterator.h
* Date Created:					2/11/2015
*
* Modification Date: 			2/12/2015	
* Modification: 				finished commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: ForwardIterator
*
*	Purpose: 
*		Iterates through a double linked list starting at the head and going to each next node
*
*	Manager Functions: 
*		ForwardIterator();
*			Default Constructor
*		ForwardIterator(const ForwardIterator<T> & copy);
*			Copy Constructor
*		~ForwardIterator();
*			Destructor
*		ForwardIterator<T> & operator = (const ForwardIterator<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		virtual void Reset();
*			starts at the beginning of the list
*		virtual void MoveNext();
*			moves to the next item
*		virtual bool IsDone();
*			  checks if at the end
*		virtual T & GetCurrent();
*			gets the data and can change it
*
***************************************************************************************************/
#ifndef FORWARDITERATOR_H
#define FORWARDITERATOR_H
#include "ListIterator.h"

template <typename T>
class ForwardIterator: public ListIterator<T>
{
public:
			//1 arg ctor
	ForwardIterator(const DoubleLinkedList<T> * list);
			//Copy Constructor
	ForwardIterator(const ForwardIterator<T> & copy);
			//Destructor
	~ForwardIterator();
			//Assignment Operator
	ForwardIterator<T> & operator = (const ForwardIterator<T> & rhs);

			//starts at the beginning of the list
	virtual void Reset();
			//moves to the next item
	virtual void MoveNext();
			//checks if at the end
	virtual bool IsDone();
			//gets the data and can change it
	virtual T & GetCurrent();
};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: 1 arg ctor
*
*	Entry: list
*
*	Exit: objects created
***************************************************************************************************/
template <typename T>
ForwardIterator<T>::ForwardIterator(const DoubleLinkedList<T> * list): ListIterator<T>(list)
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the iterator to copy
*
*	Exit: created 
***************************************************************************************************/
template <typename T>
ForwardIterator<T>::ForwardIterator(const ForwardIterator<T> & copy): ListIterator<T>(copy)
{ }
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: object destroyed
***************************************************************************************************/
template <typename T>
ForwardIterator<T>::~ForwardIterator()
{ }
/***************************************************************************************************
*	Purpose: assignment operator 
*
*	Entry: rhs
*
*	Exit: this = rhs
***************************************************************************************************/
template <typename T>
ForwardIterator<T> & ForwardIterator<T>::operator=(const ForwardIterator<T> & rhs)
{
	if (this != &rhs)
		ListIterator<T>::operator=(rhs);
	return *this;
}
/***************************************************************************************************
*	Purpose: starts at the beginning of the list
*
*	Entry: none
*
*	Exit: current set to front of list
***************************************************************************************************/
template <typename T>
void ForwardIterator<T>::Reset()
{
	m_current = m_list->m_head;
}
/***************************************************************************************************
*	Purpose:  moves to the next node if the current node is not null
*
*	Entry: none
*
*	Exit: m_current moved to next node
***************************************************************************************************/
template <typename T>
void ForwardIterator<T>::MoveNext()
{
	if (m_current)
		m_current = m_current->m_next;
}
/***************************************************************************************************
*	Purpose: checks to see if the iteration is complete
*
*	Entry: none
*
*	Exit: returns true if m_current is null
***************************************************************************************************/
template <typename T>
bool ForwardIterator<T>::IsDone()
{
	return !(m_current);
}
/***************************************************************************************************
*	Purpose: gets the current node
*
*	Entry: none
*
*	Exit: returns m_currents data
***************************************************************************************************/
template <typename T>
T & ForwardIterator<T>::GetCurrent()
{
	return m_current->m_data;
}
#endif