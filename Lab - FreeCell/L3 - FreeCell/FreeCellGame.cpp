/***************************************************************************************************
* Author:						Tanna McClure
* File:							FreeCell.cpp
* Date Created:					1/29/2015
*
* Modification Date: 			2/8/2015
* Modification: 				completed 
*		  
***************************************************************************************************/
#include "FreeCellGame.h"
using std::cin;

/***************************************************************************************************
*	Purpose: default ctor
*
*	Entry: none
*
*	Exit: created and cursor no blinking
***************************************************************************************************/
FreeCellGame::FreeCellGame()
{ 
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;  //makes the cursor not do the blinky thing
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: a game to copy
*
*	Exit: this = what was passed in
***************************************************************************************************/
FreeCellGame::FreeCellGame(const FreeCellGame & copy)
{
	*this = copy;
}

/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the game to copy
*
*	Exit: this = rhs
***************************************************************************************************/
FreeCellGame & FreeCellGame::operator=(const FreeCellGame & rhs)
{
	if (this != &rhs)
	{
		m_home = rhs.m_home;
		m_cascades = rhs.m_cascades;
		m_free = rhs.m_free;
		m_deck = rhs.m_deck;
	}
	return *this;
}

/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: game wiped
***************************************************************************************************/
FreeCellGame::~FreeCellGame()
{
	StartOver();
}

/***************************************************************************************************
*	Purpose: begins the free cell game
*
*	Entry: none
*
*	Exit: game complete
***************************************************************************************************/
void FreeCellGame::StartGame()
{
	char menu(0);
	do
	{
		menu = InitialMenu();

		if (menu == 'P' || menu == 'S')
		{
			switch (menu)
			{
				case 'P':
					m_deck.Shuffle();
					break;
				case 'S':
					CheatyGame();
					break;
			}
			PlayGame();
			StartOver();
		}
	} while (menu != 'E');
}

/***************************************************************************************************
*	Purpose: displays the menu
*						
*	Entry: none	
*							
*	Exit: returns 
***************************************************************************************************/
char FreeCellGame::InitialMenu()
{
	char menu = 0;
	COORD click;
	DrawInitialMenu();
	do 
	{
		click = GetMouseClick();
		menu = GetMenuArea(click);

	} while (menu == 0);
	return menu;
}

/***************************************************************************************************
*	Purpose: gets the menu choice that was clicked
*
*	Entry: the coord of the moue click
*
*	Exit: the menu choice
***************************************************************************************************/
char FreeCellGame::GetMenuArea(COORD click)
{
	char menu = 0;

	//if in menu choices area
	if (click.X >= DISPLAY::MAIN_MENU_PLAY.X &&
		click.X <= DISPLAY::MAIN_MENU_PLAY.X + DISPLAY::MAIN_MENU_CHOICE_WIDTH)
	{
		//if in play box
		if (click.Y >= DISPLAY::MAIN_MENU_PLAY.Y && click.Y < DISPLAY::MAIN_MENU_PLAY.Y + 3)
			menu = 'P';

		//if secret cheaty spot
		if (click.Y >= DISPLAY::MAIN_MENU_TITLE.Y && click.Y < DISPLAY::MAIN_MENU_TITLE.Y + 4)
			menu = 'S';

		//if in exit box
		if (click.Y >= DISPLAY::MAIN_MENU_EXIT.Y && click.Y < DISPLAY::MAIN_MENU_EXIT.Y + 3)
			menu = 'E';
	}
	return menu;
}

/***************************************************************************************************
*	Purpose: displays the initial menu to initiate game play
*
*	Entry: none
*
*	Exit: main menu displayed
***************************************************************************************************/
void FreeCellGame::DrawInitialMenu()
{
	system("cls & color F8 & mode 39, 20");
	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = DISPLAY::MAIN_MENU_TITLE;

	//display fancy title
	if (SetConsoleCursorPosition(hStdout, position))
	{
		SetConsoleTextAttribute(hStdout, DISPLAY::PURPLE_TEXT);
		cout << " ___             ___     _ _ ___";
		position.Y++;
		SetConsoleCursorPosition(hStdout, position);
		cout << "| __| _ ___ ___ / __|___| | |__ \\";
		position.Y++;
		SetConsoleCursorPosition(hStdout, position);
		cout << "| _| '_/ -_) -_) (__/ -_) | | /_/";
		position.Y++;
		SetConsoleCursorPosition(hStdout, position);
		cout << "|_||_| \\___\\___|\\___\\___|_|_|(_)";

	}
	SetConsoleTextAttribute(hStdout, DISPLAY::DEFAULT_GAME);

	DrawMenuChoice(" Play  Game ", DISPLAY::MAIN_MENU_PLAY, DISPLAY::MAIN_MENU_CHOICE_WIDTH);
	DrawMenuChoice("    Exit    ", DISPLAY::MAIN_MENU_EXIT, DISPLAY::MAIN_MENU_CHOICE_WIDTH);

}

/***************************************************************************************************
*	Purpose: Draws a menu box
*
*	Entry: the text for the box, the position of the upper left hand side of the box, and width
*
*	Exit: displayed to screen
***************************************************************************************************/
void FreeCellGame::DrawMenuChoice(string text, COORD pos, int width)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = pos;

	position.X += 2; //spaces on sides
	position.Y++; //start text position

	if (SetConsoleCursorPosition(hStdout, position))
		cout << text.c_str();

	position = pos;
	if (SetConsoleCursorPosition(hStdout, position))
	{
		cout << DISPLAY::BOX_UPPER_LEFT_CORNER;
		for (int i(0); i < width - 1; i++)
			cout << DISPLAY::BOX_HORIZONTAL;
		cout << DISPLAY::BOX_UPPER_RIGHT_CORNER;
	}

	position = pos;
	position.Y++;
	if (SetConsoleCursorPosition(hStdout, position))
		cout << DISPLAY::BOX_VERITICAL;
	position.X += width;
	if (SetConsoleCursorPosition(hStdout, position))
		cout << DISPLAY::BOX_VERITICAL;

	position = pos;
	position.Y += 2;
	if (SetConsoleCursorPosition(hStdout, position))
	{
		cout << DISPLAY::BOX_LOWER_LEFT_CORNER;
		for (int i(0); i < width - 1; i++)
			cout << DISPLAY::BOX_HORIZONTAL;
		cout << DISPLAY::BOX_LOWER_RIGHT_CORNER;
	}
}

