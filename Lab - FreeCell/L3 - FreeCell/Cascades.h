 /***************************************************************************************************
* Author:						Tanna McClure
* File:							Cascades.h
* Date Created:					2/3/2015
*
* Modification Date: 			2/8/2015
* Modification: 				finalized documentation
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Cascades
*
*	Purpose: 
*		manages the play areas cascades
*
*	Manager Functions: 
*		Cascades();
*			Default Constructor
*		Cascades(const Cascades & copy);
*			Copy Constructor
*		~Cascades();
*			Destructor
*		Cascades & operator = (const Cascades & rhs);
*			Assignment operator
*
*	Methods: 
*		void Draw();
*			Draws the cards in the free cells
*		void DealGame(Deck deck);
*			deals the game
*		Stack<Card> GetCards(int column, int pos);
*			gets cards but does not remove them
*		void RemoveCards(int column, int pos);
*			removes cards from the stack
*		bool AddCards(Stack<Card> cards, int column, int freecells);
*			adds cards to the stack if valid
*		bool ValidCalc(int column, int num_cards, int free);
*			checks if the number of cards trying to be moved is ok
*		void Clear();
*			clears everything for a new game
*		int GetSize(int col);
*			gets the size of the specified column
*
***************************************************************************************************/
#ifndef CASCADES_H
#define CASCADES_H
#include "Array_1D.h"
#include "Stack.h"
#include "Card.h"
#include "Deck.h"
class Cascades
{
public:
			//Default Constructor
	Cascades();
			//Copy Constructor
	Cascades(const Cascades & copy);
			//Destructor
	~Cascades();
			//Assignment Operator
	Cascades & operator = (const Cascades & rhs);

			//Draws the cards in the free cells
	void Draw();
			//deals the game
	void DealGame(Deck deck);
			//gets cards but does not remove them
	Stack<Card> GetCards(int column, int pos);
			//removes cards from the stack
	void RemoveCards(int column, int pos);
			//adds cards to the stack if valid
	bool AddCards(Stack<Card> cards, int column, int freecells);
			//checks if the number of cards trying to be moved is ok
	bool ValidCalc(int column, int num_cards, int free);
			//clears everything for a new game
	void Clear();
			//gets the size of the specified column
	int GetSize(int col);

	static const int CASCADE_AMOUNT = 8;

private:
	Array_1D<Stack<Card>> m_cascades;
};
#endif