/***************************************************************************************************
* Author:						Tanna McClure
* File:							BackwardsIterator.h
* Date Created:					2/11/2015
*
* Modification Date: 			2/12/2015
* Modification: 				finished commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: BackwardsIterator
*
*	Purpose: 
*		Iterates through a double linked list starts at the end going to each previous node
*
*	Manager Functions: 
*		BackwardsIterator(DoubleLinkedList<T> * list);
*			1 arg Constructor
*		BackwardsIterator(const BackwardsIterator<T> & copy);
*			Copy Constructor
*		~BackwardsIterator();
*			Destructor
*		BackwardsIterator<T> & operator = (const BackwardsIterator<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		virtual void Reset();
*			starts at the end of the list
*		virtual void MoveNext();
*			moves to the next item
*		virtual bool IsDone();
*			  checks if at the end
*		virtual T & GetCurrent();
*			gets the data and can change it
*
***************************************************************************************************/
#ifndef BACKWARDSITERATOR_H
#define BACKWARDSITERATOR_H
#include "ListIterator.h"

template <typename T>
class BackwardsIterator: public ListIterator<T>
{
public:
			//1 arg Constructor
	BackwardsIterator(const DoubleLinkedList<T> * list);
			//Copy Constructor
	BackwardsIterator(const BackwardsIterator<T> & copy);
			//Destructor
	~BackwardsIterator();
			//Assignment Operator
	BackwardsIterator<T> & operator = (const BackwardsIterator<T> & rhs);

			//starts at the end of the list
	virtual void Reset();
			//moves to the prev item
	virtual void MoveNext();
			//checks if done
	virtual bool IsDone();
			//gets the data and can change it
	virtual  T & GetCurrent();

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
BackwardsIterator<T>::BackwardsIterator(const DoubleLinkedList<T> * list): ListIterator<T>(list)
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the iterator to copy
*
*	Exit: created
***************************************************************************************************/
template <typename T>
BackwardsIterator<T>::BackwardsIterator(const BackwardsIterator<T> & copy): ListIterator<T>(copy)
{ }
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: object destroyed
***************************************************************************************************/
template <typename T>
BackwardsIterator<T>::~BackwardsIterator()
{ }
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: rhs
*
*	Exit: this = rhs
***************************************************************************************************/
template <typename T>
BackwardsIterator<T> & BackwardsIterator<T>::operator=(const BackwardsIterator<T> & rhs)
{
	if (this != &rhs)
		ListIterator<T>::operator=(rhs);
	return *this;
}
/***************************************************************************************************
*	Purpose: starts at the end of the list
*
*	Entry: none
*
*	Exit: current set to end of list
***************************************************************************************************/
template <typename T>
void BackwardsIterator<T>::Reset()
{
	m_current = m_list->m_tail;
}
/***************************************************************************************************
*	Purpose:  moves to the prev node if the current node is not null
*
*	Entry: none
*
*	Exit: m_current moved to prev node
***************************************************************************************************/
template <typename T>
void BackwardsIterator<T>::MoveNext()
{
	if (m_current)
		m_current = m_current->m_prev;
}
/***************************************************************************************************
*	Purpose: checks to see if the iteration is complete
*
*	Entry: none
*
*	Exit: returns true if m_current is null
***************************************************************************************************/
template <typename T>
bool BackwardsIterator<T>::IsDone()
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
T & BackwardsIterator<T>::GetCurrent()
{
	return m_current->m_data;
}
#endif