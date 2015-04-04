/***************************************************************************************************
* Author:						Tanna McClure
* File:							Queue.h
* Date Created:					1/29/2015
*
* Modification Date: 			1/29/2015
* Modification: 				Created class
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Queue
*
*	Purpose: 
*		Linked List based queue
*
*	Manager Functions: 
*		Queue();
*			Default Constructor
*		Queue(const Queue<T> & copy);
*			Copy Constructor
*		~Queue();
*			Destructor
*		Queue<T> & operator = (const Queue<T> & rhs);
*			Assignment operator
*
*	Methods: 	
*		void Enqueue(T data);
*			puts an item at the end of the queue
*		T Dequeue();
*			removes the item at the beginning of the list and returns it
*		T & Front();
*			returns ref to first in queue
*		int Size() const;
*			returns the number of items currently in size
*		bool IsEmpty() const;
*			checks if queue is empty
*
***************************************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H
#include "DoubleLinkedList.h"

template <typename T>
class Queue
{
public:
			//Default Constructor
	Queue();
			//Copy Constructor
	Queue(const Queue<T> & copy);
			//Destructor
	~Queue();
			//Assignment Operator
	Queue<T> & operator = (const Queue<T> & rhs);

			//puts an item at the end of the queue
	void Enqueue(T data);
			//removes the item at the beginning of the list and returns it
	T Dequeue();
			//returns ref to first in queue
	T & Front();
			//returns the number of items currently in size
	int Size() const;
			//checks if queue is empty
	bool IsEmpty() const;
			//empties the queue
	void Purge();

private:
	DoubleLinkedList<T> m_list;
	int m_size;
};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: empty queue created
***************************************************************************************************/
template <typename T>
Queue<T>::Queue():m_size(0)
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the queue to copy
*
*	Exit: new queue created
***************************************************************************************************/
template <typename T>
Queue<T>::Queue(const Queue<T> & copy):m_list(copy.m_list), m_size(copy.m_size)
{ }
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: set back to 0
***************************************************************************************************/
template <typename T>
Queue<T>::~Queue()
{
	m_size = 0;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry:
*
*	Exit:
***************************************************************************************************/
template <typename T>
Queue<T> & Queue<T>::operator=(const Queue<T> & rhs)
{
	if (this != &rhs)
	{
		m_list = rhs.m_list;
		m_size = rhs.m_size;
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: adds an item to the end of the queue
*
*	Entry: the item to add
*
*	Exit: added
***************************************************************************************************/
template <typename T>
void Queue<T>::Enqueue(T data)
{
	m_size++;
	m_list.Append(data);
}
/***************************************************************************************************
*	Purpose: removes the item at the front of the queue
*
*	Entry: none
*
*	Exit: item at the front of queue
***************************************************************************************************/
template <typename T>
T Queue<T>::Dequeue()
{
	if (IsEmpty())
		throw Exception("Exception:  Queue - Dequeue:   Empty");
	m_size--;
	return m_list.RemoveFirst();
}
/***************************************************************************************************
*	Purpose: returns a ref to the first item in the queue
*
*	Entry: none
*
*	Exit: first item in queue
***************************************************************************************************/
template <typename T>
T & Queue<T>::Front()
{
	if (IsEmpty())
		throw Exception("Exception:  Queue - Front:   Empty");
	return const_cast<T &>(m_list.First());
}
/***************************************************************************************************
*	Purpose: gets the number of elements in the queue
*
*	Entry: none
*
*	Exit: returns m_size
***************************************************************************************************/
template <typename T>
int Queue<T>::Size() const
{
	return m_size;
}
/***************************************************************************************************
*	Purpose: checks if the queue is empty
*
*	Entry: none
*
*	Exit: returns true if nothing in queue
***************************************************************************************************/
template <typename T>
bool Queue<T>::IsEmpty() const
{
	return (m_size == 0);
}
/***************************************************************************************************
*	Purpose: empties queue
*
*	Entry: none
*
*	Exit: size = 0
***************************************************************************************************/
template <typename T>
void Queue<T>::Purge()
{
	m_list.Purge();
	m_size = 0;
}
#endif