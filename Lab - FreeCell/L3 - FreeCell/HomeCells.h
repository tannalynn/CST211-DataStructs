/***************************************************************************************************
* Author:						Tanna McClure
* File:							HomeCells.h
* Date Created:					2/3/2015
*
* Modification Date: 			2/4/2015
* Modification: 				commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: HomeCells
*
*	Purpose: 
*		Manages the home cells for the game
*
*	Manager Functions: 
*		HomeCells();
*			Default Constructor
*		HomeCells(const HomeCells & copy);
*			Copy Constructor
*		~HomeCells();
*			Destructor
*		HomeCells & operator = (const HomeCells & rhs);
*			Assignment operator
*
*	Methods: 
*		void Draw();
*			Draws the cards in the free cells
*		bool HomeFull();
*			checks if all are full
*		bool AddCard(Card card);
*			adds a card to the home cells - returns true if successful
*		void Clear();
*			empties the stack
*
***************************************************************************************************/
#ifndef HOMECELLS_H
#define HOMECELLS_H
#include "StackLimit.h"
#include "Card.h"

class HomeCells
{
public:
			//Default Constructor
	HomeCells();
			//Copy Constructor
	HomeCells(const HomeCells & copy);
			//Destructor
	~HomeCells();
			//Assignment Operator
	HomeCells & operator = (const HomeCells & rhs);

			//Draws the cards in the free cells
	void Draw();
			//checks if all are full
	bool HomeFull();
			//adds a card to the home cells - returns true if successful
	bool AddCard(Card card);
			//empties the stack
	void Clear();

	static const int HOME_AMOUNT = 4;

private:
	Array_1D<StackLimit<Card> *> m_cells;
};
#endif