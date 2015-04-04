/***************************************************************************************************
* Author:						Tanna McClure
* File:							Minesweeper.cpp
* Date Created:					1/11/2015
*
* Modification Date: 			1/16/2015
* Modification: 				created main level menu and made the input safe for the cell
*		  
***************************************************************************************************/
#include "Minesweeper.h"
#include <iostream>
using std::cout;
using std::cin;
#include <Windows.h>
#include "global display.h"
#include <conio.h>

/***************************************************************************************************
*	Purpose: ctor
*
*	Entry: none
*
*	Exit: game set up
***************************************************************************************************/
Minesweeper::Minesweeper()
{
	m_flagged_value_position.X = 0;
	m_flagged_value_position.Y = 0;
	m_last_selected_position.X = 0;
	m_last_selected_position.Y = 0;
	m_input_position.X = 0;
	m_input_position.Y = 0;
}

/***************************************************************************************************
*	Purpose: destructor
* 
*	Entry:none
* 
*	Exit: farewell message to the user
***************************************************************************************************/
Minesweeper::~Minesweeper()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	system("cls");
	system("mode 40, 11");
	position.X = 12;
	position.Y = 5;
	SetConsoleCursorPosition(hStdout, position);
	cout << "Goodbye Forever";
	cin.get();
}

/***************************************************************************************************
*	Purpose: Plays minesweeper
*
*	Entry: none
*
*	Exit: plays the game
***************************************************************************************************/
void Minesweeper::Play()
{
	bool hit_bomb = false;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	do
	{
		m_flagged_value_position.X = 0;
		m_flagged_value_position.Y = 0;
		m_last_selected_position.X = 0;
		m_last_selected_position.Y = 0;
		m_input_position.X = 0;
		m_input_position.Y = 0;

		Start();
		InitialDraw();
		
		do
		{
			hit_bomb = SelectCell();
		} while (!GameOver(hit_bomb));
		m_board.DrawBombs();

		position.X = DISPLAY::board_cols_min;
		position.Y = m_input_position.Y;
		Sleep(500);

		for (int i(0); i < 4; i++)
		{
			if (SetConsoleCursorPosition(hStdout, position))
			{
				if (hit_bomb) //lost
				{
					SetConsoleTextAttribute(hStdout, DISPLAY::RED_DARK_TEXT);
					for (int i(DISPLAY::board_cols_min); (i + 8) <= DISPLAY::board_cols_max; i += 11)
						cout << "GAME OVER  ";

				}
				else //won
				{
					SetConsoleTextAttribute(hStdout, DISPLAY::TEAL_DARK_TEXT);
					for (int i(DISPLAY::board_cols_min); (i + 8) <= DISPLAY::board_cols_max; i += 10)
						cout << "You Won!  ";
				}
			}
			Sleep(500);
			if (SetConsoleCursorPosition(hStdout, position))
				for (int i(DISPLAY::board_cols_min); (i + 8) <= DISPLAY::board_cols_max; i += 10)
					cout << "          ";
			Sleep(500);
		}
	} while (Again());
}

/***************************************************************************************************
*	Purpose: checks to see if the game is over
*
*	Entry: true if a bomb was selected
*
*	Exit: true if game is over
***************************************************************************************************/
bool Minesweeper::GameOver(bool hit_bomb) const
{
	bool over = false;
	if (hit_bomb)
		over = true;
	else if (m_board.GetHidden() == 0 && m_board.GetFlagged() == m_board.GetBombs())
		over = true;

	return over;
}

