/***************************************************************************************************
* Author:						Tanna McClure
* File:							Exception.cpp
* Date Created:					1/5/2015
*
* Modification Date: 			1/6/2015
* Modification: 				Finished
*
***************************************************************************************************/
#include "Exception.h"

static const char * DEFAULT ("Default Exception"); //file scope

/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: m_msg is set to the default exception
***************************************************************************************************/
Exception::Exception() : m_msg(nullptr)
{
	m_msg = new char[strlen(DEFAULT) + 1];
	strcpy(m_msg, DEFAULT);
}

/***************************************************************************************************
*	Purpose: 1 arg constructor
*
*	Entry: the char string to set m_msg to
*
*	Exit: m_msg is set to msg, unless msg was null
***************************************************************************************************/
Exception::Exception(const char * msg) : m_msg(nullptr)
{
	SetMessage(msg);
}

/***************************************************************************************************
*	Purpose: copies an existing exception
*
*	Entry: the exception to copy
*
*	Exit: this is a copy of exception
***************************************************************************************************/
Exception::Exception(const Exception & copy) : m_msg(nullptr)
{
	SetMessage(copy.m_msg);
}

/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: m_msg is deleted
***************************************************************************************************/
Exception::~Exception()
{
	delete[] m_msg;
	m_msg = nullptr;
}

/***************************************************************************************************
*	Purpose: overloaded assignment operator
*
*	Entry: passes in the exception to copy
*
*	Exit: this is now the same as rhs
***************************************************************************************************/
Exception & Exception::operator=(const Exception & rhs)
{
	if (this != &rhs)
	{
		delete[] m_msg;

		if (rhs.m_msg)
		{
			m_msg = new char[strlen(rhs.m_msg) + 1];
			strcpy(m_msg, rhs.m_msg);
		}
		else
		{
			m_msg = new char[strlen(DEFAULT) + 1];
			strcpy(m_msg, DEFAULT);
		}

	}
	return *this; 
}

/***************************************************************************************************
*	Purpose: returns a pointer to the character array 
*
*	Entry: none
*
*	Exit: returns m_msg
***************************************************************************************************/
const char * Exception::GetMessage() const
{
	return m_msg;
}

/***************************************************************************************************
*	Purpose: sets m_msg to msg passed in
*
*	Entry: the msg to set m_msg to.
* 
* 	Exit: 
***************************************************************************************************/
void Exception::SetMessage(const char * msg)
{
	delete[] m_msg;

	if (msg)
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
	else
	{
		m_msg = new char[strlen(DEFAULT) + 1];
		strcpy(m_msg, DEFAULT);
	}
}

/***************************************************************************************************
*	Purpose: ostream operator
*
*	Entry: ostream and exception
*
*	Exit: exception inserted into ostream
***************************************************************************************************/
ostream & operator << (ostream & in, const Exception & ex)
{
	if (ex.m_msg)
		in << ex.m_msg;
	return in;
}