/***************************************************************************************************
*	Purpose: main game loop
*
*	Entry: none
*
*	Exit: game over
***************************************************************************************************/
void FreeCellGame::PlayGame()
{
	Selection from, to;
	bool game_won = false;

	DrawInitial();
	DealGame();

	do
	{
		from = MakeSelection();
		DrawInvalidMove(false); //false to clear invalid message
		if (from.type[0] != 'E') //E is exit to menu
		{
			to = MakeSelection();
			if (to.type[0] != 'E') //E is exit to menu
			{
				if (DoMove(from, to))
				{
					if (from.type[0] == 'F' || to.type[0] == 'F')
						m_free.Draw();
					if (from.type[0] == 'C' || to.type[0] == 'C')
						m_cascades.Draw();
					if (to.type[0] == 'H')
						m_home.Draw();

					game_won = GameWon();
				}
				else
				{
					DrawInvalidMove();
					game_won = false;
				}
			}
		}											//till either game is won or user exits 
	} while (!game_won && from.type[0] != 'E' && to.type[0] != 'E'); 

	if (game_won)
		DrawWon();
}

/***************************************************************************************************
*	Purpose: sets the game to be cheaty easy
*
*	Entry: none
*
*	Exit: game set to awesome
***************************************************************************************************/
void FreeCellGame::CheatyGame()
{
	for (int i(Card::KING), k(0); i >= Card::ACE; i--)
		for (int j(Card::HEART); j <= Card::SPADE; j++, k++)
			m_deck[k] = Card(Card::SUIT(j), Card::RANK(i));
}

