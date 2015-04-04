/***************************************************************************************************
* Author:						Tanna McClure
* File:							main.cpp
* Date Created:					1/11/2015
*
* Overview:
*		Calls the minesweeper class and plays the game
* 
* Input:
*		Minesweeper asks for positions on the board to uncover
*
* Output:
*		The screen is updated after selecting a cell
*	
***************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Minesweeper.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Minesweeper a;
	a.Play();

	return 0;
}