/***************************************************************************************************
*	Purpose: draws the board with the size of the difficulty
*
*	Entry: none
*
*	Exit: board drawn to screen
***************************************************************************************************/
void Minesweeper::InitialDraw()
{
	system("cls");

	int rows = m_board.GetBoard().GetRow();
	int cols = m_board.GetBoard().GetColumn();

	DISPLAY::board_cols_min = 4; //setting board left boundary
	DISPLAY::board_rows_min = 4; //setting board upper boundary
		//setting lower boundary
	DISPLAY::board_rows_max = (rows - 1) * DISPLAY::CELL_HEIGHT + DISPLAY::board_rows_min + 2; 
		//setting right boundary
	DISPLAY::board_cols_max = (cols * DISPLAY::CELL_WIDTH) + DISPLAY::board_cols_min; 

	//set console window size
	switch (m_level) 
	{	     //width, height
	case Minesweeper::BEG:
		system("mode 49, 34"); 
		break;
	case Minesweeper::INT:
		system("mode 73, 45");  
		break;
	case Minesweeper::EXP:
		system("mode 129, 45");  
		break;
	}

	//draws the board
	m_board.InitialDraw();

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	//draws number of cells flagged
	SetConsoleTextAttribute(hStdout, DISPLAY::GREY_DARK_TEXT);
	position.Y = DISPLAY::board_rows_min - 3; //-3 to put above board
	position.X = DISPLAY::board_cols_max - 15; //-15 for offset
	if (SetConsoleCursorPosition(hStdout, position))
		cout << "Flagged: 0" ; 
	m_flagged_value_position.X = DISPLAY::board_cols_max - 6; //-6 offset
	m_flagged_value_position.Y = position.Y;

	//draws number of bombs
	position.X = DISPLAY::board_cols_min + 3; //+3 to offset4
	if (SetConsoleCursorPosition(hStdout, position))
		cout << "Total Bombs: " << m_board.GetBombs();
	
	//displays input instructions
	SetConsoleTextAttribute(hStdout, DISPLAY::GREY_LIGHT_TEXT);
	position.X = DISPLAY::board_cols_max - 32; //20 = length of string
	position.Y = DISPLAY::board_rows_max + 2;  //below board
	if (SetConsoleCursorPosition(hStdout, position))
		cout << "F - Flag   U - Unflag   S - Show";
	position.X = DISPLAY::board_cols_max - 34; //34 = length of string
	position.Y++;  //increment line
	if (SetConsoleCursorPosition(hStdout, position))
		cout << "Input format: (F/U/S) row# column#";

	SetConsoleTextAttribute(hStdout, DISPLAY::BLACK_TEXT);
	position.X = DISPLAY::board_cols_min;
	position.Y +=2;
	if (SetConsoleCursorPosition(hStdout, position))
		cout << "Enter cell: ";
	m_input_position.Y = position.Y;
	m_input_position.X = position.X + 12;

	m_last_selected_position.Y = m_input_position.Y;// +1;
	m_last_selected_position.X = DISPLAY::board_cols_max - 7; //7 enough space to display entry

}

/***************************************************************************************************
*	Purpose: Updates the screen after every cell selection
*
*	Entry: the row and column and type of last selection
*
*	Exit: screen data is updates
***************************************************************************************************/
void Minesweeper::UpdateScreen(int last_row, int last_col, char flagged) const

{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;

	if (SetConsoleCursorPosition(hStdout, m_input_position))//clear input position
		cout << "                                                                                 ";

	//display last input 
	SetConsoleTextAttribute(hStdout, DISPLAY::GREY_DARK_TEXT);
	position.Y = m_last_selected_position.Y;
	position.X = m_last_selected_position.X - 10;
	if (SetConsoleCursorPosition(hStdout, position))
		cout << "Previous: ";
	if (SetConsoleCursorPosition(hStdout, m_last_selected_position))
		cout << flagged << " " << last_row << " " << last_col << "       ";

	//resets the number of flagged cells
	if (SetConsoleCursorPosition(hStdout, m_flagged_value_position))//clears area
		cout << "         ";
	if (SetConsoleCursorPosition(hStdout, m_flagged_value_position))
		cout << m_board.GetFlagged();

}

/***************************************************************************************************
*	Purpose: Sets the level and board size
*
*	Entry: none
*
*	Exit: level stored and board sized
***************************************************************************************************/
void Minesweeper::Start()
{
	system("cls");
	system("color F0"); //white bg black text
	system("mode 45, 13");

	char in = '\0';
	bool error = true;
	cout << "\n\n\t\tMinesweeper\n";
	cout << "\n\n\n\t\tBeginner\n\t\tIntermediate\n\t\tExpert\n\n\tEnter Level choice: ";
	do{
		cin >> in;
		cin.sync();
		in = toupper(in);
		switch (in)
		{
		case 'B':
			m_board.SetSize(10, 10);
			m_board.SetBombs(10);
			m_level = BEG;
			error = false;
			break;
		case 'I':
			m_board.SetSize(16, 16);
			m_board.SetBombs(40);
			m_level = INT;
			error = false;
			break;
		case 'E':
			m_board.SetSize(16, 30);
			m_board.SetBombs(100);
			m_level = EXP;
			error = false;
			break;
		default:
			system("cls");
			cout << "\n\n\t\tMinesweeper\n";
			cout << "\n\n\n\t\tBeginner <B>\n\t\tIntermediate <I>\n\t\tExpert <E>\n\n\tEnter Level choice: ";
		}
	} while (error);
}

/***************************************************************************************************
*	Purpose: Asks the player if they want to play the game again
* 
*	Entry: none
* 
*	Exit: returns true to play again
***************************************************************************************************/
bool Minesweeper::Again() const
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	char answer = 0;
	bool again = false;

	position.X = DISPLAY::board_cols_min;
	position.Y = m_input_position.Y;

	if (SetConsoleCursorPosition(hStdout, position))
		for (int i(DISPLAY::board_cols_min); (i + 8) <= DISPLAY::board_cols_max; i += 10)
			cout << "          ";
	position.X += 5;
	if (SetConsoleCursorPosition(hStdout, position))
		cout << "Play Again?: ";
	do
	{
		cin >> answer;
		cin.sync();
		answer = toupper(answer);
		Sleep(500);
		if (answer != 'Y' && answer != 'N')
		{
			again = true;
			if (SetConsoleCursorPosition(hStdout, position))
				cout << "That's rude. Enter something valid: ";
		}
		else
			again = false;
	} while (again);

	if (answer == 'Y')
		again = true;
	
	return again;
}