/***************************************************************************************************
*	Purpose: deals the deck into the cascades
*
*	Entry: none
*
*	Exit: game set up
***************************************************************************************************/
void FreeCellGame::DealGame()
{
	m_cascades.DealGame(m_deck);
}

/***************************************************************************************************
*	Purpose: makes the selection for the move
*
*	Entry: none
*
*	Exit:  returns the selection
***************************************************************************************************/
FreeCellGame::Selection FreeCellGame::MakeSelection()
{
	char area = 0;
	COORD pos;
	Selection sel;
	do
	{
		do
		{
			pos = GetMouseClick();
			area = GetClickArea(pos);
		} while (area == 0);

		switch (area)
		{
			case 'F':
				sel.type = "F";
				sel.pos = ClickHF(pos, DISPLAY::FREE_UPPER_LEFT);

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
				cout << "                              ";
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
				cout << " Free cell: " << sel.pos;

				break;
			case 'H':
				sel.type = "H";
				sel.pos = ClickHF(pos, DISPLAY::HOME_UPPER_LEFT);
				break;
			case 'C':
				sel = ClickC(pos);
				break;
			case 'E':
				sel.type = "E";
				sel.pos = 0;
				break;
		}
	} while (sel.pos == -1 && sel.type[0] != 'H');

	return sel;
}

/***************************************************************************************************
*	Purpose: completes the move
* 
*	Entry: the choice
* 
*	Exit: true if the move was valid and successful
***************************************************************************************************/
bool FreeCellGame::DoMove(Selection from, Selection to)
{
	bool valid = false;

	switch (from.type[0])
	{
		case 'F':
			valid = MoveFromFree(from, to);
			break;
		case 'C':
			valid = MoveFromCascade(from, to);
			break;
	}

	return valid;
}

/***************************************************************************************************
*	Purpose: does a move that starts from a free cell
*
*	Entry: the moves data
*
*	Exit: returns true if the move was valid
***************************************************************************************************/
bool FreeCellGame::MoveFromFree(Selection from, Selection to)
{
	bool valid = !m_free.CheckEmpty(from.pos);

	if (valid)
	{
		Card temp = m_free.GetCard(from.pos);
		switch (to.type[0])
		{
			case 'H':
				valid = m_home.AddCard(temp);
				break;
			case 'F':
				valid = m_free.AddCard(temp, to.pos);
				break;
			case 'C':
				valid = m_cascades.AddCards(Stack<Card>(temp),to.type[1]-'A',m_free.GetNumEmpty());
				break;
		}
		if (valid)
			m_free.EmptyPosition(from.pos);
	}
	return valid;
}

/***************************************************************************************************
*	Purpose: executes a move from a cascade
*
*	Entry: the move data
*
*	Exit: returns true if the move is valid
***************************************************************************************************/
bool FreeCellGame::MoveFromCascade(Selection from, Selection to)
{
	bool valid = true;
	Stack<Card> temp;
									  // - 'A' because columns are listed as A - H
	try { temp = m_cascades.GetCards(from.type[1] - 'A', from.pos); } //throws exception if invalid
	catch (...) { valid = false; }		//returns cards in reverse order

	if (valid)
	{
		int size = temp.Size();

		if (size > 1 && (to.type[0] == 'F' || to.type[0] == 'H'))//only 1 card in those places
			valid = false;
		else
		{
			switch (to.type[0])
			{
				case 'F':
					valid = m_free.AddCard(temp.Peek(), to.pos);
					break;
				case 'H':
					valid = m_home.AddCard(temp.Peek());
					break;
				case 'C':
					valid = m_cascades.AddCards(temp, to.type[1] - 'A', m_free.GetNumEmpty());
					break;
			}

			if (valid)
				m_cascades.RemoveCards(from.type[1] - 'A', from.pos);
		}
	}
	return valid;
}

