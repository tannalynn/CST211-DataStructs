/***************************************************************************************************
* Author:						Tanna McClure
* File:							Source.cpp
* Date Created:					2/22/2015
*
* Overview:
*		Creates a tree of the directory given and all subdirectories
* 
* Input:
*		none
*
* Output:
*		program displays the contents of the tree to the console and stores it in a file
*	
***************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::cin;
#include "DirectoryTree.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//C:\\Users\\Nayru\\downloaded\\The Mindy Project
	DirectoryTree a("C:");
	DirectoryTree b(a); //checking assignment op and copy ctor
	b.DisplayTree();
	b.FileWrite("files.txt");

	cin.get();
	return 0;
}