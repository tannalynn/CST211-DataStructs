/***************************************************************************************************
* Author:						Tanna McClure
* File:							Row.h
* Date Created:					1/7/2015
*
* Modification Date: 			1/8/2015
* Modification: 				Finished writing function definitions
*
***************************************************************************************************/
/***************************************************************************************************
*	Class: Row
*
*	Purpose: 
*		Helper class for the 2D array class
*
*	Manager Functions:
*		Row(const Array_2D<T> & array, int row);
*			2 arg ctor
*		Row(const Row & copy);
*			Copy ctor
*		~Row();
*			Dtor
*
*	Methods:
*		T & operator [] (int i);
*			[] operator - returns a element in the 2darray
*		const T & operator [] (int i) const;
*			[] operator - returns a CONST element in the 2darray
*		Array_2D<T> & GetArray() const;
*			returns m_array
*		int GetRow() const;
*			gets the row
*		void SetRow(int i);
*			sets the row to what is passed in
*
***************************************************************************************************/
#ifndef ROW_H
#define ROW_H
#include "Exception.h"

template <typename T>
class Row
{
	template <typename T>
	friend class Array_2D;

public:
			//[] operator
	const T & operator [] (int i) const;
	T & operator [] (int i);
			//Destructor
	~Row();

private:
			//2 arg ctor
	Row(Array_2D<T> & array, int row);
	Row(const Array_2D<T> & array, int row);
	
			//Copy Constructor
	Row(const Row & copy);

			//getters
	Array_2D<T> & GetArray() const;
	int GetRow() const;
			//setters
	void SetRow(int i);

	const Array_2D<T> & m_array2D;
	int m_row;

};


/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: 2 arg ctor
*
*	Entry: the Array_2D objects and row
*
*	Exit: Row is created with the arguments passed in
***************************************************************************************************/
template <typename T>
Row<T>::Row(Array_2D<T> & ar, int row) : m_array2D(ar), m_row(row)
{
	if (m_row < 0)
		throw Exception("Exception:  Row - 2 arg ctor:   Invalid Row ");
}
/***************************************************************************************************
*	Purpose: 2 arg ctor
*
*	Entry: the Array_2D objects and row
*
*	Exit: Row is created with the arguments passed in
***************************************************************************************************/
template <typename T>
Row<T>::Row(const Array_2D<T> & ar, int row) : m_array2D(ar), m_row(row)
{
	if (m_row < 0)
		throw Exception("Exception:  Row - 2 arg ctor:   Invalid Row ");
}
/***************************************************************************************************
*	Purpose: copy ctor
*	
*	Entry: a row to copy
*	
*	Exit: this is created and is the same as the row passed in
***************************************************************************************************/
template <typename T>
Row<T>::Row(const Row & copy) : m_array2D(copy.m_array2d), m_row(copy.m_row)
{ }
/***************************************************************************************************
*	Purpose: dtor
*	
*	Entry: none
*	
*	Exit: object is destroyed
***************************************************************************************************/
template <typename T>
Row<T>::~Row()
{
	m_row = 0;
}
/***************************************************************************************************
*	Purpose: returns a reference to the array
*
*	Entry: none
*
*	Exit: returns m_array2D
***************************************************************************************************/
template <typename T>
Array_2D<T> & Row<T>::GetArray() const
{
	return m_array2D;
}
/***************************************************************************************************
*	Purpose: gets the row
*
*	Entry: none
*
*	Exit: returns m_row
***************************************************************************************************/
template <typename T>
int Row<T>::GetRow() const
{
	return m_row;
}
/***************************************************************************************************
*	Purpose: sets the row
*
*	Entry: the row number to set it to
*
*	Exit: m_row is now equal to i
***************************************************************************************************/
template <typename T>
void Row<T>::SetRow(int i)
{
	if (i < 0)
		throw Exception("Exception:  Row - SetRow:   Invalid Row")
	m_row = i;
}
/***************************************************************************************************
*	Purpose: gets an element from the row in the list 
*	
*	Entry: the column in the row to get
*	
*	Exit: returns a reference to the data at that location
***************************************************************************************************/
template <typename T>
T & Row<T>::operator[](int i)
{
	if (i < 0 || i >= m_array2D.GetColumn())
		throw Exception("Exception:   Row - [] operator:   Invalid Position");
	return const_cast<T&>(m_array2D.Select(m_row, i));
}
/***************************************************************************************************
*	Purpose: gets an element from the row in the list   CONST
*
*	Entry: the column in the row to get
*
*	Exit: returns a reference to the data at that location
***************************************************************************************************/
template <typename T>
const T & Row<T>::operator[](int i) const
{
	if (i < 0 || i >= m_array2D.GetColumn())
		throw Exception("Exception:   Row - [] operator:   Invalid Position");
	return m_array2D.Select(m_row, i);
}
#endif