/***************************************************************************************************
*	Purpose: checks to see if the game is won
*
*	Entry: none
*
*	Exit: true if all home cells are full
***************************************************************************************************/
bool FreeCellGame::GameWon()
{
	return m_home.HomeFull();
}

/***************************************************************************************************
*	Purpose: clears the game so it can start over
*
*	Entry: none
*
*	Exit: everything is emptied
***************************************************************************************************/
void FreeCellGame::StartOver()
{
	m_free.Clear();
	m_home.Clear();
	m_cascades.Clear();
}

/***************************************************************************************************
*	Purpose: draws the board
*
*	Entry: none
*
*	Exit: beginning board drawn
***************************************************************************************************/
void FreeCellGame::DrawInitial()
{
	system("cls & color F8 & mode 86, 65");  // width, height
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//Draw empty free cells
	DrawInitialHF(DISPLAY::FREE_UPPER_LEFT, FreeCells::FREE_AMOUNT);

	//Draw empty home cells
	DrawInitialHF(DISPLAY::HOME_UPPER_LEFT, HomeCells::HOME_AMOUNT);

	//Draw empty Cascade spots
	COORD position = DISPLAY::CASC_UPPER_LEFT;
	for (int i(0); i < Cascades::CASCADE_AMOUNT; i++)
	{
		Card::DrawEmpty(position);
		position.X += DISPLAY::SINGLE_CARD_WIDTH + DISPLAY::SPACE_BTWN_CARDS;
	}

	//Display Main Menu box
	DrawMenuChoice("Main  Menu", DISPLAY::MENU_UPPER_LEFT, DISPLAY::MENU_WIDTH);
}

/***************************************************************************************************
*	Purpose: draws the initial layout for the free or home cells
*
*	Entry: the position of the upper left corner of the first card and number of cards
*
*	Exit: drawn to screen
***************************************************************************************************/
void FreeCellGame::DrawInitialHF(COORD pos, int num)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = pos;
	position.X -= 2;
	position.Y -= 1;
	int inner_width = (DISPLAY::SINGLE_CARD_WIDTH * num)+((num - 1) * DISPLAY::SPACE_BTWN_CARDS)+2;
	int inner_height = (DISPLAY::SINGLE_CARD_HEIGHT);

	//section box - upper
	if (SetConsoleCursorPosition(hStdout, position))
	{
		cout << DISPLAY::BOX_UPPER_LEFT_CORNER;
		for (int i(0); i < inner_width; i++)
			cout << DISPLAY::BOX_HORIZONTAL;
		cout << DISPLAY::BOX_UPPER_RIGHT_CORNER;
	}

	//section box - sides
	for (int i(0); i < inner_height; i++)
	{
		position.Y++;

		position.X = pos.X - 2;
		if (SetConsoleCursorPosition(hStdout, position))
			cout << DISPLAY::BOX_VERITICAL;

		position.X += inner_width + 1;
		if (SetConsoleCursorPosition(hStdout, position))
			cout << DISPLAY::BOX_VERITICAL;
	}

	//section box - bottom
	position = pos;
	position.X -= 2;
	position.Y += DISPLAY::SINGLE_CARD_HEIGHT;
	if (SetConsoleCursorPosition(hStdout, position))
	{
		cout << DISPLAY::BOX_LOWER_LEFT_CORNER;
		for (int i(0); i < inner_width; i++)
			cout << DISPLAY::BOX_HORIZONTAL;
		cout << DISPLAY::BOX_LOWER_RIGHT_CORNER;
	}

	//draw empty cards
	position = pos;
	for (int i(0); i < num; i++)
	{
		Card::DrawEmpty(position);
		position.X += DISPLAY::SINGLE_CARD_WIDTH + DISPLAY::SPACE_BTWN_CARDS;
	}
}

