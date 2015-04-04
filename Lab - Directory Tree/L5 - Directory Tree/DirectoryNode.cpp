/***************************************************************************************************
* Author:						Tanna McClure
* File:							DirectoryNode.cpp
* Date Created:					2/24/2015 
*
* Modification Date:			2/25/2015 
* Modification:					wrote Write function
*
***************************************************************************************************/
#include "DirectoryNode.h"
/***************************************************************************************************
*	Purpose: 2 arg constructor
*
*	Entry: the path of the file and the name of the file
*
*	Exit: entire directory has been put into the tree
***************************************************************************************************/
DirectoryNode::DirectoryNode(string path, string name): m_name(name), m_path(path)
{
	WIN32_FIND_DATAA find;
	string new_path = m_path + m_name + "\\*";
	HANDLE handle = FindFirstFileA(new_path.c_str(), &find);
	new_path.pop_back(); //remove *

	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			string filename = find.cFileName;
			if (filename != "." && filename != "..")
				m_children.Append(new DirectoryNode(new_path, filename));
		} while (FindNextFileA(handle, &find) != 0);
	}
	FindClose(handle);
}
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the node to copy
*
*	Exit: object created
***************************************************************************************************/
DirectoryNode::DirectoryNode(const DirectoryNode & copy)
{
	*this = copy;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the node to copy
*
*	Exit: object copied
***************************************************************************************************/
DirectoryNode & DirectoryNode::operator=(const DirectoryNode & rhs)
{
	if (this != &rhs)
	{
		m_name = rhs.m_name;
		m_path = rhs.m_path;
		ForwardIterator<DirectoryNode*> iter(&rhs.m_children);
		for (iter.Reset(); !iter.IsDone(); iter.MoveNext())
			m_children.Append(new DirectoryNode(*iter.GetCurrent()));
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: deletes dynamic memory allocated in constructor
*
*	Exit: everything is dead
***************************************************************************************************/
DirectoryNode::~DirectoryNode()
{
	while (!m_children.isEmpty())
		delete m_children.RemoveFirst();
}
/***************************************************************************************************
*	Purpose: insert into ostream
* 
*	Entry: the stream to do stuff with
* 
*	Exit: it happened
***************************************************************************************************/
void DirectoryNode::Write(ostream & out, int tabs)
{
	if (!m_children.isEmpty())
	{
		for (int i(0); i < tabs; i++)
			out << "\t";
		out << "Directory: " <<m_path << "\ " << m_name << "\n";
		ForwardIterator<DirectoryNode*> iter(&m_children);
		for (iter.Reset(); !iter.IsDone(); iter.MoveNext())
			iter.GetCurrent()->Write(out, tabs+1);
	}
	else
	{
		for (int i(0); i < tabs; i++)
			out << "\t";
		out << "- File: " << m_name << "\n";
	}
}