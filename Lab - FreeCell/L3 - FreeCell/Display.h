/***************************************************************************************************
* Author:						Tanna McClure
* File:							global display.h
* Date Created:					1/14/2015
*
* Modification Date: 			2/5/2015
* Modification: 				updated for free cell
*
***************************************************************************************************/
#ifndef DISPLAY_H
#define DISPLAY_H
#include <Windows.h>
namespace DISPLAY
{
	//width for display
	const int SINGLE_CARD_HEIGHT = 6;
	const int SINGLE_CARD_WIDTH = 6;
	const int SPACE_BTWN_CARDS = 2;
	const int MENU_WIDTH = 13;
	const int MAIN_MENU_CHOICE_WIDTH = 15;

	//coordinates for display
	const COORD FREE_UPPER_LEFT = { 6, 6 };
	const COORD HOME_UPPER_LEFT = { 50, 6 };
	const COORD CASC_UPPER_LEFT = { 12, 16 };
	const COORD MENU_UPPER_LEFT = { 36, 1 };
	const COORD INVALID_MOVE_TEXT = { 37, 13 };
	const COORD MAIN_MENU_PLAY = { 11, 8 };
	const COORD MAIN_MENU_EXIT = { MAIN_MENU_PLAY.X, MAIN_MENU_PLAY.Y + 4 };
	const COORD MAIN_MENU_TITLE = { 3, 1 };

	//Display characters
	const unsigned char CARD_UPPER_LEFT_CORNER = 218;
	const unsigned char CARD_UPPER_RIGHT_CORNER = 191;
	const unsigned char CARD_LOWER_LEFT_CORNER = 192;
	const unsigned char CARD_LOWER_RIGHT_CORNER = 217;
	const unsigned char CARD_HORIZONTAL = 196;
	const unsigned char CARD_VERTICAL = 179;

	//Display box characters
	const unsigned char BOX_UPPER_LEFT_CORNER = 201;
	const unsigned char BOX_UPPER_RIGHT_CORNER = 187;
	const unsigned char BOX_LOWER_LEFT_CORNER = 200;
	const unsigned char BOX_LOWER_RIGHT_CORNER = 188;
	const unsigned char BOX_HORIZONTAL = 205;
	const unsigned char BOX_VERITICAL = 186;

	//color constants - all with white background
	const unsigned int BLACK_TEXT = 0xF0;
	const unsigned int GREY_DARK_TEXT = 0xF8;
	const unsigned int RED_BRIGHT_TEXT = 0xFC;
	const unsigned int PURPLE_TEXT = 0xF5;

	const unsigned int RED_CARD_TEXT = RED_BRIGHT_TEXT;
	const unsigned int BLACK_CARD_TEXT = BLACK_TEXT;
	const unsigned int DEFAULT_GAME = GREY_DARK_TEXT;
}
#endif