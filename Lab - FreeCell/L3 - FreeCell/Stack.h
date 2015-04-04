/***************************************************************************************************
* Author:						Tanna McClure
* File:							Stack.h
* Date Created:					1/28/2015
*
* Modification Date: 			1/28/2015
* Modification: 				Finished functions
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Stack
*
*	Purpose: 
*		Linked list based stack
*
*	Manager Functions: 
*		Stack();
*			Default Constructor
*		Stack(const Stack<T> & copy);
*			Copy Constructor
*		~Stack();
*			Destructor
*		Stack<T> & operator = (const Stack<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		void Push(T data);
*			adds an element to the array
*		T Pop();
*			returns and removes an element from the array
*		T Peek() const;
*			returns a copy of the element on top of the stack
*		int Size() const;
*			returns the number of items in the stack
*		bool IsEmpty() const;
*			returns true if stack is empty
*
***************************************************************************************************/
#ifndef STACK_H
#define STACK_H
#include "DoubleLinkedList.h"

template <typename T>
class Stack
{
public:
			//Default Constructor
	Stack();
			//1 arg ctor
	Stack(const T & first);
			//Copy Constructor
	Stack(const Stack<T> & copy);
			//Destructor
	~Stack();
			//Assignment Operator
	Stack<T> & operator = (const Stack<T> & rhs);

			//adds an element to the array
	void Push(T data);
			//returns and removes an element from the array
	T Pop();
			//returns a copy of the element on top of the stack
	T Peek() const;
			//returns the number of items in the stack
	int Size() const;
			//returns true if stack is empty
	bool IsEmpty() const;
			//returns true if stack is full

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
*	Exit: creates empty list
***************************************************************************************************/
template <typename T>
Stack<T>::Stack(): m_size(0)
{ }
/***************************************************************************************************
*	Purpose:1 arg ctor
*
*	Entry: the first item on the stack
*
*	Exit: stack created w/ one item
***************************************************************************************************/
template <typename T>
Stack<T>::Stack(const T & first):m_size(0)
{
	Push(first);
}
/***************************************************************************************************
*	Purpose: copy ctor
*
*	Entry: stack to copy
*
*	Exit: m_list is created to equal copy's
***************************************************************************************************/
template <typename T>
Stack<T>::Stack(const Stack<T> & copy): m_list(copy.m_list), m_size(copy.m_size)
{ }
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: objects is destroyed
***************************************************************************************************/
template <typename T>
Stack<T>::~Stack()
{
	m_size = 0;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the stack to copy
*
*	Exit: this now equals rhs
***************************************************************************************************/
template <typename T>
Stack<T> & Stack<T>::operator=(const Stack<T> & rhs)
{
	if (this != &rhs)
	{
		m_list = rhs.m_list;
		m_size = rhs.m_size;
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: adds an element to the top of the stack 
*
*	Entry: the element to add
*
*	Exit: item is now on top of the stack
***************************************************************************************************/
template <typename T>
void Stack<T>::Push(T data)
{
	m_size++;
	m_list.Append(data);
}
/***************************************************************************************************
*	Purpose: removes an item from the top of the stack
*
*	Entry: none
*
*	Exit: returns the item being removed
***************************************************************************************************/
template <typename T>
T Stack<T>::Pop()
{
	if (m_list.isEmpty())
		throw Exception("Exception:  Stack - Pop:   Underflow");

	m_size--;
	return m_list.RemoveLast();
}
/***************************************************************************************************
*	Purpose: returns the element on top of the stack without removing it
*
*	Entry: none
*
*	Exit: returns top of stack
***************************************************************************************************/
template <typename T>
T Stack<T>::Peek() const
{
	if (m_list.isEmpty())
		throw Exception("Exception:  Stack - Peek:   Underflow");

	return m_list.Last();
}
/***************************************************************************************************
*	Purpose: gets the number of items in the stack
*
*	Entry: none
*
*	Exit: returns m_size
***************************************************************************************************/
template <typename T>
int Stack<T>::Size() const
{
	return m_size;
}
/***************************************************************************************************
*	Purpose: checks if the stack is empty
*
*	Entry: none
*
*	Exit: returns true if nothing in stack
***************************************************************************************************/
template <typename T>
bool Stack<T>::IsEmpty() const
{
	return m_list.isEmpty();
}
#endif