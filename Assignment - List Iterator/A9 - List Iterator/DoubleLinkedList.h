/***************************************************************************************************
* Author:						Tanna McClure
* File:							DoubleLinkedList.h
* Date Created:					1/6/2015
*
* Modification Date: 			1/28/2015
* Modification: 				now throws exception class rather than cstrings
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: DoubleLinkedList
* 
*	Purpose:
*		Linked list
*
*	Manager Functions:
*		DoubleLinkedList();
*			Default Constructor
*		DoubleLinkedList(const T & first);
*			1 arg ctor
*		DoubleLinkedList(const DoubleLinkedList & copy);
*			Copy Constructor
*		~DoubleLinkedList();
*			Destructor
*		DoubleLinkedList & operator = (const DoubleLinkedList & rhs);
*			Assignment Operator
*
*	Methods:
*		const T & First() const;
*			returns the first element
*		const T & Last() const;
*			returns the last element
*		bool isEmpty() const;
*			checks if the list is empty
*		void Prepend(const T & element);
*			adds an element to the front of the list
*		void Append(const T & element);
*			adds an element to the end of the list
*		void InsertBefore(int insert, int element);
*			inserts the first before the second arg
*		void InsertAfter(int insert, int element);
*			inserts the first after the second arg
*		void Purge();
*			removes all elements in the list
*		void Extract(const T & data);
*			removes one element in the list
*		T RemoveFirst();
*			removes the first item in the list
*		T RemoveLast();
*			removes the last item in the list
*
***************************************************************************************************/
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "Node.h"
#include "Exception.h"

template <typename T>
class DoubleLinkedList
{
	template <typename T>
	friend class ForwardIterator;
	template <typename T>
	friend class BackwardsIterator;
public:
			//Default Constructor
	DoubleLinkedList();
			//1 arg ctor
	DoubleLinkedList(const T & first);
			//Copy Constructor
	DoubleLinkedList(const DoubleLinkedList & copy);
			//Destructor
	~DoubleLinkedList();
			//Assignment Operator
	DoubleLinkedList & operator = (const DoubleLinkedList & rhs);

			//returns the first element
	const T & First() const;
			//returns the last element
	const T & Last() const;

			//checks if the list is empty
	bool isEmpty() const;

			//adds an element to the front of the list
	void Prepend(const T & element);
			//adds an element to the end of the list
	void Append(const T & element);

			//inserts the first before the second arg
	void InsertBefore(int insert, int element);
			//inserts the first after the second arg
	void InsertAfter(int insert, int element);

			//removes all elements in the list
	void Purge();
			//removes one element in the list
	void Extract(const T & data);

			//removes the first item in the list
	T RemoveFirst();
			//removes the last item in the list
	T RemoveLast();

private:
	Node<T> * m_head;
	Node<T> * m_tail;
};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/

