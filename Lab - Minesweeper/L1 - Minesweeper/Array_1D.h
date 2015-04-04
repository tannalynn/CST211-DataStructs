/***************************************************************************************************
*	Class: Array_1D
* 
*	Constructors:
*			
*		Array_1D();
*			Default Constructor
*		Array_1D(int length, int start);
*			2 arg constructor
*		Array_1D(const Array_1D & copy);
*			Copy Constructor
*
*	Mutators:
*					
*		~Array_1D();
*			Destructor
*		Array_1D & operator = (const Array_1D & rhs);
*			Assignment Operator
*		void SetStartIndex(int index);
*			sets the starting index
*		void SetLength(int len);
*			sets the length of the array
*		T & operator [] (int i) const;
*			returns the ith element in the array
*
*
*	Methods:
*				
*		int GetLength() const;
*			gets the length of the array
*		int GetStartIndex() const;
*			returns the starting index
*
***************************************************************************************************/
#ifndef ARRAY_1D_H
#define ARRAY_1D_H
#include "Exception.h"

template <typename T>
class Array_1D
{
public:
			//Default Constructor
	Array_1D();
			//2 arg constructor
	Array_1D(int length, int start = 0);
			//Copy Constructor
	Array_1D(const Array_1D & copy);
			//Destructor
	~Array_1D();
			//Assignment Operator
	Array_1D & operator = (const Array_1D & rhs);

			//returns the starting index
	int GetStartIndex() const;
			//sets the starting index
	void SetStartIndex(int index);
			//gets the length of the array
	int GetLength() const;
			//sets the length of the array
	void SetLength(int len);

			//returns the ith element in the array
	const T & operator [] (int i) const;
			//returns the ith element in the array
	T & operator [] (int i);

private:
	T * m_array;
	int m_length;
	int m_start_index;

};

/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/

/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: everything set to zero
***************************************************************************************************/
template <typename T>
Array_1D<T>::Array_1D() : m_array(nullptr), m_length(0), m_start_index(0)
{ }

/***************************************************************************************************
*	Purpose: 2 arg constructor
*
*	Entry: length and starting index
*
*	Exit: an array of length length array
***************************************************************************************************/
template <typename T>
Array_1D<T>::Array_1D(int length, int start) : m_array(nullptr), m_length(length), 
											   m_start_index(start)
{
	if (m_length < 0)
	{
		m_length = 0;
		throw Exception("Exception:   Array_1D - 2 arg ctor:   Invalid Length");
	}
	if (m_length > 0)
		m_array = new T[m_length];
}

/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the object to copy
*
*	Exit: this is now equal to what was passed in
***************************************************************************************************/
template <typename T>
Array_1D<T>::Array_1D(const Array_1D & copy) : m_array(nullptr), m_length(copy.m_length), 
											   m_start_index(copy.m_start_index)
{
	m_array = new T[m_length];

	for (int i(0); i < m_length; i++)
		m_array[i] = copy.m_array[i];
}

/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: deletes m_array and sets all members to 0
*
*	Exit: everything is 0
***************************************************************************************************/
template <typename T>
Array_1D<T>::~Array_1D()
{
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}

/***************************************************************************************************
*	Purpose: overloaded assignment operator
*
*	Entry: the array to copy
*
*	Exit: this is now the same as the rhs
***************************************************************************************************/
template <typename T>
Array_1D<T> & Array_1D<T>::operator=(const Array_1D & rhs)
{
	if (this != &rhs)
	{
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;

		delete[] m_array;
		m_array = new T[m_length];

		for (int i(0); i < m_length; i++)
			m_array[i] = rhs.m_array[i];
	}
	return *this;
}

/***************************************************************************************************
*	Purpose: gets the starting index of the array
*
*	Entry: none
*
*	Exit: returns m_start_index
***************************************************************************************************/
template <typename T>
int Array_1D<T>::GetStartIndex() const
{
	return m_start_index;
}

/***************************************************************************************************
*	Purpose: changes the starting index
*
*	Entry: the number to set the index to
*
*	Exit: m_start_index is changed to the value passed in
***************************************************************************************************/
template <typename T>
void Array_1D<T>::SetStartIndex(int index)
{
	m_start_index = index;
}

/***************************************************************************************************
*	Purpose: gets the number of elements in the array
*
*	Entry: none
*
*	Exit: returns m_length
***************************************************************************************************/
template <typename T>
int Array_1D<T>::GetLength() const
{
	return m_length;
}

/***************************************************************************************************
*	Purpose: sets the length of the array
*
*	Entry: the new length
*
*	Exit: the array is changed to the length passed in
***************************************************************************************************/
template <typename T>
void Array_1D<T>::SetLength(int len)
{
	T * temp = m_array;

	if (len < 0)
		throw Exception("Exception:   Array_1D - SetLength:   Invalid Length");
	if (len != 0)
	{
		m_array = new T[len];
		int min_len(len < m_length ? len : m_length); 
		for (int i(0); i < min_len; i++)
			m_array[i] = temp[i];
	}
	else
		m_array = nullptr;

	delete[] temp;
	m_length = len;
}

/***************************************************************************************************
*	Purpose: overloaded brackets   CONST
*
*	Entry: the position in the array to return
*
*	Exit: returns the element at position 1 
*
*	Exception: throws invalid position if the position is invalid
***************************************************************************************************/
template <typename T>
const T & Array_1D<T>::operator[](int i) const
{
	if (i < m_start_index || i > m_start_index + m_length - 1) //if i is out of bounds
		throw Exception("Exception:   Array_1D - []:   Invalid Position"); 

	return m_array[i - m_start_index];
}
/***************************************************************************************************
*	Purpose: overloaded brackets
*
*	Entry: the position in the array to return
*
*	Exit: returns the element at position 1
*
*	Exception: throws invalid position if the position is invalid
***************************************************************************************************/
template <typename T>
T & Array_1D<T>::operator[](int i)
{
	if (i < m_start_index || i > m_start_index + m_length - 1) //if i is out of bounds
		throw Exception("Exception:   Array_1D - []:   Invalid Position");

	return m_array[i - m_start_index];
}
#endif