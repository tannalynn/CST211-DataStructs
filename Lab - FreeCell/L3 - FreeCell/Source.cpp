/***************************************************************************************************
* Author:						Tanna McClure
* File:							Source.cpp
* Date Created:					1/29/2015
*
* Overview: 
*		initializes game
* 
* Input: 
*		none
*
* Output: 
*		the game
*	
***************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "FreeCellGame.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FreeCellGame a;
	a.StartGame();

	return 0;
}