/***************************************************************************************************
* Author:						Tanna McClure
* File:							Array_2D.h
* Date Created:					1/7/2015
*
* Modification Date: 			1/9/2015
* Modification: 				Finished
*		  
***************************************************************************************************//***************************************************************************************************
*	Class: Array_2D
* 
*	Purpose: 
*		2D array class. 
* 
*	Manager Functions: 
*		Array_2D();
*			Default Constructor
*		Array_2D(int row, int col = 0);
*			2 arg ctor
*		Array_2D(const Array_2D<T> & copy);
*			Copy Constructor
*		~Array_2D();
*			dtor
*		Array_2D<T> & operator = (const Array_2D<T> & rhs);
*			Assignment Operator
*
*	Methods: 
*		Row<T> operator [] (int i) const;
*			[] operator - returns  a row object that you can use to get an element from the array
*		const Row<T> Array_2D<T>::operator[](int i) const
*			[] operator - returns a  CONST row object that you can use to get an element from the array
*		int GetRow() const;
*			gets the number of rows in the array
*		int GetColumn() const;
*			gets the number of columns in the array
*		void SetRow(int i);
*			changes the number of rows in the array
*		void SetColumn(int i);
*			changes the number
*		T & Select(int row, int col) const;
*			returns a specific element in the array
*
***************************************************************************************************/
#ifndef ARRAY_2D_H
#define ARRAY_2D_H
#include "Array_1D.h"
#include "Row.h"

template <typename T>
class Array_2D
{
public:
			//Default Constructor
	Array_2D();
			//2 arg ctor
	Array_2D(int row, int col = 0);
			//Copy Constructor
	Array_2D(const Array_2D<T> & copy);
			//Destructor
	~Array_2D();
			//Assignment Operator
	Array_2D<T> & operator = (const Array_2D<T> & rhs);
			//[] operator
	Row<T> operator [] (int i);
	const Row<T> operator[](int i) const;

			//getters 
	int GetRow() const;
	int GetColumn() const;
			//setters
	void SetRow(int i);
	void SetColumn(int i);

			//Deletes everything in the Array
	void Purge();

			//returns the data from a specific spot in the 2d array
	T & Select(int row, int col);
	const T & Select(int row, int col) const;

private:


