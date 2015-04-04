/***************************************************************************************************
* Author:						Tanna McClure
* File:							Card.cpp
* Date Created:					1/29/2015
*
* Modification Date: 			1/30/2015
* Modification: 				Added DrawCard function
*		  
***************************************************************************************************/
#include "Card.h"
#include <iostream>
using std::cout;
#include <iomanip>
using std::setw;
using std::left;
using std::right;

/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: creates a card with no suit or rank
***************************************************************************************************/
Card::Card(): m_suit((SUIT)0), m_rank((RANK)0)
{ }
/***************************************************************************************************
*	Purpose: 2 arg constructor
*
*	Entry: a suit and a rank
*
*	Exit: the card has been created with the rank and suit that were passed in
***************************************************************************************************/
Card::Card(SUIT suit, RANK rank): m_rank(rank), m_suit(suit)
{ }
/***************************************************************************************************
*	Purpose: Copy constructor
*
*	Entry: the card to copy
*
*	Exit: a new card has been created that is the same as the card passed in
***************************************************************************************************/
Card::Card(const Card & copy): m_suit(copy.m_suit), m_rank(copy.m_rank)
{ }
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: resets the card to no rank and no suit
***************************************************************************************************/
Card::~Card()
{
	m_suit = (SUIT)0;
	m_rank = (RANK)0;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the card to copy
*
*	Exit: this is now the same as the card that was passed in
***************************************************************************************************/
Card & Card::operator=(const Card & rhs)
{
	m_rank = rhs.m_rank;
	m_suit = rhs.m_suit;
	return *this;
}
/***************************************************************************************************
*	Purpose: returns the suit of the card
*
*	Entry: none
*
*	Exit: the suit of the card is returned
***************************************************************************************************/
Card::SUIT Card::GetSuit() const
{
	return m_suit;
}
/***************************************************************************************************
*	Purpose: returns the rank of the card
*
*	Entry: none
*
*	Exit: the rank of the card is returned
***************************************************************************************************/
Card::RANK Card::GetRank() const
{
	return m_rank;
}
/***************************************************************************************************
*	Purpose: changes the suit of the card
*
*	Entry: new suit
*
*	Exit: m_suit is changed
***************************************************************************************************/
void Card::SetSuit(SUIT suit)
{
	m_suit = suit;
}
/***************************************************************************************************
*	Purpose: sets the rank
*
*	Entry: the new rank of the card
*
*	Exit: m_rank is set
***************************************************************************************************/
void Card::SetRank(RANK rank)
{
	m_rank = rank;
}
/***************************************************************************************************
*	Purpose: Draws the card to the screen
*
*	Entry: the position to start the card
*
*	Exit: card drawn to screen
***************************************************************************************************/
void Card::DrawCard(COORD position_upper_left)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//Draw top edge of card
	if (SetConsoleCursorPosition(hStdout, position_upper_left))
		cout << DISPLAY::CARD_UPPER_LEFT_CORNER << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_HORIZONTAL 
		   << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_UPPER_RIGHT_CORNER;
	
	//Draw top suit and rank
	position_upper_left.Y++;
	if (SetConsoleCursorPosition(hStdout, position_upper_left))
	{
		cout << DISPLAY::CARD_VERTICAL;

		if (m_suit == HEART || m_suit == DIAMOND)
			SetConsoleTextAttribute(hStdout, DISPLAY::RED_CARD_TEXT);
		else
			SetConsoleTextAttribute(hStdout, DISPLAY::BLACK_CARD_TEXT);

		if (m_rank == ACE)
			cout << "A ";
		else if ( m_rank == JACK)
			cout << "J ";
		else if (m_rank == QUEEN)
			cout << "Q ";
		else if (m_rank == KING)
			cout << "K ";
		else
			cout <<left << setw(2) << m_rank;

		cout << " " << (char)m_suit;
		SetConsoleTextAttribute(hStdout, DISPLAY::DEFAULT_GAME);
		cout << DISPLAY::CARD_VERTICAL;
	}

	//Draw empty middle
	position_upper_left.Y++;
	if (SetConsoleCursorPosition(hStdout, position_upper_left))
		cout << DISPLAY::CARD_VERTICAL << "    " << DISPLAY::CARD_VERTICAL;
	//Draw empty middle
	position_upper_left.Y++;
	if (SetConsoleCursorPosition(hStdout, position_upper_left))
		cout << DISPLAY::CARD_VERTICAL << "    " << DISPLAY::CARD_VERTICAL;

	//Draw lower rank and suit
	position_upper_left.Y++;
	if (SetConsoleCursorPosition(hStdout, position_upper_left))
	{
		cout << DISPLAY::CARD_VERTICAL;

		if (m_suit == HEART || m_suit == DIAMOND)
			SetConsoleTextAttribute(hStdout, DISPLAY::RED_CARD_TEXT);
		else
			SetConsoleTextAttribute(hStdout, DISPLAY::BLACK_CARD_TEXT);

		cout << (char)m_suit <<" ";

		if (m_rank == ACE)
			cout << " A";
		else if (m_rank == JACK)
			cout << " J";
		else if (m_rank == QUEEN)
			cout << " Q";
		else if (m_rank == KING)
			cout << " K";
		else
			cout << right << setw(2) << m_rank;

		SetConsoleTextAttribute(hStdout, DISPLAY::DEFAULT_GAME);
		cout << DISPLAY::CARD_VERTICAL;
	}

	//Draw lower edge
	position_upper_left.Y++;
	if (SetConsoleCursorPosition(hStdout, position_upper_left))
		cout << DISPLAY::CARD_LOWER_LEFT_CORNER << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_HORIZONTAL 
		   << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_LOWER_RIGHT_CORNER;
}

/***************************************************************************************************
*	Purpose: Draws a blank to the screen
*
*	Entry: the position to start the card
*
*	Exit: card drawn to screen
***************************************************************************************************/
void Card::DrawEmpty(COORD position_upper_left)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, DISPLAY::DEFAULT_GAME);

	//Draw top edge of card
	if (SetConsoleCursorPosition(hStdout, position_upper_left))
		cout << DISPLAY::CARD_UPPER_LEFT_CORNER << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_HORIZONTAL
		  << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_UPPER_RIGHT_CORNER;

	//Draw empty middle and sides
	for (int i(0); i < 4; i++)
	{
		position_upper_left.Y++;
		if (SetConsoleCursorPosition(hStdout, position_upper_left))
			cout << DISPLAY::CARD_VERTICAL << "    " << DISPLAY::CARD_VERTICAL;
	}

	//Draw lower edge
	position_upper_left.Y++;
	if (SetConsoleCursorPosition(hStdout, position_upper_left))
		cout << DISPLAY::CARD_LOWER_LEFT_CORNER << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_HORIZONTAL
		  << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_HORIZONTAL << DISPLAY::CARD_LOWER_RIGHT_CORNER;
}

/***************************************************************************************************
*	Purpose: checks the cards color
*
*	Entry: none
*
*	Exit: returns true if card is red
***************************************************************************************************/
bool Card::IsRed()
{
	return (m_suit == DIAMOND || m_suit == HEART);

}
