/***************************************************************************************************
* Author:						Tanna McClure
* File:							Board.cpp
* Date Created:					1/11/2015
*
* Modification Date: 			1/15/15
* Modification: 				added functions
*		  
***************************************************************************************************/
#include "Board.h"
#include "global display.h"
#include <iostream>
#include <Windows.h>
using std::cout;

/***************************************************************************************************
*	Purpose: default ctor
*
*	Entry: none
*
*	Exit: sets variables to 0
***************************************************************************************************/
Board::Board() :m_bombs(0), m_hidden(0), m_pop(false), m_flagged(0)
{ }
/***************************************************************************************************
*	Purpose: copy ctor
*
*	Entry: board to copy
*
*	Exit: this = copy
***************************************************************************************************/
Board::Board(const Board & copy) : m_hidden(copy.m_hidden), m_bombs(copy.m_bombs), 
								   m_board(copy.m_board), m_pop(copy.m_pop), m_flagged(copy.m_flagged)
{ }
/***************************************************************************************************
*	Purpose: dtor
*
*	Entry: none
*
*	Exit: sets to zero
***************************************************************************************************/
Board::~Board()
{
	m_bombs = 0;
	m_hidden = 0;
	m_flagged = 0;
	m_pop = false;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the board to copy
*
*	Exit: data members equal the rhs
***************************************************************************************************/
Board & Board::operator=(const Board & rhs)
{
	m_hidden = rhs.m_hidden;
	m_bombs = rhs.m_bombs;
	m_board = rhs.m_board;
	m_pop = rhs.m_pop;
	m_flagged = rhs.m_flagged;
	return *this;
}
/***************************************************************************************************
*	Purpose: sets the size of the board
*
*	Entry: the number of rows and columns
*
*	Exit: board size is set
***************************************************************************************************/
void Board::SetSize(int row, int col)
{
	m_board.Purge();
	m_board.SetColumn(col);
	m_board.SetRow(row);
	m_hidden = col * row;
	m_pop = false;
	m_flagged = 0;
}
/***************************************************************************************************
*	Purpose: sets the number of bombs
*
*	Entry: the number of bombs
*
*	Exit:number of bombs is set
***************************************************************************************************/
void Board::SetBombs(int bomb)
{
	m_bombs = bomb;
	m_pop = false;
	if (m_bombs > m_board.GetColumn()* m_board.GetRow() - 9)
		m_bombs = m_board.GetColumn()* m_board.GetRow() - 9;
}
/***************************************************************************************************
*	Purpose: gets the number of bombs on the board
*
*	Entry: none
*
*	Exit: returns m_bombs
***************************************************************************************************/
int Board::GetBombs() const
{
	return m_bombs;
}
/***************************************************************************************************
*	Purpose: Gets the number of cells still hidden
*
*	Entry: none
*
*	Exit: returns m_hidden
***************************************************************************************************/
int Board::GetHidden() const
{
	return m_hidden;
}
/***************************************************************************************************
*	Purpose: gets a copy the board
*
*	Entry: none
*
*	Exit: returns m_board
***************************************************************************************************/
const Array_2D<Cell> & Board::GetBoard() const
{
	return m_board;
}
/***************************************************************************************************
*	Purpose: gets the number of flagged cells
*
*	Entry: none
*
*	Exit: returns m_flagged
***************************************************************************************************/
int Board::GetFlagged() const
{
	return m_flagged;
}
/***************************************************************************************************
*	Purpose: flags a cell in a specific spot
*
*	Entry: the row and column of the cell to flag
*
*	Exit: cell status is changed to flagged
***************************************************************************************************/
void Board::FlagCell(int row, int col)
{
	Cell & cell = m_board[row][col];

	if (!m_pop)
		PopBoard(0, 0);

	if (cell.m_status == Cell::HIDDEN) //if cell is already flagged or shown, do nothing
	{
		cell.m_status = Cell::FLAGGED;
		m_flagged++;
		DrawCell(row, col);
	}
}
/***************************************************************************************************
*	Purpose: Uncovers a cell
*
*	Entry:  the row and column
*
*	Exit: cell is uncovered
***************************************************************************************************/
bool Board::Uncover(int row, int col)
{
	bool bomb_found(false);

	if (!m_pop)
		PopBoard(row, col); //populate bombs if board is empty
	Cell & cell = m_board[row][col];
	if (cell.m_status == Cell::HIDDEN) //if already shown or flagged, do nothing
	{
		if (cell.m_type == Cell::EMPTY)
			Flood(row, col); //flood draws the cells it uncovers
		else if (cell.m_type == Cell::BOMB)
			bomb_found = true;
		else
		{
			m_hidden--;
			DrawCell(row, col); //draws the cell
		}
		cell.m_status = Cell::SHOWN;
	}

	return bomb_found;
}
/***************************************************************************************************
*	Purpose: uncovers cells
*
*	Entry: the cell to uncover
*
*	Exit: cells are uncovered
***************************************************************************************************/
void Board::Flood(int row, int col)
{
	if (m_board[row][col].m_status == Cell::HIDDEN)
	{
		int row_min = row-1 < 0 ? 0 : row-1;
		int col_min = col-1 < 0 ? 0 : col-1;
		int row_max = row+1 >= m_board.GetRow() ? m_board.GetRow()-1 : row+1;
		int col_max = col+1 >= m_board.GetColumn() ? m_board.GetColumn()-1 : col+1;
		Cell & g = m_board[row][col];

		DrawCell(row, col); //displays cell that was just uncovered
		m_board[row][col].m_status = Cell::SHOWN;
		m_hidden--;

		for (int i(row_min); i <= row_max; i++) //check all rows adjacent
			for (int j(col_min); j <= col_max; j++) //check all columns adjacent
				if (m_board[i][j].m_type == Cell::EMPTY && m_board[i][j].m_status == Cell::HIDDEN)
					Flood(i, j); // if empty show all adjacent cells
				else if (m_board[i][j].m_status == Cell::HIDDEN)
				{
					m_board[i][j].m_status = Cell::SHOWN;
					DrawCell(i, j);
					m_hidden--;
				}
	}
}
/***************************************************************************************************
*	Purpose:  places the number of bombs required onto the board
*
*	Entry: the row and column the user selected (so no bomb is placed there)
*
*	Exit: board is populated
***************************************************************************************************/
void Board::PopBoard(int x, int y)
{
	m_pop = true;
	srand(static_cast<unsigned int>(time(0)));

	int row = m_board.GetRow();
	int col = m_board.GetColumn();
	int rand_x = 0;
	int	rand_y = 0;

	for (int k(0); k < m_bombs;)
	{
		rand_x = rand() % row;
		rand_y = rand() % col;

		if ((rand_x < x - 1 || rand_x > x + 1 || 
			 rand_y < y - 1 || rand_y > y + 1) && 
			 m_board[rand_x][rand_y].m_type != Cell::BOMB)
		{
			k++;
			m_board[rand_x][rand_y].m_type = Cell::BOMB;
			m_hidden--;
			int x_min = rand_x - 1 < 0 ? 0 : rand_x - 1;
			int y_min = rand_y - 1 < 0 ? 0 : rand_y - 1;
			int x_max = rand_x + 1 >= row ? row - 1 : rand_x + 1;
			int y_max = rand_y + 1 >= col ? col - 1 : rand_y + 1;

			for (int i(x_min); i <= x_max; i++)
				for (int j(y_min); j <= y_max; j++)
					if (m_board[i][j].m_type != Cell::BOMB)
						m_board[i][j].m_type = static_cast<Cell::TYPE>(1 + (m_board[i][j].m_type));
		}
	}
}
/***************************************************************************************************
*	Purpose: draws the entire board with all cells hidden
*
*	Entry: none
*
*	Exit: board drawn to the screen
***************************************************************************************************/
void Board::InitialDraw() const
{
	int num_rows = m_board.GetRow();
	int	num_cols = m_board.GetColumn();
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;


	//Displaying row numbers on sides
	position.Y = DISPLAY::board_rows_min + 1; //setting starting y position  +1 to center on each row
	for (int row_count(0); row_count < num_rows; row_count++)
	{
		position.X = DISPLAY::board_cols_min - 2; //left -2 to put before the border
		if (SetConsoleCursorPosition(hStdout, position))
			cout << (row_count < 10 ? " " : "") << row_count;

		position.X = DISPLAY::board_cols_max + 1; //right
		if (SetConsoleCursorPosition(hStdout, position))
			cout << row_count;
		position.Y += 2;
	}


	//Display column numbers above and below
	for (int x_pos(DISPLAY::board_cols_min + 2), col_count(0); col_count < num_cols;x_pos += 4, col_count++) 
	{									 //+ 2 to offset number to middle
		position.X = x_pos;
		position.Y = DISPLAY::board_rows_min - 1; //-1 to put it before the board
		if (SetConsoleCursorPosition(hStdout, position))
			cout << col_count;

		position.Y = DISPLAY::board_rows_max + 1; //+1 to put it after the board
		if (SetConsoleCursorPosition(hStdout, position))
			cout << col_count;
	}


	//Displaying corners
	position.Y = DISPLAY::board_rows_min;
	position.X = DISPLAY::board_cols_min;
	if (SetConsoleCursorPosition(hStdout, position))
		cout << DISPLAY::UPPER_LEFT_CORNER; //upper left corner
	position.X = DISPLAY::board_cols_max; 
	if (SetConsoleCursorPosition(hStdout, position))
		cout << DISPLAY::UPPER_RIGHT_CORNER; //upper right corner
	position.Y = DISPLAY::board_rows_max;
	if (SetConsoleCursorPosition(hStdout, position))
		cout << DISPLAY::LOWER_RIGHT_CORNER; //lower right corner
	position.X = DISPLAY::board_cols_min;
	if (SetConsoleCursorPosition(hStdout, position))
		cout << DISPLAY::LOWER_LEFT_CORNER; //lower left corner


	//Displaying top and bottom borders
	for (int x_pos(DISPLAY::board_cols_min + 1); x_pos < DISPLAY::board_cols_max; x_pos++) 
	{									//+1 to account for corner
		position.X = x_pos;
		position.Y = DISPLAY::board_rows_min;
		if (SetConsoleCursorPosition(hStdout, position))				//every 4 times
			cout << ((x_pos %  DISPLAY::CELL_WIDTH) != 0 ? DISPLAY::HORIZONTAL : DISPLAY::TOP_CROSS); 

		if (x_pos % DISPLAY::CELL_WIDTH == 0)
		{
			position.Y++;
			for (; position.Y < DISPLAY::board_rows_max; position.Y++)
				if (SetConsoleCursorPosition(hStdout, position))			//every other
					cout << ((position.Y % DISPLAY::CELL_HEIGHT) != 0 ? DISPLAY::VERTICAL : DISPLAY::CROSS); 
		}
		else
			position.Y = DISPLAY::board_rows_max;
		if (SetConsoleCursorPosition(hStdout, position))
			cout << ((x_pos %  DISPLAY::CELL_WIDTH) != 0 ? DISPLAY::HORIZONTAL : DISPLAY::BOTTOM_CROSS);
	}


	//Displaying side borders
	for (int y_pos(DISPLAY::board_rows_min + 1); y_pos < DISPLAY::board_rows_max; y_pos++) 
	{										//+1 to account for corner
		position.Y = y_pos;
		position.X = DISPLAY::board_cols_min;
		if (SetConsoleCursorPosition(hStdout, position))
			cout << (y_pos % DISPLAY::CELL_HEIGHT == 0 ? DISPLAY::LEFT_CROSS : DISPLAY::VERTICAL);

		if (y_pos % DISPLAY::CELL_HEIGHT == 0) //every other
		{
			position.X++;
			for (; position.X < DISPLAY::board_cols_max; position.X++)
				if (SetConsoleCursorPosition(hStdout, position))
					if (position.X %  DISPLAY::CELL_WIDTH != 0)
						cout << DISPLAY::HORIZONTAL;
		}
		else
			position.X = DISPLAY::board_cols_max;

		if (SetConsoleCursorPosition(hStdout, position))
			cout << (y_pos % DISPLAY::CELL_HEIGHT == 0 ? DISPLAY::RIGHT_CROSS : DISPLAY::VERTICAL);
	}


	//Display all cells as hidden
	SetConsoleTextAttribute(hStdout, DISPLAY::GREY_DARK_TEXT); //white bg gray text
	for (int y_pos(DISPLAY::board_rows_min + 1); y_pos < DISPLAY::board_rows_max; y_pos += DISPLAY::CELL_HEIGHT)
	{
		position.Y = y_pos;
		for (int j(DISPLAY::board_cols_min + 1); j < DISPLAY::board_cols_max; j += DISPLAY::CELL_WIDTH)
			for (unsigned int j_temp(j); j_temp < j + DISPLAY::CELL_WIDTH-1; j_temp++)
			{														 //-1 to not fill in any borders
				position.X = j_temp;
				if (SetConsoleCursorPosition(hStdout, position))
					cout << DISPLAY::HIDDENCELL;
			}
		
	}
}
/***************************************************************************************************
*	Purpose: display when bomb is found and game is over
*
*	Entry: none
*
*	Exit: screen is updated to show position of all bombs
***************************************************************************************************/
void Board::DrawBombs() const
{
	int num_rows = m_board.GetRow();
	int num_cols = m_board.GetColumn();
	int bombs = m_bombs;

	for (int row(0); row < num_rows && bombs; row++)
		for (int col(0); col < num_cols && bombs; col++)
			if (m_board[row][col].m_type == Cell::BOMB)
			{
				bombs--;
				DrawCell(row, col);
			}
}
/***************************************************************************************************
*	Purpose: draws one cell
*
*	Entry: the row and column of the cell to show
*
*	Exit: screen is updated to show that cell
***************************************************************************************************/
void Board::DrawCell(int row, int col) const
{
	//position of the first cell   - each cell is 3 wide and 1 high
	int row_start = DISPLAY::board_rows_min + 1; //+1 on each puts it in the cell, not on the border
	int col_start = DISPLAY::board_cols_min + 1; 

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	position.Y = row_start + (row * DISPLAY::CELL_HEIGHT);//position of the cell to draw
	position.X = col_start + (col * DISPLAY::CELL_WIDTH); 

	Cell::TYPE type = m_board[row][col].m_type;
	Cell::STATUS status = m_board[row][col].m_status;
	unsigned char display_type = '\0';

	if (status != Cell::FLAGGED)
		switch (type)
		{
		case Cell::EMPTY:
			display_type = ' ';
			break;
		case Cell::BOMB:
			display_type = 235;
			SetConsoleTextAttribute(hStdout, DISPLAY::BOMB_TEXT);
			break;
		case Cell::ONE:
			SetConsoleTextAttribute(hStdout, DISPLAY::TEAL_DARK_TEXT);
			break;
		case Cell::TWO:
			SetConsoleTextAttribute(hStdout, DISPLAY::PURPLE_TEXT);
			break;
		case Cell::THREE:
			SetConsoleTextAttribute(hStdout, DISPLAY::GREEN_DARK_TEXT);
			break;
		case Cell::FOUR:
			SetConsoleTextAttribute(hStdout, DISPLAY::BLUE_DARK_TEXT);
			break;
		case Cell::FIVE:
			SetConsoleTextAttribute(hStdout, DISPLAY::RED_DARK_TEXT);
			break;
		case Cell::SIX:
			SetConsoleTextAttribute(hStdout, DISPLAY::BLUE_BRIGHT_TEXT);
			break;
		case Cell::SEVEN:
			SetConsoleTextAttribute(hStdout, DISPLAY::MAGENTA_TEXT);
			break;
		case Cell::EIGHT:
			SetConsoleTextAttribute(hStdout, DISPLAY::RED_BRIGHT_TEXT);
			break;
		}
	
	else if (status == Cell::FLAGGED)
	{
		display_type = 0xFB; //  184;//
		SetConsoleTextAttribute(hStdout, DISPLAY::FLAGGED_TEXT);
	}

	if (SetConsoleCursorPosition(hStdout, position))
	{
		cout << " ";
		if (type == Cell::EMPTY || type == Cell::BOMB || status == Cell::FLAGGED)
			cout << display_type;
		else
			cout << type;
		cout << " ";
	}

	SetConsoleTextAttribute(hStdout, DISPLAY::BLACK_TEXT);
}
/***************************************************************************************************
*	Purpose: Cheats the game
*
*	Entry: none
*
*	Exit: makes you win
***************************************************************************************************/
void Board::Cheat()
{
	if (!m_pop)
		PopBoard(0, 0);
	for (int row(0); row < m_board.GetRow(); row++)
		for (int col(0); col < m_board.GetColumn(); col++)
			if (m_board[row][col].m_type != Cell::BOMB)
			{
				if (m_board[row][col].m_status == Cell::HIDDEN)
					m_hidden--;
				if (m_board[row][col].m_status == Cell::FLAGGED)
				{
					m_flagged--;
					m_hidden--;
				}
				m_board[row][col].m_status = Cell::SHOWN;
				DrawCell(row, col);
			}
			else
				FlagCell(row, col);

}
/***************************************************************************************************
*	Purpose: unflags a cell
*
*	Entry: row and col
*
*	Exit: unflags a cell and hides it again
***************************************************************************************************/
void Board::UnflagCell(int row, int col)
{	
	Cell & cell = m_board[row][col];

	int row_start = DISPLAY::board_rows_min + 1; //+1 on each puts it in the cell, not on the border
	int col_start = DISPLAY::board_cols_min + 1;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	position.Y = row_start + (row * DISPLAY::CELL_HEIGHT);//position of the cell to draw
	position.X = col_start + (col * DISPLAY::CELL_WIDTH);
	cell.m_status = Cell::HIDDEN;
	m_flagged--;

	if (SetConsoleCursorPosition(hStdout, position))
		cout << DISPLAY::HIDDENCELL << DISPLAY::HIDDENCELL << DISPLAY::HIDDENCELL;
}	