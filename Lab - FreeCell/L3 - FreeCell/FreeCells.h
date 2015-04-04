/***************************************************************************************************
* Author:						Tanna McClure
* File:							FreeCells.h
* Date Created:					2/2/2015
*
* Modification Date: 			2/4/2015
* Modification: 				commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: FreeCells
*
*	Purpose: 
*		Manages the free cells for the game
*
*	Manager Functions: 
*		FreeCells();
*			Default Constructor
*		FreeCells(const FreeCells & copy);
*			Copy Constructor
*		~FreeCells();
*			Destructor
*		FreeCells & operator = (const FreeCells & rhs);
*			Assignment operator
*
*	Methods: 
*		int GetNumEmpty();
*			gets the total number of empty cells
*		void Clear();
*			sets back to empty
*		void Draw();
*			Draws the cards in the free cells
*		bool AddCard(Card card, int pos);
*			adds a card to the free cell selected
*		bool CheckEmpty(int i);
*			checks if empty
*		Card GetCard(int pos);
*			returns a card in that position but doesn't empty it
*		void EmptyPosition(int pos);
*			empties that position
*
***************************************************************************************************/
#ifndef CELLS_H
#define CELLS_H
#include "Card.h"
#include "Array_1D.h"

class FreeCells
{
public:
			//Default Constructor
	FreeCells();
			//Copy Constructor
	FreeCells(const FreeCells & copy);
			//Destructor
	~FreeCells();
			//Assignment Operator
	FreeCells & operator = (const FreeCells & rhs);
			//gets the total number of empty cells
	int GetNumEmpty();
			//sets back to empty
	void Clear();
			//Draws the cards in the free cells
	void Draw();
			//adds a card to the free cell selected
	bool AddCard(Card card, int pos);
			//checks if empty
	bool CheckEmpty(int i);
			// returns a card in that position but doesn't empty it
	Card GetCard(int pos);
			//empties that position
	void EmptyPosition(int pos);
		
	static const int FREE_AMOUNT = 4;

private:
	Array_1D<Card> m_cell;
	Array_1D<bool> m_empty;
};
#endif