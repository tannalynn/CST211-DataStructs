/***************************************************************************************************
* Author:						Tanna McClure
* File:							Board.h
* Date Created:					1/11/2015
*
* Modification Date: 			
* Modification: 				
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Board
*
*	Purpose: 
*		Keeps the board for minesweeper.
*
*	Manager Functions: 
*
*		Board();
*			Default ctor
*		Board(const Board & copy);
*			Copy ctor
*		~Board();
*			dtor
*		Board & operator = (const Board & rhs);
*			assignment operator
*
*	Methods: 
*		void SetSize(int row, int col);
*			Sets the size of the board and resets everything to a new round
*		void SetBombs(int bomb);
*			Sets the number of bombs on the board
*		int GetBombs() const;
*		int GetHidden() const;
*		const Array_2D<Cell> & GetBoard() const;
*		int GetFlagged() const;
*			Getters
*		void InitialDraw() const;
*			Draws the board initially
*		void DrawBombs() const;
*			Updates the screen with the bombs places
*		bool Uncover(int row, int col);
*			uncovers a cell
*		void FlagCell(int row, int col);
*			flags a cell
*		void UnflagCell(int row, int col);
*			unflags a cell
*		void Cheat();
*			Makes you win!
*		void Flood(int row, int col);
*			Flood uncovers cells
*		void PopBoard(int x, int y);
*			populates board with bombs
*		void DrawCell(int row, int col) const;
*			Draws a cell
*
***************************************************************************************************/
#ifndef BOARD_H
#define BOARD_H
#include "Cell.h"
#include "Array_2D.h"
#include <time.h>

class Board
{
public:
			//Default Constructor
	Board();
			//Copy Constructor
	Board(const Board & copy);
			//Destructor
	~Board();
			//Assignment Operator
	Board & operator = (const Board & rhs);

			//setters
	void SetSize(int row, int col);
	void SetBombs(int bomb);
			//getters
	int GetBombs() const;
	int GetHidden() const;
	const Array_2D<Cell> & GetBoard() const;
	int GetFlagged() const;
			//Draws the board initially
	void InitialDraw() const;
			//Updates the screen with the bombs places
	void DrawBombs() const;
			//uncovers a cell
	bool Uncover(int row, int col);
			//flags a cell
	void FlagCell(int row, int col);
			//unflags a cell
	void UnflagCell(int row, int col);
			//Clears the board
	void Cheat();
private:
	Array_2D<Cell> m_board;
	int m_bombs;
	int m_flagged;
	int m_hidden;
	bool m_pop;

			//Flood uncovers cells 
	void Flood(int row, int col);
			//populates board
	void PopBoard(int x, int y);
			//Draws a cell
	void DrawCell(int row, int col) const;
};
#endif