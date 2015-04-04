/***************************************************************************************************
* Author:						Tanna McClure
* File:							DirectoryTree.h
* Date Created:					2/22/2015
*
* Modification Date: 			2/26/2015
* Modification: 				Finished Commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: DirectoryTree
*
*	Purpose: 
*		Stores a tree that contains the paths and names of all files in a given directory
*
*	Manager Functions: 
*		DirectoryTree(string start = "C:");
*			Default Constructor
*		DirectoryTree(const DirectoryTree & copy);
*			Copy Constructor
*		~DirectoryTree();
*			Destructor
*		DirectoryTree & operator = (const DirectoryTree & rhs);
*			Assignment operator
*
*	Methods: 
*		void DisplayTree();
*			Displays the entire tree to the console window
*		void FileWrite(string filename);
*			Writes the entire tree to a file
*
***************************************************************************************************/
#ifndef DIRECTORYTREE_H
#define DIRECTORYTREE_H
#include "DirectoryNode.h"

class DirectoryTree
{
public:
			//Default Constructor
	DirectoryTree(string start = "C:");
			//Destructor
	~DirectoryTree();
			//Assignment Operator
	DirectoryTree & operator = (const DirectoryTree & rhs);
			//Copy Constructor 
	DirectoryTree(const DirectoryTree & copy);
			//Calls display on root
	void DisplayTree();
			//Calls FileWrite on root
	void FileWrite(string filename);

private:
	DirectoryNode * m_root;
};
#endif