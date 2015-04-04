/***************************************************************************************************
* Author:						Tanna McClure
* File:							Exception.h
* Date Created:					1/5/2015
*
* Modification Date: 			1/6/2015
* Modification: 				Finished
*
***************************************************************************************************/
/***************************************************************************************************
*	Class: Exception
* 
*	Purpose:
*		Holds a message for an exception
*
*	Manager Functions:
*		Exception();
*			Default Constructor
*		Exception(const char * msg);
*			1 arg constructor
*		Exception(const Exception & copy);
*			Copy Constructor
*		Exception & operator = (const Exception & rhs);
*			Assignment Operator
*		~Exception();
*			Destructor
*
*	Methods:
*		void SetMessage(char * msg);
*			sets m_msg
*		const char * GetMessage() const;
*			returns m_msg
*		friend ostream & operator << (ostream & in, const Exception & ex);
*			overloaded ostream operator
*
***************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
using std::ostream;

class Exception
{
public:
			//Default Constructor
	Exception();
			//1 arg constructor
	Exception(const char * msg);
			//Copy Constructor
	Exception(const Exception & copy);
			//Destructor
	~Exception();
			//Assignment Operator
	Exception & operator = (const Exception & rhs);

			//returns m_msg
	const char * GetMessage() const;
			//sets m_msg
	void SetMessage(const char * msg);
			

			//overloaded ostream operator
	friend ostream & operator << (ostream & in, const Exception & ex);

private:
	char * m_msg;

};
#endif