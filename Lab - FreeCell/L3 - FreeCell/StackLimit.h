/***************************************************************************************************
* Author:						Tanna McClure
* File:							StackLimit.h
* Date Created:					1/28/2015
*								
* Modification Date: 			1/28/2015
* Modification: 				wrote functions
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: StackLimit
*
*	Purpose: 
*		Stack with a maximum size, given when constructed
*
*	Manager Functions: 
*		StackLimit(int size);
*			1 arg constructor
*		StackLimit(const StackLimit<T> & copy);
*			Copy Constructor
*		~StackLimit();
*			Destructor
*		StackLimit<T> & operator = (const StackLimit<T> & rhs);
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
*		bool IsFull() const;
*			returns true if stack is full
*
***************************************************************************************************/
#ifndef STACKLIMIT_H
#define STACKLIMIT_H
#include "Array_1D.h"

template <typename T>
class StackLimit
{
public:
			//1 arg ctor
	StackLimit(int size/* = 0*/);
			//Copy Constructor
	StackLimit(const StackLimit<T> & copy);
			//Destructor
	~StackLimit();
			//Assignment Operator
	StackLimit<T> & operator = (const StackLimit<T> & rhs);

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
	bool IsFull() const;

private:
	Array_1D<T> m_array;
	int m_size;
	int m_top;
};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: 1 arg ctor
*
*	Entry: the max size of the stack
*
*	Exit: array is created with a certain size
***************************************************************************************************/
template <typename T>
StackLimit<T>::StackLimit(int size): m_size(size), m_array(size), m_top(-1)
{ }
/***************************************************************************************************
*	Purpose: copy ctor
*
*	Entry: the stack to copy
*
*	Exit: a new stack is created that matches the one passed in
***************************************************************************************************/
template <typename T>
StackLimit<T>::StackLimit(const StackLimit<T> & copy): m_size(copy.m_size), m_array(copy.m_array),
													   m_top(copy.m_top)
{ }
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: set back to zero
***************************************************************************************************/
template <typename T>
StackLimit<T>::~StackLimit()
{
	m_top = 0;
	m_size = 0;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the stack to copy
*
*	Exit: this has been made equal to the rhs
***************************************************************************************************/
template <typename T>
StackLimit<T> & StackLimit<T>::operator=(const StackLimit<T> & rhs)
{
	if (this != &rhs)
	{
		m_size = rhs.m_size;
		m_array = rhs.m_array;
		m_top = rhs.m_top;
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: adds an element to the top of the stack
*
*	Entry: the new element
*
*	Exit: top of the stack has been moved and element added
***************************************************************************************************/
template <typename T>
void StackLimit<T>::Push(T data)
{
	if (IsFull())
		throw Exception("Exception:   StackLimit - Push:   Overflow");
	m_array[++m_top] = data;
}
/***************************************************************************************************
*	Purpose: removes an element from the top of the stack
*
*	Entry: none
*
*	Exit: returns the element being removed
***************************************************************************************************/
template <typename T>
T StackLimit<T>::Pop()
{
	if (IsEmpty())
		throw Exception("Exception:   StackLimit - Pop:   Underflow");
	return m_array[m_top--];

}
/***************************************************************************************************
*	Purpose: returns the element on top of the stack without removing it
*
*	Entry: none
*
*	Exit: returns element at m_top
***************************************************************************************************/
template <typename T>
T StackLimit<T>::Peek() const
{
	if (IsEmpty())
		throw Exception("Exception:   StackLimit - Peek:   Underflow");
	return m_array[m_top];
}
/***************************************************************************************************
*	Purpose: gets the number of items on the stack 
*
*	Entry: none
*
*	Exit: returns m_top+1 (+1 bc starting at zero)
***************************************************************************************************/
template <typename T>
int StackLimit<T>::Size() const
{
	return m_top + 1;
}
/***************************************************************************************************
*	Purpose: checks to see if the stack is empty
*
*	Entry: none
*
*	Exit: returns true if the stack has nothing in it
***************************************************************************************************/
template <typename T>
bool StackLimit<T>::IsEmpty() const
{
	return m_top < 0;
}
/***************************************************************************************************
*	Purpose: checks to see if the stack is full
*
*	Entry: none
*
*	Exit: returns true if the stack is full
***************************************************************************************************/
template <typename T>
bool StackLimit<T>::IsFull() const
{
	return m_top == m_size - 1;
}
#endif