	Array_1D<T> m_array;
	int m_row;
	int m_col;

};
/***************************************************************************************************
*									Function Definitions										     
***************************************************************************************************/ 
/***************************************************************************************************
*	Purpose: default ctor
*
*	Entry: none
*
*	Exit: initializes everything to zero
***************************************************************************************************/
template <typename T>
Array_2D<T>::Array_2D() : m_col(0), m_row(0)
{ }
/***************************************************************************************************
*	Purpose: 2 arg ctor
* 
*	Entry: number of rows  and columns
* 
*	Exit: the array is set to the length needed for the number of rows and columns passed in
*
*	Exception: Throws an exception if the row or column passed in is negative
***************************************************************************************************/
template <typename T>
Array_2D<T>::Array_2D(int row, int col /*= 0*/) : m_row(row), m_col(col)
{ 
	if (m_row < 0 || m_col < 0)
	{
		m_row = m_col = 0;
		throw Exception("Exception:   Array_2D - 2 arg ctor:    Invalid row or column");
	}
	m_array.SetLength(m_col*m_row);
}
/***************************************************************************************************
*	Purpose: copy ctor
*
*	Entry: the array to copy
*
*	Exit: this is equal to the array passed in
***************************************************************************************************/
template <typename T>
Array_2D<T>::Array_2D(const Array_2D<T> & copy) : m_row(copy.m_row), m_col(copy.m_col), 
												  m_array(copy.m_array)
{ }
/***************************************************************************************************
*	Purpose: dtor
*
*	Entry: none
*
*	Exit: object is destroyed and values set back to 0
***************************************************************************************************/
template <typename T>
Array_2D<T>::~Array_2D()
{
	Purge();
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the array to copy
*
*	Exit: this is now the same as rhs
***************************************************************************************************/
template <typename T>
Array_2D<T> & Array_2D<T>::operator=(const Array_2D<T> & rhs)
{
	m_row = rhs.m_row;
	m_col = rhs.m_col;
	m_array = rhs.m_array;
	return *this;
}
/***************************************************************************************************
*	Purpose: gets the row to access 
*
*	Entry: the row
*
*	Exit: the Row object is returned containing the row to access and a ref to the 2d array
***************************************************************************************************/
template <typename T>
Row<T> Array_2D<T>::operator[](int i)
{
	if (i < 0 || i >= m_row)
		throw Exception("Exception:   Array_2D - [] operator:   Invalid position");
	return Row<T>(*this, i);
}
/***************************************************************************************************
*	Purpose: gets the row to access  CONST
*
*	Entry: the row
*
*	Exit: the Row object is returned containing the row to access and a ref to the 2d array
***************************************************************************************************/
template <typename T>
const Row<T> Array_2D<T>::operator[](int i) const
{
	if (i < 0 || i >= m_row)
		throw Exception("Exception:   Array_2D - [] operator:   Invalid position");
	return Row<T>(*this, i);
}
/***************************************************************************************************
*	Purpose: gets the number of rows in the array
*
*	Entry: none
*
*	Exit: returns m_row
***************************************************************************************************/
template <typename T>
int Array_2D<T>::GetRow() const
{
	return m_row;
}
/***************************************************************************************************
*	Purpose: gets the number of columns in the array
*
*	Entry: none
*
*	Exit: returns m_col
***************************************************************************************************/
template <typename T>
int Array_2D<T>::GetColumn() const
{
	return m_col;
}
/***************************************************************************************************
*	Purpose: sets the number of rows
*
*	Entry: the new number of rows
*
*	Exit: the array has been changed
***************************************************************************************************/
template <typename T>
void Array_2D<T>::SetRow(int i)
{
	if (i < 0)
		throw Exception("Exception:   Array_2D - SetRow:   Invalid Row");
	if (m_row != i)
	{
		m_row = i;
		m_array.SetLength(m_row * m_col);
	}
}
/***************************************************************************************************
*	Purpose: sets the number of columns in the array
*
*	Entry: the number of columns
*
*	Exit: array size is changed
***************************************************************************************************/
template <typename T>
void Array_2D<T>::SetColumn(int new_col)
{
	if (new_col < 0)
		throw Exception("Exception:   Array_2D - SetColumn:   Invalid Column");
	
	if (m_col != new_col)
	{
		Array_1D<T> temp(new_col * m_row);

		int col_min = new_col < m_col ? new_col : m_col;

		for (int i(0), row(0); row < m_row; row++)
			for (int j(0); j < col_min; j++)
				temp[(row*new_col) + j] = m_array[(row*m_col) + j];
	
		m_col = new_col;
		m_array = temp;
	}
}
/***************************************************************************************************
*	Purpose: returns an element in the array at a specified location
*
*	Entry: the row and column 
*
*	Exit: the data at that part of the array is returned by reference
***************************************************************************************************/
template <typename T>
T & Array_2D<T>::Select(int row, int col)
{
	if (row > m_row || row < 0   ||   col > m_col || col < 0)
		throw Exception("Exception:   Array_2D - Select:  Invalid Row or Column");

	return m_array[(row* m_col) + col];
}
/***************************************************************************************************
*	Purpose: returns an element in the array at a specified location CONST
*
*	Entry: the row and column
*
*	Exit: the data at that part of the array is returned by reference
***************************************************************************************************/
template <typename T>
const T & Array_2D<T>::Select(int row, int col) const
{
	if (row > m_row || row < 0 || col > m_col || col < 0)
		throw Exception("Exception:   Array_2D - Select:  Invalid Row or Column");

	return m_array[(row* m_col) + col];
}
/***************************************************************************************************
*	Purpose: empties the array
*
*	Entry: none
*
*	Exit: array is set back to size 0
***************************************************************************************************/
template <typename T>
void Array_2D<T>::Purge()
{
	m_row = 0;
	m_col = 0;
	m_array.SetLength(0);
}
#endif