/***************************************************************************************************
* Author:						Tanna McClure
* File:							DirectoryNode.h
* Date Created:					2/22/2015
*
* Modification Date: 			2/26/2015
* Modification: 				finished commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: DirectoryNode
*
*	Purpose: 
*		Contains the name, path and if it is a directory, all subdirectories and files of the folder
*
*	Manager Functions: 
*		DirectoryNode(string path, string name);
*			2 arg Constructor
*		DirectoryNode(const DirectoryNode & copy);
*			Copy Constructor
*		~DirectoryNode();
*			Destructor
*		DirectoryNode & operator = (const DirectoryNode & rhs);
*			Assignment operator
*
*	Methods: 
*		void Write(ostream & out, int tabs = 0); 
*			Writes the node information(and all children) to the ostream object passed in
*
***************************************************************************************************/
#ifndef DIRECTORYNODE_H
#define DIRECTORYNODE_H
#include <string>
using std::string;
#include <fstream>
using std::ofstream;
#include <windows.h>
#include "DoubleLinkedList.h"
#include "ForwardIterator.h"
class DirectoryNode
{
	friend class DirectoryTree;
private:
			//2 arg Constructor
	DirectoryNode(string path, string name);
			//Destructor
	~DirectoryNode();
			//Assignment Operator
	DirectoryNode & operator= (const DirectoryNode & rhs);
			//Copy Constructor
	DirectoryNode(const DirectoryNode & copy);
			//writes name and all children to file
	void Write(ostream & out, int tabs = 0); 

	string m_name;
	string m_path;
	DoubleLinkedList<DirectoryNode *> m_children;
};
#endif