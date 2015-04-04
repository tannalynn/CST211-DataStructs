/***************************************************************************************************
* Author:						Tanna McClure
* File:							HomeCells.cpp
* Date Created:					2/3/2015
*
* Modification Date: 			2/4/2015
* Modification: 				added an add card function
*		  
***************************************************************************************************/
#include "HomeCells.h"


/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: memory created and stack size set to 13
***************************************************************************************************/
HomeCells::HomeCells(): m_cells(HOME_AMOUNT)
{
	for (int i(0); i < HOME_AMOUNT; i++)
		m_cells[i] = new StackLimit<Card>(13);
}

/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the object to copy
*
*	Exit: this = copy
***************************************************************************************************/
HomeCells::HomeCells(const HomeCells & copy)
{
	for (int i(0); i < HOME_AMOUNT; i++)
		m_cells[i] = new StackLimit<Card>(13);
	for (int i(0); i < HOME_AMOUNT; i++)
		*m_cells[i] = *copy.m_cells[i]; //copy contents
}

/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: deletes memory
***************************************************************************************************/
HomeCells::~HomeCells()
{
	for (int i(0); i < HOME_AMOUNT; i++)
		delete m_cells[i];
}

/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the thing to copy
*
*	Exit: this = what was passed in
***************************************************************************************************/
HomeCells & HomeCells::operator=(const HomeCells & rhs)
{
	if (this != &rhs)
		for (int i(0); i < HOME_AMOUNT; i++)
			*m_cells[i] = *rhs.m_cells[i]; //copy contents
	return *this;
}

/***************************************************************************************************
*	Purpose: checks if all home cells are full
*
*	Entry: none
*
*	Exit: returns true if all are full
***************************************************************************************************/
bool HomeCells::HomeFull()
{
	bool full = true;

	for (int i(0); i < HOME_AMOUNT && full; i++)
		if (!m_cells[i]->IsFull())
			full = false;

	return full;
}

/***************************************************************************************************
*	Purpose: clears the home cells
*
*	Entry: none
*
*	Exit: home cells are all empty
***************************************************************************************************/
void HomeCells::Clear()
{
	for (int i(0); i < HOME_AMOUNT; i++)
		while (!m_cells[i]->IsEmpty())
			m_cells[i]->Pop();
}

/***************************************************************************************************
*	Purpose: adds a card to the appropriate home cell
*
*	Entry: the card to add
*
*	Exit: true if the move was successful
***************************************************************************************************/
bool HomeCells::AddCard(Card card)
{
	bool valid = true;

	if (card.GetRank() == Card::ACE || //if ace or the next one
		(!m_cells[card.GetSuit() - Card::HEART]->IsEmpty() &&
		(card.GetRank() == (m_cells[card.GetSuit() - Card::HEART]->Peek().GetRank() + 1))))
		m_cells[card.GetSuit() - Card::HEART]->Push(card);
	else
		valid = false;

	return valid;
}

/***************************************************************************************************
*	Purpose: updates the display for the home cells
*
*	Entry: none 
*
*	Exit: screen updated
***************************************************************************************************/
void HomeCells::Draw()
{
	COORD position = DISPLAY::HOME_UPPER_LEFT;
	for (int i(0); i < HOME_AMOUNT; i++)
	{
		if (m_cells[i]->Size() == 0)
			Card::DrawEmpty(position);
		else
			m_cells[i]->Peek().DrawCard(position);
		position.X += DISPLAY::SINGLE_CARD_WIDTH + DISPLAY::SPACE_BTWN_CARDS;
	}
}
