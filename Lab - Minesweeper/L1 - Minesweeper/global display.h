/***************************************************************************************************
* Author:						Tanna McClure
* File:							global display.h
* Date Created:					1/14/2015
*
* Modification Date: 			1/15/2015
* Modification: 				added board boundary variables
*		  
***************************************************************************************************/
#ifndef DISPLAY_H
#define DISPLAY_H
namespace DISPLAY
{
	//board boundaries - variables - in cpp
	extern int board_cols_min;
	extern int board_rows_min;
	extern int board_rows_max;
	extern int board_cols_max;

	//height and width of the cell 
	const unsigned int CELL_HEIGHT = 2;
	const unsigned int CELL_WIDTH = 4;

	//Display characters
	const unsigned char UPPER_LEFT_CORNER = 218;
	const unsigned char UPPER_RIGHT_CORNER = 191;
	const unsigned char LOWER_LEFT_CORNER = 192;
	const unsigned char LOWER_RIGHT_CORNER = 217;
	const unsigned char HORIZONTAL = 196;
	const unsigned char VERTICAL = 179;
	const unsigned char CROSS = 197;
	const unsigned char LEFT_CROSS = 195;
	const unsigned char RIGHT_CROSS = 180;
	const unsigned char HIDDENCELL = 177;
	const unsigned char TOP_CROSS = 194;
	const unsigned char BOTTOM_CROSS = 193;

	//color constants - all with white background
	const unsigned int WHITE_BACKGROUND = 0xF0;
	const unsigned int BLACK_TEXT = 0xF0;
	const unsigned int GREY_DARK_TEXT = 0xF8;
	const unsigned int GREY_LIGHT_TEXT = 0xF7;
	const unsigned int RED_DARK_TEXT = 0xF4;
	const unsigned int RED_BRIGHT_TEXT = 0xFC;
	const unsigned int BLUE_DARK_TEXT = 0xF1;
	const unsigned int BLUE_BRIGHT_TEXT = 0xF9;
	const unsigned int GREEN_DARK_TEXT = 0xF2;
	const unsigned int GREEN_BRIGHT_TEXT = 0xFA;
	const unsigned int TEAL_DARK_TEXT = 0xF3;
	const unsigned int TEAL_BRIGHT_TEXT = 0xFB;
	const unsigned int PURPLE_TEXT = 0xF5;
	const unsigned int MAGENTA_TEXT = 0xFD;
	const unsigned int BOMB_TEXT = 0xCF;
	const unsigned int FLAGGED_TEXT = 0x7F;
}
#endif