/***************************************************************************************************
* Author:						Tanna McClure
* File:							Cells.cpp
* Date Created:					2/2/2015
*
* Modification Date: 			2/4/2015
* Modification: 				updated draw function
*		  
***************************************************************************************************/
#include "FreeCells.h"

/***************************************************************************************************
*	Purpose: default ctor
*
*	Entry: none
*
*	Exit: everything set to empty
***************************************************************************************************/
FreeCells::FreeCells(): m_cell(FREE_AMOUNT), m_empty(FREE_AMOUNT)
{ 
	for (int i(0); i < FREE_AMOUNT; i++)
		m_empty[i] = true;
}

/***************************************************************************************************
*	Purpose: copy ctor
*
*	Entry: cells to copy
*
*	Exit: this = what was passed in
***************************************************************************************************/
FreeCells::FreeCells(const FreeCells & copy)
{ 
	*this = copy;
}

/***************************************************************************************************
*	Purpose: dtor
*
*	Entry: none
*
*	Exit: everything set to empty
***************************************************************************************************/
FreeCells::~FreeCells()
{
	Clear();
}

/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the rhs
*
*	Exit: this = rhs
***************************************************************************************************/
FreeCells & FreeCells::operator=(const FreeCells & rhs)
{
	if (this != &rhs)
	{
		m_cell = rhs.m_cell;
		m_empty = rhs.m_empty;
	}
	return *this;
}

/***************************************************************************************************
*	Purpose: gets the number of empty cells
*
*	Entry: none
*
*	Exit: returns number of cells that are empty
***************************************************************************************************/
int FreeCells::GetNumEmpty()
{
	int empty(0);

	for (int i(0); i < FREE_AMOUNT; i++)
		if (m_empty[i])
			empty++;

	return empty;
}

/***************************************************************************************************
*	Purpose: clears the cells
*
*	Entry: none
*
*	Exit: everything is set back to empty
***************************************************************************************************/
void FreeCells::Clear()
{
	for (int i(0); i < FREE_AMOUNT; i++)
		m_empty[i] = true;
}

/***************************************************************************************************
*	Purpose: Adds a card to a specific free cell
*
*	Entry: the card and the position
*
*	Exit: true if the move was successful
***************************************************************************************************/
bool FreeCells::AddCard(Card card, int pos)
{
	bool valid = m_empty[pos];
	if (valid)
	{
		m_cell[pos] = card;
		m_empty[pos] = false;
	}
	return valid;
}

/***************************************************************************************************
*	Purpose: checks whether a specific cell is empty or not
*
*	Entry: the position to check
*
*	Exit: true if the cell is empty
***************************************************************************************************/
bool FreeCells::CheckEmpty(int i)
{
	return m_empty[i];
}

/***************************************************************************************************
*	Purpose: returns a card in the specified position WITHOUT setting it to empty
*
*	Entry: the position
*
*	Exit: card in that position is returned
***************************************************************************************************/
Card FreeCells::GetCard(int pos)
{
	if (m_empty[pos])
		throw Exception("Exception:   FreeCells - GetCard:   Position is marked as empty");
	return m_cell[pos];
}

/***************************************************************************************************
*	Purpose: marks a cell as empty
*
*	Entry: the cell to mark
*
*	Exit: cell is now open to place other cards there
***************************************************************************************************/
void FreeCells::EmptyPosition(int pos)
{
	m_empty[pos] = true;
}

/***************************************************************************************************
*	Purpose: draws all the free cells to the board
*
*	Entry: none
*
*	Exit: free cell area is updated
***************************************************************************************************/
void FreeCells::Draw()
{
	COORD position = DISPLAY::FREE_UPPER_LEFT;
	for (int i(0); i < FREE_AMOUNT; i++)
	{
		if (m_empty[i])
			Card::DrawEmpty(position);
		else
			m_cell[i].DrawCard(position);
		position.X += DISPLAY::SINGLE_CARD_WIDTH + DISPLAY::SPACE_BTWN_CARDS;
	}
}