/***************************************************************************************************
*	Purpose: Displays invalid move
*
*	Entry: none
*
*	Exit: displayed to screen
***************************************************************************************************/
void FreeCellGame::DrawInvalidMove(bool message /*= true*/)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (SetConsoleCursorPosition(hStdout, DISPLAY::INVALID_MOVE_TEXT))
	{
		SetConsoleCursorPosition(hStdout, DISPLAY::INVALID_MOVE_TEXT);
		if(message)
			cout << "Invalid Move";
 		else
			cout << "            ";
	}
	_flushall();
}

/***************************************************************************************************
*	Purpose: gets a mouse click from the screen
*
*	Entry: none
*
*	Exit: returns the coordinate of the click
***************************************************************************************************/
COORD FreeCellGame::GetMouseClick()
{
	HANDLE ConsoleIn(GetStdHandle(STD_INPUT_HANDLE));
	DWORD ConsoleMode;
	DWORD InputEvents;
	DWORD EventCount;
	INPUT_RECORD InputBuffer;
	GetConsoleMode(ConsoleIn, &ConsoleMode);
	SetConsoleMode(ConsoleIn, ConsoleMode | ENABLE_MOUSE_INPUT);

	bool click = false;
	while (!click)
	{
		GetNumberOfConsoleInputEvents(ConsoleIn, &EventCount);
		if (EventCount > 0)
		{
			ReadConsoleInput(ConsoleIn, &InputBuffer, 1, &InputEvents);
			if ((InputBuffer.EventType==MOUSE_EVENT)&&(InputBuffer.Event.MouseEvent.dwButtonState))
				click = true;
		}
	}
	return InputBuffer.Event.MouseEvent.dwMousePosition;
}

/***************************************************************************************************
*	Purpose: gets the area the click was in
*
*	Entry: the coordinate of click
*
*	Exit: char representing the area
***************************************************************************************************/
char FreeCellGame::GetClickArea(COORD click)
{
	char choice = 0;

	//if click is in main menu box
	if (click.X >= DISPLAY::MENU_UPPER_LEFT.X && click.Y >= DISPLAY::MENU_UPPER_LEFT.Y &&
		click.X <= DISPLAY::MENU_UPPER_LEFT.X + DISPLAY::MENU_WIDTH &&
		click.Y <= DISPLAY::MENU_UPPER_LEFT.Y + 2)
		choice = 'E';

	//else if in the home or free cells area
	else if (click.Y >= DISPLAY::FREE_UPPER_LEFT.Y &&
			 click.Y <= DISPLAY::FREE_UPPER_LEFT.Y + DISPLAY::SINGLE_CARD_HEIGHT)
	{
		//if in the free cells box
		if (click.X >= DISPLAY::FREE_UPPER_LEFT.X && click.X <= DISPLAY::FREE_UPPER_LEFT.X +
			(FreeCells::FREE_AMOUNT * DISPLAY::SINGLE_CARD_WIDTH) +
			((FreeCells::FREE_AMOUNT - 1) * DISPLAY::SPACE_BTWN_CARDS))
			choice = 'F';

		//else if in the home cells box
		else if (click.X >= DISPLAY::HOME_UPPER_LEFT.X && click.X <= DISPLAY::HOME_UPPER_LEFT.X +
				 (HomeCells::HOME_AMOUNT * DISPLAY::SINGLE_CARD_WIDTH) +
				 ((HomeCells::HOME_AMOUNT - 1) * DISPLAY::SPACE_BTWN_CARDS))
				 choice = 'H';
	}

	//else if cascades area
	else if (click.Y >= DISPLAY::CASC_UPPER_LEFT.Y && click.X >= DISPLAY::CASC_UPPER_LEFT.X &&
			 click.X <= DISPLAY::CASC_UPPER_LEFT.X +
			 DISPLAY::SINGLE_CARD_WIDTH * Cascades::CASCADE_AMOUNT +
			 (Cascades::CASCADE_AMOUNT - 1) * DISPLAY::SPACE_BTWN_CARDS)
			 choice = 'C';		

	return choice;
}