/***************************************************************************************************
*	Purpose: selects and uncovers a cell
*
*	Entry: none
*
*	Exit: returns true if a bomb is selected
***************************************************************************************************/
bool Minesweeper::SelectCell()
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	bool bomb = false, error = false;
	int row = 0;
	int col = 0;
	char selection = 's', sp = 0;

	if (SetConsoleCursorPosition(hStdout, m_input_position))
	{
		selection = _getch();
		SetConsoleCursorPosition(hStdout, m_input_position);
		cout << selection <<" ";
		selection = toupper(selection);

		if (selection != '@')
		{
			while (selection != 'S' && selection != 'F' && selection != 'U' && selection != '@')
			{
				for (int i(0); i < 2; i++)
				{
					SetConsoleCursorPosition(hStdout, m_input_position);
					cout << "Invalid. F/S/U";
					Sleep(400);
					SetConsoleCursorPosition(hStdout, m_input_position);
					cout << "                    ";
					Sleep(400);
				}

				if (m_level == BEG) //redisplay part of screen overwritten by error message
				{
					SetConsoleTextAttribute(hStdout, DISPLAY::GREY_DARK_TEXT);
					position.Y = m_last_selected_position.Y;
					position.X = m_last_selected_position.X - 10;
					if (SetConsoleCursorPosition(hStdout, position))
						cout << "Previous: ";
					SetConsoleTextAttribute(hStdout, DISPLAY::BLACK_TEXT);
				}
				SetConsoleCursorPosition(hStdout, m_input_position); 
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));//clears the input
				selection = _getch();
				SetConsoleCursorPosition(hStdout, m_input_position);
				cout << selection << " ";
				selection = toupper(selection);
				
			}
			if (selection != '@')
			{
				error = GetCellSelection(row);
					while (row >= m_board.GetBoard().GetRow() || row < 0 || error)
					{
						error = false;
						for (int i(0); i < 2; i++)
						{
							SetConsoleCursorPosition(hStdout, m_input_position);
							cout << "Invalid Row";
							Sleep(400);
							SetConsoleCursorPosition(hStdout, m_input_position);
							cout << "           ";
							Sleep(400);
						}
						SetConsoleCursorPosition(hStdout, m_input_position);
						cout << selection << " ";
						cin.clear();
						cin.ignore(cin.rdbuf()->in_avail());
						FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
						error = GetCellSelection(row);
					}

				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				SetConsoleCursorPosition(hStdout, m_input_position);
				cout << selection << " " <<row <<" ";

				error = GetCellSelection(col);
				while (col >= m_board.GetBoard().GetColumn() || col < 0 || error)
				{
					error = false;
					for (int i(0); i < 2; i++)
					{
						SetConsoleCursorPosition(hStdout, m_input_position);
						cout << "Invalid Column";
						Sleep(400);
						SetConsoleCursorPosition(hStdout, m_input_position);
						cout << "              ";
						Sleep(400);
					}
					SetConsoleCursorPosition(hStdout, m_input_position);
					cout << selection << " " << row << " ";
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					error = GetCellSelection(col);
				}
			}
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cin.sync();

			if (selection == 'S')
				bomb = m_board.Uncover(row, col);
			else if (selection == 'U')
				m_board.UnflagCell(row, col);
			else if (selection == 'F')
				m_board.FlagCell(row, col);

			UpdateScreen(row, col, selection);
		}
		if (selection == '@')
			m_board.Cheat();
	}
	return bomb;
}

/***************************************************************************************************
*	Purpose: grabs the input from the screen
*
*	Entry: the value to put the value in
*
*	Exit: returns true if the input was bad
***************************************************************************************************/
bool Minesweeper::GetCellSelection(int & val) const
{
	char sp = 0;
	bool error = false;

	sp = _getch(); //this section of code protects against rude input
	if (!isdigit(sp))
		sp = _getch();  // so it doesn't get mad if you put a space before the number
	if (isdigit(sp))
	{
		cout << sp; //displays the char back out the the screen
		val = sp - '0'; //converts character into decimal value
		sp = _getch();
		if (isdigit(sp))
		{
			cout << sp; //displays the char back out the the screen
			val *= 10;  //second number was digit, so this number is a 2 digit number
			val += sp - '0'; //converts character into decimal value
		}
	}
	else
		error = true;  //they put in something rude

	return error;
}