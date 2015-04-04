/***************************************************************************************************
* Author:						Tanna McClure
* File:							Source.cpp
* Date Created:					2/13/2015
*
* Overview:
*		tests BinaryTree and BinarySearchTree classes
* 
* Input:
*		none
*
* Output:
*		results of test
*	
***************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
using std::cout;
using std::cin;

#include "BinarySearchTree.h"

void Display(const int &num); //displays an integers
void TestBinaryTree();		  //tests the BinaryTree Class
void TestBinarySearchTree();  //tests the BinarySearchTreeClass

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TestBinaryTree();
	cout << "\n\n\nPress Enter ";

	cin.get();
	cout << "\n\n";

	TestBinarySearchTree();

	cout << "\n\n\nPress Enter ";
	cin.get();
	return 0;
}
/***************************************************************************************************
*	Purpose: displays an int
*
*	Entry: number to display
*
*	Exit: displayed
***************************************************************************************************/
void Display(const int &num)
{
	cout << " " << num << " ";
}
/***************************************************************************************************
*	Purpose: tests the binary tree base class functions that are overridden in derived class
*
*	Entry: none
*
*	Exit: none
***************************************************************************************************/
void TestBinaryTree()
{
	BinaryTree<int> b;
	b.Insert(1);						 //				  1
	b.Insert(2);						 //			2		    3
	b.Insert(3);						 //		4		5   6		7
	b.Insert(4);						 //	  8
	b.Insert(5);						 
	b.Insert(6);						 
	b.Insert(7);
	b.Insert(8);

	b.TraverseBreadth(Display);

	b.Delete(2);
	cout << "\n\nBinaryTree - After deleting 2: \n";
	b.TraverseBreadth(Display);

	b.Delete(7);
	cout << "\n\nBinaryTree - After deleting 7: \n";
	b.TraverseBreadth(Display);

	b.Delete(1);
	cout << "\n\nBinaryTree - After deleting 1: \n";
	b.TraverseBreadth(Display);

	b.Delete(3);
	b.Delete(4);
	b.Delete(5);
	b.Delete(8);
	cout << "\n\nBinaryTree - After deleting everything but 6: \n";
	b.TraverseBreadth(Display);
	try { b.Delete(0); } catch (...) { cout << "   Good.  "; }

	b.Delete(6);
	cout << "\n\nBinaryTree - After deleting 6 IsEmpty?:  " << (b.IsEmpty()? "true":"false") <<"\n";
}
/***************************************************************************************************
*	Purpose: tests binary search tree class
*
*	Entry: none
*
*	Exit: none
***************************************************************************************************/
void TestBinarySearchTree()
{
	BinarySearchTree<int> a; //default constructor

	//testing insert an height functions                            my beautiful tree
	a.Insert(30);							//							   30
	cout << "Height(0): " << a.Height() << "\n";//					  /			\.
	a.Insert(40);							//				   20				    40
	cout << "Height(1): " << a.Height() << "\n";//		    /	  \				 /		 \.
	a.Insert(20);	 						//		   10		   25		 35		        50
	cout << "Height(1): " << a.Height() << "\n";//		 \		  /	  \		  \			   /
	a.Insert(10);	 						//           15     23     27	  38        49
	cout << "Height(2): " << a.Height() << "\n";//					   /	   \		/
	a.Insert(15);							//					     26		   39    47
	cout << "Height(3): " << a.Height() << "\n";//									  \.
	a.Insert(25);							//										    48
	cout << "Height(3): " << a.Height() << "\n";
	a.Insert(23);
	cout << "Height(3): " << a.Height() << "\n";
	a.Insert(27);
	cout << "Height(3): " << a.Height() << "\n";
	a.Insert(26);
	cout << "Height(4): " << a.Height() << "\n";
	a.Insert(35);
	cout << "Height(4): " << a.Height() << "\n";
	a.Insert(50);
	cout << "Height(4): " << a.Height() << "\n";
	a.Insert(38);
	cout << "Height(4): " << a.Height() << "\n";
	a.Insert(39);
	cout << "Height(4): " << a.Height() << "\n";
	a.Insert(40); //shouldn't add another 40
	cout << "Height(4): " << a.Height() << "\n";
	a.Insert(49);
	cout << "Height(4): " << a.Height() << "\n";
	a.Insert(47);
	cout << "Height(4): " << a.Height() << "\n";
	a.Insert(48);
	cout << "Height(5): " << a.Height() << "\n";

	//testing traversal functions
	cout << "\n\nIn Order:\n";
	a.TraverseInOrder(Display);
	cout << "\nBreadth:\n";
	a.TraverseBreadth(Display);
	cout << "\nPre-Order:\n";
	a.TraversePreOrder(Display);
	cout << "\nPost-Order:\n";
	a.TraversePostOrder(Display);

	//testing delete
	a.Delete(40);
	cout << "\n\nIn order after delete 40:\n";
	a.TraverseInOrder(Display);
	try { a.Delete(40); cout << "    Bad."; } catch (...) { cout << "     Good."; }
	a.Delete(30);
	cout << "\nIn order after delete 30:\n";
	a.TraverseInOrder(Display);
	a.Delete(10);
	cout << "\nIn order after delete 10:\n";
	a.TraverseInOrder(Display);

	//testing copy ctor and =
	BinarySearchTree<int> b(a);
	cout << "\n\nCopy constructor copying last tree:\n";
	b.TraverseInOrder(Display);
	b.Purge();
	if (b.IsEmpty())
		cout << "\nPurged and then assignment operator:\n";
	b = a; 
	b.TraverseInOrder(Display);
}