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
*	Constructors:
*			
*		Exception();
*			Default Constructor
*		Exception(const char * msg);
*			1 arg constructor
*		Exception(const Exception & copy);
*			Copy Constructor
*
*	Mutators:
*			
*		void SetMessage(char * msg);
*			sets m_msg
*		Exception & operator = (const Exception & rhs);
*			Assignment Operator
*		~Exception();
*			Destructor
*
*	Methods:
*			
*		const char * GetMessage() const;
*			returns m_msg
*		friend ostream & operator << (ostream & in, const Exception & ex);
*			overloaded ostream operator
*
***************************************************************************************************/
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
			//s

			//overloaded ostream operator
	friend ostream & operator << (ostream & in, const Exception & ex);

private:
	char * m_msg;

};
#endif











