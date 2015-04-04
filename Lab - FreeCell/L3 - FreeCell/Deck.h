/***************************************************************************************************
* Author:						Tanna McClure
* File:							Deck.h
* Date Created:					1/29/2015
*
* Modification Date: 			1/29/2015	
* Modification: 				Created

***************************************************************************************************/
/***************************************************************************************************
*	Class: Deck
*
*	Purpose: 
*		Holds 52 cards - 1 of each type
*
*	Manager Functions: 
*		Deck();
*			Default Constructor
*		Deck(const Deck & copy);
*			Copy Constructor
*		~Deck();
*			Destructor
*		Deck & operator = (const Deck & rhs);
*			Assignment operator
*
*	Methods: 
*		Card & operator[] (int i);
*			[] operator
*		void Shuffle();
*			Shuffles deck
*
***************************************************************************************************/
#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <time.h>
class Deck
{
public:
			//Default Constructor
	Deck();
			//Copy Constructor
	Deck(const Deck & copy);
			//Destructor
	~Deck() { }
			//Assignment Operator
	Deck & operator= (const Deck & rhs);

			//[] operator
	Card & operator[] (int i);
			//shuffle deck
	void Shuffle(unsigned int seed = static_cast<unsigned int>(time(0)));
		
	static const int NUM_CARDS = 52;
private:
	Card m_cards[NUM_CARDS];
};
#endif