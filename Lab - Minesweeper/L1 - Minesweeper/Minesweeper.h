/***************************************************************************************************
* Author:						Tanna McClure
* File:							Minesweeper.h
* Date Created:					1/11/2015
*
* Modification Date: 			1/16/2015
* Modification: 				finished
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Minesweeper
*
*	Purpose: 
*		Controls the minesweeper game. Once Play is called, the game plays until the user decides 
*			quit
*
*	Manager Functions: 
*		Minesweeper();
*			Default Constructor
*
*		Minesweeper(const Minesweeper & copy);
*			Copy Constructor
*		~Minesweeper();
*			Destructor
*		Minesweeper & operator = (const Minesweeper & rhs);
*			Assignment operator
*
*	Methods: 
*
*		void Start();
*			Begins a game
*		bool SelectCell();
*			selects a cell from the user
*		void InitialDraw();
*			Draws the game
*		void UpdateScreen(int last_row, int last_col, char flagged) const;
*			Updates screen
*		bool GameOver(bool hit_bomb) const;
*			Checks to see if the a bomb has been hit, or the player won.
*		bool Again() const;
*			Asks is player wants to play again
*		bool GetCellSelection(int & val) const;
*			gets input
*
***************************************************************************************************/
#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include "Board.h"
#include "String.h"
#include <Windows.h>
class Minesweeper
{
public:
	enum LEVEL { BEG, INT, EXP };

			//Default Constructor
	Minesweeper();
			//Destructor
	~Minesweeper();
			//Starts the game
	void Play();

private:
	Board m_board;
	LEVEL m_level;

	COORD m_flagged_value_position;
	COORD m_last_selected_position;
	COORD m_input_position;

			//Begins a game
	void Start();
			//selects a cell from the user
	bool SelectCell();
			//Draws the game
	void InitialDraw();
			//Updates screen
	void UpdateScreen(int last_row, int last_col, char flagged) const;
			//Checks to see if the a bomb has been hit, or the player won.
	bool GameOver(bool hit_bomb) const;
			//Asks is player wants to play again
	bool Again() const;
			//gets input
	bool GetCellSelection(int & val) const;

			//Copy Constructor
	Minesweeper(const Minesweeper & copy) { } //don't want this to be used
			//Assignment Operator
	Minesweeper & operator = (const Minesweeper & rhs) { return *this; } //don't want this to be used

};
#endif