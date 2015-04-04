/***************************************************************************************************
* Author:						Tanna McClure
* File:							Card.h
* Date Created:					1/29/2015
*
* Modification Date: 			1/30/2015
* Modification: 				completed
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Card
*
*	Purpose: 
*		Manages data for a card object
*
*	Manager Functions: 
*		Card();
*			Default Constructor
*		Card(SUIT suit, RANK rank);
*			2 arg ctor
*		Card(const Card & copy);
*			Copy Constructor
*		~Card();
*			Destructor
*		Card & operator = (const Card & rhs);
*			Assignment operator
*
*	Methods: 
*		void DrawCard(COORD position_upper_left);
*			draws card to screen
*		static void DrawEmpty(COORD position_upper_left);
*			draws an empty card
*		SUIT GetSuit() const;
*			Returns the suit of the card
*		RANK GetRank() const;
*			Returns the rank of the card
*		void SetRank(RANK rank);
*			sets the rank
*		void SetSuit(SUIT suit);
*			sets the suit
*		bool IsRed();
*			checks if the card is red or black
*
***************************************************************************************************/
#ifndef CARD_H
#define CARD_H
#include "Display.h"
class Card
{
public:
	enum SUIT { HEART = 3, DIAMOND = 4, CLUBS = 5, SPADE = 6, NOSUIT = 0 };

	enum RANK { NORANK, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

			//Default Constructor
	Card();
			//2 arg constructor
	Card(SUIT suit, RANK rank);
			//Copy Constructor
	Card(const Card & copy);
			//Destructor
	~Card();
			//Assignment Operator
	Card & operator = (const Card & rhs);

			//draws card to screen
	void DrawCard(COORD position_upper_left);
			//draws an empty card 
	static void DrawEmpty(COORD position_upper_left);
			//Returns the suit of the card
	SUIT GetSuit() const;
			//Returns the rank of the card
	RANK GetRank() const;
			//sets the rank
	void SetRank(RANK rank);
			//sets the suit
	void SetSuit(SUIT suit);
			//checks if the card is red or black
	bool IsRed();

private:
	SUIT m_suit;
	RANK m_rank;
};
#endif