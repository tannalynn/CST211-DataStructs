/***************************************************************************************************
* Author:						Tanna McClure
* File:							FreeCell.h
* Date Created:					1/29/2015
*
* Modification Date: 			2/6/2015
* Modification: 				finalized commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: FreeCell
*
*	Purpose: 
*		Manages the cascades in the play area for the game
*
*	Manager Functions: 
*		FreeCell();
*			Default Constructor
*		FreeCell(const FreeCell & copy);
*			Copy Constructor
*		~FreeCell();
*			Destructor
*		FreeCell & operator = (const FreeCell & rhs);
*			Assignment operator
*
*	Methods: 
*		char InitialMenu();
*			displays menu and returns menu choice
*		void DrawInitialMenu();
*			draws the initial menu
*		void DrawMenuChoice(string text, COORD pos, int width);
*			draws a menu choice
*		void PlayGame();
*			starts the game
*		void CheatyGame();
*			sets the deck to a be cheaty
*		void DealGame();
*			deals the cards from the deck to the cascades
*		Selection MakeSelection();
*			Selects move choice
*		bool DoMove(Selection from, Selection to);
*			does the move selected by the user if valid
*		bool GameWon();
*			checks to see if the game is won
*		bool MoveFromFree(Selection from, Selection to);
*			move is from a free cell
*		bool MoveFromCascade(Selection from, Selection to);
*			move is from a cascade
*		void StartOver();
*			starts a blank game
*		void DrawInitial();
*			draws empty game
*		void DrawInitialHF(COORD pos, int num);
*			Draws empty home or free cells
*		void DrawInvalidMove(bool message = true);
*			draws invalid
*		COORD GetMouseClick();
*			gets a mouse click from the screen
*		char GetClickArea(COORD click);
*			gets the area for the click during gameplay
*		int ClickHF(COORD click, COORD up_left);
*			gets the position of the card clicked in home or free cell area
*		Selection ClickC(COORD click);
*			gets the position of the card clicked in the play area
*		char GetMenuArea(COORD click);
*			gets the menu choice clicked
*		void DrawWon();
*			draws a screen that's like YOU WON
*
***************************************************************************************************/
#ifndef FREECELL_H
#define FREECELL_H
#include "Deck.h"
#include "FreeCells.h"
#include "HomeCells.h"
#include "Cascades.h"
using std::string;

class FreeCellGame
{
public:
			//Default Constructor
	FreeCellGame();
			//Destructor
	~FreeCellGame();
			//StartGame
	void StartGame();
	
private:
	FreeCells m_free;
	HomeCells m_home;
	Cascades m_cascades;
	Deck m_deck;

			// Selection of card for each move
	struct Selection { string type;  int pos; }; 

			//displays menu and returns menu choice
	char InitialMenu();
			//draws the initial menu
	void DrawInitialMenu();
			//draws a menu choice
	void DrawMenuChoice(string text, COORD pos, int width);
			//starts the game
	void PlayGame();
			//sets the deck to a be cheaty
	void CheatyGame();
			//deals the cards from the deck to the cascades
	void DealGame();
			//Selects move choice
	Selection MakeSelection();
			//does the move selected by the user if valid
	bool DoMove(Selection from, Selection to);
			//checks to see if the game is won
	bool GameWon();
			//move is from a free cell
	bool MoveFromFree(Selection from, Selection to);
			//move is from a cascade
	bool MoveFromCascade(Selection from, Selection to);
			//starts a blank game
	void StartOver();
			//draws empty game
	void DrawInitial();
			//Draws empty home or free cells
	void DrawInitialHF(COORD pos, int num);
			//draws invalid
	void DrawInvalidMove(bool message = true);
			//gets a mouse click from the screen
	COORD GetMouseClick();
			//gets the area for the click during gameplay
	char GetClickArea(COORD click);
			//gets the position of the card clicked in home or free cell area
	int ClickHF(COORD click, COORD up_left);
			//gets the position of the card clicked in the play area
	Selection ClickC(COORD click);
			//gets the menu choice clicked
	char GetMenuArea(COORD click);
			//Draw game won screen
	void DrawWon();

			//Copy Constructor
	FreeCellGame(const FreeCellGame & copy);
			//Assignment Operator
	FreeCellGame & operator = (const FreeCellGame & rhs);
};
#endif