/***************************************************************************************************
* Author:						Tanna McClure
* File:							Deck.cpp
* Date Created:					1/29/2015
*
* Modification Date: 			1/29/2015
* Modification: 				Created
*		  
***************************************************************************************************/
#include "Deck.h"
#include "Exception.h"
#include <time.h>
#include <stdlib.h>

/***************************************************************************************************
*	Purpose: constructor
*
*	Entry: creates the deck and the shuffles it
*
*	Exit: deck is random
***************************************************************************************************/
Deck::Deck()
{
	int pos = 0;
	for (int i(Card::ACE); i <= Card::KING; i++)
	{
		for (int j(Card::HEART); j <= Card::SPADE; j++, pos++)
		{
			m_cards[pos].SetRank((Card::RANK)i);
			m_cards[pos].SetSuit((Card::SUIT)j);
		}
	}
	Shuffle();
}
/***************************************************************************************************
*	Purpose: copy ctor
*
*	Entry: deck to copy
*
*	Exit: the cards are in the same position as the deck passed in
***************************************************************************************************/
Deck::Deck(const Deck & copy)
{
	for (int i(0); i < NUM_CARDS; i++)
		m_cards[i] = copy.m_cards[i];
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the deck to copy
*
*	Exit: the cards are in the same position as the deck passed in
***************************************************************************************************/
Deck & Deck::operator=(const Deck & rhs)
{
	for (int i(0); i < NUM_CARDS; i++)
		m_cards[i] = rhs.m_cards[i];
	return *this;
}
/***************************************************************************************************
*	Purpose: [] operator
*
*	Entry: position
*
*	Exit: returns the card at the position passed in
***************************************************************************************************/
Card & Deck::operator[](int i)
{
	if (i < 0 || i >= NUM_CARDS)
		throw Exception("Exception:   Deck - []:   Invalid Position");
	return m_cards[i];
}
/***************************************************************************************************
*	Purpose: Shuffles the deck
*
*	Entry: none
*
*	Exit: deck is in a random order
***************************************************************************************************/
void Deck::Shuffle(unsigned int seed)
{
	srand(seed);

	for (int i(NUM_CARDS-1); i > 0; i--)
	{
		Card temp = m_cards[i];
		int pos = rand() % i;
		m_cards[i] = m_cards[pos];
		m_cards[pos] = temp;
	}
}