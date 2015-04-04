/***************************************************************************************************
* Author:						Tanna McClure
* File:							Cell.h
* Date Created:					1/11/2015
*
* Modification Date: 			1/12/15
* Modification: 				finished
*
***************************************************************************************************/
/***************************************************************************************************
*	Class: Cell
*
*	Purpose: 
*		Class to keep track of each cell
*
*	Manager Functions: 
*		Cell();
*			Default Constructor
*		Cell(const Cell & copy);
*			Copy Constructor
*		~Cell();
*			Destructor
*		Cell & operator = (const Cell & rhs);
*			Assignment operator
*
*	Methods: 
*		STATUS GetStatus() const;
*		TYPE GetType() const;
*			Getters
*		void SetStatus(STATUS stat);
*		void SetType(TYPE ty);
*			Setters
*
***************************************************************************************************/
#ifndef CELL_H
#define CELL_H

class Cell
{
	friend class Board; 
public:
	static enum STATUS { FLAGGED, HIDDEN, SHOWN };
	static enum TYPE { EMPTY, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, BOMB };

			//Default Constructor
	Cell();
			//Copy Constructor
	Cell(const Cell & copy);
			//Destructor
	~Cell();
			//Assignment Operator
	Cell & operator = (const Cell & rhs);

			//Getters
	STATUS GetStatus() const;
	TYPE GetType() const;

			//Setters
	void SetStatus(STATUS stat);
	void SetType(TYPE ty);

private:
	STATUS m_status;
	TYPE m_type;
};
#endif