/***************************************************************************************************
*	Purpose: default ctor
*
*	Entry: none
*
*	Exit: m_head and m_tail are set to nullptr
***************************************************************************************************/
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : m_head(nullptr), m_tail(nullptr)
{ }
/***************************************************************************************************
*	Purpose: 1 arg ctor
*
*	Entry: an element to put in the list
*
*	Exit: the list is created
***************************************************************************************************/
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const T & first) : m_head(nullptr), m_tail(nullptr)
{
	m_head = m_tail = new Node<T>(first);
}
/***************************************************************************************************
*	Purpose: copy ctor
*
*	Entry: the list to copy
*
*	Exit: this has been created and is the same as the list passed in
***************************************************************************************************/
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList & copy) : m_head(nullptr), m_tail(nullptr)
{
	*this = copy;
}
/***************************************************************************************************
*	Purpose: dtor 
*
*	Entry: none
*
*	Exit: the object is destroyed
***************************************************************************************************/
template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	Purge();
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the list to make this equal to
*
*	Exit: this is now equal to rhs
***************************************************************************************************/
template <typename T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator=(const DoubleLinkedList & rhs)
{
	if (this != &rhs)
	{
		Purge(); 
		Node<T> * travel = rhs.m_head;
		while (travel)
		{
			Append(travel->m_data);
			travel = travel->m_next;
		}
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: gets the first item 
*
*	Entry: none
*
*	Exit: returns a const reference to the first element in the list
*	
*	Exception: throws an exception if the list is empty
***************************************************************************************************/
template <typename T>
const T & DoubleLinkedList<T>::First() const
{
	if (!m_head) //if the list is empty
		throw Exception("Exception:  DoubleLinkedList - First:   Empty List");
	return m_head->m_data;
}
/***************************************************************************************************
*	Purpose: gets the last item
*
*	Entry: none
*
*	Exit: returns a const reference to the last element in the list
*
*	Exception: throws an exception if the list is empty
***************************************************************************************************/
template <typename T>
const T & DoubleLinkedList<T>::Last() const
{
	if (!m_head) //if the list is empty
		throw Exception("Exception:  DoubleLinkedList - Last:   Empty List");
	return m_tail->m_data;
}
/***************************************************************************************************
*	Purpose: sees if the list is empty
*
*	Entry: none
*
*	Exit: returns true if the list is empty, otherwise false
***************************************************************************************************/
template <typename T>
bool DoubleLinkedList<T>::isEmpty() const
{
	return !m_head;
}
/***************************************************************************************************
*	Purpose: adds an item to the beginning of the list
*
*	Entry: the item to put in the list
*
*	Exit: the list now starts with the element passed in
***************************************************************************************************/
template <typename T>
void DoubleLinkedList<T>::Prepend(const T & element)
{
	if (!m_head) // list is empty
		m_head = m_tail = new Node<T>(element);
	else		 
	{
		m_head->m_prev = new Node<T>(element);
		m_head->m_prev->m_next = m_head; //change new heads next ptr
		m_head = m_head->m_prev;
	}

}
/***************************************************************************************************
*	Purpose: adds an item to the end of the list
*
*	Entry: the item to put in the list
*
*	Exit: the list now ends with the element passed in
***************************************************************************************************/
template <typename T>
void DoubleLinkedList<T>::Append(const T & element)
{
	if (!m_head)
		m_head = m_tail = new Node<T>(element);
	else
	{
		m_tail->m_next = new Node<T>(element);
		m_tail->m_next->m_prev = m_tail; //changes the new tails prev ptr
		m_tail = m_tail->m_next;
	}
}
/***************************************************************************************************
*	Purpose: inserts an element  before another element
*
*	Entry: the element to insert, and the element to put it before
*
*	Exit: the element is inserted into the list
***************************************************************************************************/
template <typename T>
void DoubleLinkedList<T>::InsertBefore(int insert, int element)
{
	if (!m_head)
		throw Exception("Exception:  DoubleLinkedList - InsertBefore:   Empty List");
	
	bool found(false);
	Node<T> * travel = m_head;

	while (travel && !found)
	{
		if (travel->m_data == element)
		{
			found = true;
			Node<T> * temp = new Node<T>(insert);
			temp->m_next = travel;
			temp->m_prev = travel->m_prev;
			if (travel == m_head)
				m_head = temp;
			else
				travel->m_prev->m_next = temp;
			travel->m_prev = temp;
		}
		else
			travel = travel->m_next;
	}
	
	if (!found)
		throw Exception("Exception:  DoubleLinkedList - InsertBefore:   Item not found in list");
}
/***************************************************************************************************
*	Purpose: inserts an element  after another element
*
*	Entry: the element to insert, and the element to put it after
*
*	Exit: the element is inserted into the list
***************************************************************************************************/
template <typename T>
void DoubleLinkedList<T>::InsertAfter(int insert, int element)
{
	if (!m_head)
		throw Exception("Exception:  DoubleLinkedList - InsertAfter:   Empty List");

	bool found(false);
	Node<T> * travel = m_head;

	while (travel && !found)
	{
		if (travel->m_data == element)
		{
			found = true;
			Node<T> * temp = new Node<T>(insert);
			temp->m_next = travel->m_next;
			temp->m_prev = travel;
			if (travel == m_tail)
				m_tail = temp;
			else
				travel->m_next->m_prev = temp;
			travel->m_next = temp;
		}
		else
			travel = travel->m_next;
	}

	if (!found)
		throw Exception("Exception:  DoubleLinkedList - InsertAfter:   Item not found in list");
}
/***************************************************************************************************
*	Purpose: erases everything in the list
*
*	Entry: none
*
*	Exit: this is now an empty list
***************************************************************************************************/
template <typename T>
void DoubleLinkedList<T>::Purge()
{
	if (m_head)
	{
		Node<T> * travel = m_head;

		while (travel->m_next)
		{
			travel = travel->m_next;
			delete travel->m_prev;
		}
		delete m_tail; //delete the last element

		m_tail = m_head = nullptr;
	}
}
/***************************************************************************************************
*	Purpose: removes a specific element from the list
*
*	Entry: the data of the element to be removed
*
*	Exit: the list no longer has that data in it
***************************************************************************************************/
template <typename T>
void DoubleLinkedList<T>::Extract(const T & data)
{
	if (!m_head)
		throw Exception("Exception:  DoubleLinkedList - Extract:   Empty List");

	bool found(false);
	Node<T> * travel = m_head;

	while (travel && !found)
	{
		if (travel->m_data == data)
		{
			found = true;
			if (m_head == m_tail) //only 1 item in the list
				m_head = m_tail = nullptr;

			else if (travel == m_head) //if extracting the first item
			{
				m_head = m_head->m_next;
				m_head->m_prev = nullptr;
			}
			else if (travel == m_tail) //if extracting the last item
			{
				m_tail = m_tail->m_prev;
				m_tail->m_next = nullptr;
			}
			else
			{
				travel->m_next->m_prev = travel->m_prev;
				travel->m_prev->m_next = travel->m_next;
			}

			delete travel;
		}
		else
			travel = travel->m_next;
	}

	if (!found)
		throw Exception("Exception:  DoubleLinkedList - Extract:   Item not found in list");
}
/***************************************************************************************************
*	Purpose: removes the item at the beginning of the list
*
*	Entry: none
*
*	Exit: returns a copy of the item that was just removed
***************************************************************************************************/
template <typename T>
T DoubleLinkedList<T>::RemoveFirst()
{
	if (!m_head) //if the list is empty
		throw Exception("Exception:  DoubleLinkedList - RemoveFirst:   Empty List");
	T temp = m_head->m_data;

	if (m_head->m_next) //not the only thing in list
	{
		m_head = m_head->m_next;
		delete m_head->m_prev;
		m_head->m_prev = nullptr;
	}
	else //1 item in list
	{
		delete m_head;
		m_head = m_tail = nullptr;
	}

	return temp;
}
/***************************************************************************************************
*	Purpose: removes the item at the end of the list
*
*	Entry: none
*
*	Exit: returns a copy of the item that was just removed
***************************************************************************************************/
template <typename T>
T DoubleLinkedList<T>::RemoveLast()
{
	if (!m_head) //if the list is empty
		throw Exception("Exception:  DoubleLinkedList - RemoveLast:   Empty List");
	T temp = m_tail->m_data;

	if (m_tail->m_prev) //not the only thing in list
	{
		m_tail = m_tail->m_prev;
		delete m_tail->m_next;
		m_tail->m_next = nullptr;
	}
	else //1 item in list
	{
		delete m_tail;
		m_head = m_tail = nullptr;
	}

	return temp;
}
#endif