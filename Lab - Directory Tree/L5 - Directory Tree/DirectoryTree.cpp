/***************************************************************************************************
* Author:						Tanna McClure
* File:							DirectoryTree.cpp
* Date Created:					2/24/2015
*
* Modification Date: 			2/25/2015
* Modification: 				wrote assignment op and copy ctor
*		  
***************************************************************************************************/
#include "DirectoryTree.h" 
/***************************************************************************************************
*	Purpose: 1 arg ctor
*
*	Entry: the directory to search in 
*
*	Exit: tree created
***************************************************************************************************/
DirectoryTree::DirectoryTree(string start): m_root(new DirectoryNode(start, ""))
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry:
*
*	Exit:
***************************************************************************************************/
DirectoryTree::DirectoryTree(const DirectoryTree & copy):m_root(new DirectoryNode(*copy.m_root))
{ }
/***************************************************************************************************
*	Purpose: deletes root(which deletes all it's children)
*
*	Entry: none
*
*	Exit: object destroyed 
***************************************************************************************************/
DirectoryTree::~DirectoryTree()
{ 
	delete m_root;
}
/***************************************************************************************************
*	Purpose: Displays tree to the console window
*
*	Entry: none
*
*	Exit: data displayed
***************************************************************************************************/
void DirectoryTree::DisplayTree()
{
	m_root->Write(std::cout);
}
/***************************************************************************************************
*	Purpose: Writes the tree to a file
*
*	Entry: the name of the file
*
*	Exit: file written
***************************************************************************************************/
void DirectoryTree::FileWrite(string filename)
{
	ofstream out(filename.c_str());

	if (out.is_open())
	{
		m_root->Write(out);
		out.close();
	}
	else
		std::cout << "\n\nYou got issues.\n\n";
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the tree to copy
*
*	Exit: rhs copied
***************************************************************************************************/
DirectoryTree & DirectoryTree::operator=(const DirectoryTree & rhs)
{
	if (this != &rhs)
	{
		delete m_root;
		m_root = new DirectoryNode(*rhs.m_root);
	}
	return *this;
}