/***************************************************************************************************
*	Purpose: gets the position of the card clicked in the area
*
*	Entry: the coord for the click, and the coord for the upper left of the area
*
*	Exit: the position of the card, or -1 if click not good
***************************************************************************************************/
int FreeCellGame::ClickHF(COORD click, COORD up_left)
{
	int pos = -1;

	//check each card if click is in it
	for (int i(0), x(up_left.X); i < FreeCells::FREE_AMOUNT && pos == -1; i++, 
		                            x += (DISPLAY::SINGLE_CARD_WIDTH + DISPLAY::SPACE_BTWN_CARDS))
		if (click.X >= x && click.X <= x + DISPLAY::SINGLE_CARD_WIDTH)
			pos = i; //if click in this card, set position to return

	return pos;
}

/***************************************************************************************************
*	Purpose: gets the specific position of the card clicked in the play area
*
*	Entry: the coord of the lick
*
*	Exit: returns selection set to the card picked
***************************************************************************************************/
FreeCellGame::Selection FreeCellGame::ClickC(COORD click)
{
	Selection sel;
	sel.type = 'C';
	sel.pos = -1;
	int col = -1;

	//find column click is in
	for (int i(0), x(DISPLAY::CASC_UPPER_LEFT.X); i < Cascades::CASCADE_AMOUNT && col == -1; i++)
		if (click.X >= x && click.X <= x + DISPLAY::SINGLE_CARD_WIDTH)
			col = i; //if click in this column, set col
		else
			x += DISPLAY::SINGLE_CARD_WIDTH + DISPLAY::SPACE_BTWN_CARDS;
	if (col != -1)
	{
		char column[2] = { col + 'A', 0 };
		sel.type.append(column); //set column in selection

		//find position in the column
		int size = m_cascades.GetSize(col);
		int y = DISPLAY::CASC_UPPER_LEFT.Y;
		if (size == 0)
		{
			if (click.Y >= y && click.Y < y + DISPLAY::SINGLE_CARD_HEIGHT)
				sel.pos = 0;
		}
		else//check all cards that are partially obscured
		{
			for (int i(0); i < size - 1 && sel.pos == -1; i++)
			{
				if (click.Y >= y && click.Y < y + 2)
					sel.pos = i;
				else
					y += 2;
			}
			if (sel.pos == -1)
				if (click.Y >= y && click.Y < y + DISPLAY::SINGLE_CARD_HEIGHT)
					sel.pos = size - 1; //last card on the stack
		}
	}
	
	return sel;
}

/***************************************************************************************************
*	Purpose: draws a screen indicating the game was won
*
*	Entry: none
*
*	Exit: YOU WON
***************************************************************************************************/
void FreeCellGame::DrawWon()
{
	system("cls & color F8 & mode 39, 20");

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = DISPLAY::MAIN_MENU_TITLE;

	//display fancy title
	if (SetConsoleCursorPosition(hStdout, position))
	{
		SetConsoleTextAttribute(hStdout, DISPLAY::PURPLE_TEXT);
		cout << " ___             ___     _ _ ___";
		position.Y++;
		SetConsoleCursorPosition(hStdout, position);
		cout << "| __| _ ___ ___ / __|___| | |__ \\";
		position.Y++;
		SetConsoleCursorPosition(hStdout, position);
		cout << "| _| '_/ -_) -_) (__/ -_) | | /_/";
		position.Y++;
		SetConsoleCursorPosition(hStdout, position);
		cout << "|_||_| \\___\\___|\\___\\___|_|_|(_)";

	}
	SetConsoleTextAttribute(hStdout, DISPLAY::DEFAULT_GAME);

	position = DISPLAY::MAIN_MENU_PLAY;
	position.X -= 6;
	if (SetConsoleCursorPosition(hStdout, position))
		cout << "wow. much freecell. such win.";

	GetMouseClick();//waits for click
}