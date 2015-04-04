/***************************************************************************************************
* Author:						Tanna McClure
* File:							AbstractIterator.h
* Date Created:					2/11/2015
*
* Modification Date: 			2/12/2015
* Modification: 				finished commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: AbstractIterator
*
*	Purpose: 
*		Abstract base class for iterators
*
*	Manager Functions: 
*
*	Methods: 
*		virtual void Reset() = 0;
*			starts at the beginning of the structure
*		virtual void MoveNext() = 0;
*			moves to the next item
*		virtual bool IsDone() = 0;
*			checks if at the end
*		virtual T & GetCurrent() = 0;
*			can change data at current node
*
***************************************************************************************************/
#ifndef ABSTRACTITERATOR_H
#define ABSTRACTITERATOR_H

template <typename T>
class AbstractIterator
{
public:
			//starts at the beginning of the structure
	virtual void Reset() = 0;
			//moves to the next item
	virtual void MoveNext() = 0;
			//checks if at the end
	virtual bool IsDone() = 0;
			//can change data at current node
	virtual T & GetCurrent() = 0;

};
#endif