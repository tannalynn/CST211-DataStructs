/***************************************************************************************************
* Author:						Tanna McClure
* File:							Cascades.cpp
* Date Created:					2/3/2015
*
* Modification Date: 			2/4/2015
* Modification: 				completed functions
*		  
***************************************************************************************************/
#include "Cascades.h"

/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: array size set to 8
***************************************************************************************************/
Cascades::Cascades(): m_cascades(CASCADE_AMOUNT)
{ }

/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the object to copy
*
*	Exit: created
***************************************************************************************************/
Cascades::Cascades(const Cascades & copy):m_cascades(copy.m_cascades)
{ }

/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: destroyed
***************************************************************************************************/
Cascades::~Cascades()
{
	Clear();
}

/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the object to copy
*
*	Exit: this now is the same as what was passed in
***************************************************************************************************/
Cascades & Cascades::operator=(const Cascades & rhs)
{
	if (this != &rhs)
		m_cascades = rhs.m_cascades;
	return *this;
}

/***************************************************************************************************
*	Purpose: deals the deck into the cascades
*
*	Entry: the deck to distributed
*
*	Exit: distributed and drawn to screen
***************************************************************************************************/
void Cascades::DealGame(Deck deck)
{
	COORD position = DISPLAY::CASC_UPPER_LEFT;

	for (int i(0); i < Deck::NUM_CARDS; i++) //deals one card to each column at a time
	{
		m_cascades[i % CASCADE_AMOUNT].Push(deck[i]);
		deck[i].DrawCard(position);
		Sleep(50);

		position.X=DISPLAY::CASC_UPPER_LEFT.X+((i+1) % CASCADE_AMOUNT) * DISPLAY::SINGLE_CARD_WIDTH
										     +((i+1) % CASCADE_AMOUNT) * DISPLAY::SPACE_BTWN_CARDS;
		if ((i % CASCADE_AMOUNT) == CASCADE_AMOUNT - 1)
			position.Y += 2;
	}
}

/***************************************************************************************************
*	Purpose: returns a certain number of cards
*
*	Entry: the column to get the cards from, and the position from the start of the first card
*
*	Exit: returns the stack, or throws exception if invalid
***************************************************************************************************/
Stack<Card> Cascades::GetCards(int column, int pos)
{
	Stack<Card> return_stack;

	if (m_cascades[column].Size() == 0) //column empty
		throw Exception("Exception:   Cascades - GetCards:   Column is empty");
	else if (pos == m_cascades[column].Size() - 1) //grabbing one card
		return_stack.Push(m_cascades[column].Peek());
	else if (m_cascades[column].Size() <= pos || pos < 0) //position is larger than max position
		throw Exception("Exception:   Cascades - GetCards:   Position Invalid");
	else
	{
		Stack<Card> copy = m_cascades[column];
		Card card;
		while (copy.Size() > pos) //every card till pos
		{
			if (return_stack.IsEmpty()) //first card
				return_stack.Push(copy.Pop());
			else
			{
				card = copy.Pop();		//if it is the next rank  AND the other color
				if (card.GetRank() == return_stack.Peek().GetRank() + 1 
					&& card.IsRed() != return_stack.Peek().IsRed())
					return_stack.Push(card);
				else
					throw Exception("Exception:   Cascades - GetCards:   Invalid Selection");
			}
		}
	}
	return return_stack; //returned in reverse order
}

/***************************************************************************************************
*	Purpose: removes cards from a stack
*
*	Entry: the column and position of the cards to remove to
*
*	Exit: cards removed
***************************************************************************************************/
void Cascades::RemoveCards(int column, int pos)
{
	if (pos >= 0 && !m_cascades[column].IsEmpty() )
		while (m_cascades[column].Size() > pos)
			m_cascades[column].Pop();
}

/***************************************************************************************************
*	Purpose: adds a stack of cards to a cascade in the play area
*
*	Entry: stack passed in in reverse order
*
*	Exit: true if move was successful
***************************************************************************************************/
bool Cascades::AddCards(Stack<Card> cards, int column, int freecells)
{
	bool valid = ValidCalc(column, cards.Size(), freecells);
	if (m_cascades[column].IsEmpty() && valid)
	{
		while (!cards.IsEmpty())
			m_cascades[column].Push(cards.Pop());
	}
	else if (valid)
	{
		Card base = m_cascades[column].Peek(), new_card = cards.Peek();
		if (base.GetRank() == new_card.GetRank() + 1 && base.IsRed() != new_card.IsRed())
		{		//already know that the cards we are moving are valid, so only check the first one
			while (!cards.IsEmpty())
				m_cascades[column].Push(cards.Pop());
		}
		else
			valid = false;
	}
	return valid;
}

/***************************************************************************************************
*	Purpose: draws all the stacks in the play area
*
*	Entry: none
*
*	Exit: redrawn on screen
***************************************************************************************************/
void Cascades::Draw()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = DISPLAY::CASC_UPPER_LEFT;

	//draws each column
	for (int i(0); i < CASCADE_AMOUNT; i++)
	{
 		COORD pos = position;
		for (int j(0); j < 55; j++, pos.Y++)
			if (SetConsoleCursorPosition(hStdout, pos))
				cout << "      ";

		if (m_cascades[i].Size() == 0) //if empty column
			Card::DrawEmpty(position);
		else
		{
			Stack<Card> temp = m_cascades[i];
			Stack<Card> to_draw;

			while (!temp.IsEmpty()) 
				to_draw.Push(temp.Pop());
			while (!to_draw.IsEmpty())//draw all the cards in the stack
			{
				to_draw.Pop().DrawCard(position);
				position.Y += 2;
			}
		}
		position = DISPLAY::CASC_UPPER_LEFT; //move cursor for new column
		position.X += ((i + 1) * DISPLAY::SINGLE_CARD_WIDTH) + ((i + 1) * DISPLAY::SPACE_BTWN_CARDS);
	}
}

/***************************************************************************************************
*	Purpose: checks the if the number of cards being moved is ok
*
*	Entry: the column being moved to, the number of cards being moved and the number of freecells
*
*	Exit: true if it's ok to move them
***************************************************************************************************/
bool Cascades::ValidCalc(int column, int num_cards, int free)
{
	int empty_c = 0;

	for (int i(0); i < CASCADE_AMOUNT; i++)
		if (m_cascades[i].IsEmpty() && column != i)
			empty_c++;
	
	double max = (free + 1) * (pow(2, empty_c));

	return max >= num_cards;
}

/***************************************************************************************************
*	Purpose: sets all the columns to empty
*
*	Entry: none
*
*	Exit: reset
***************************************************************************************************/
void Cascades::Clear()
{
	Stack<Card> empty;
	for (int i(0); i < CASCADE_AMOUNT; i++)
		m_cascades[i] = empty;
}

/***************************************************************************************************
*	Purpose: gets the size of the column
*
*	Entry: the column
*
*	Exit: size of stack
***************************************************************************************************/
int Cascades::GetSize(int col)
{
	if (col < 0 || col >= CASCADE_AMOUNT)
		throw Exception("Exception:   Cascades - GetSize:   Column given invalid");
	return m_cascades[col].Size();
}