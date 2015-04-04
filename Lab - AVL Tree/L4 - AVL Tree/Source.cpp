/***************************************************************************************************
* Author:						Tanna McClure
* File:							Source.cpp
* Date Created:					2/16/2015
*
* Overview:
*		 OKAY SO... it didn't work correctly. sometimes... so I fixed it.. and now it's late. but i 
*		 didn't know what was wrong until i was helping someone else. SO it's late and that sucks
*		 but i figured re-uploading it late but fixed is better than having it not quite right....?
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

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

#include "AVLTree.h"

void Display(const int &num);
 //8 9 10 2 1 5 3 6 4 7 11 
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	AVLTree<int> a;

	auto start = high_resolution_clock::now();
	for (int i(0); i < 100000; i++)
		a.Insert(rand()); //see how long it takes with a ton of stuff. curious
	
	auto end = high_resolution_clock::now();
	auto time = end - start;

 	cout <<"\n\n\n100,000 rand inserts: " << duration_cast<microseconds>(time).count() / 1000000.0 << " seconds\n\n";
	a.Purge(); //DO IT AGAIN
	cout << "Same as from slides: \n";

	a.Insert(8);
	a.Insert(9);
	a.Insert(10);
	a.Insert(2);
	a.Insert(1);
	a.Insert(5);
	a.Insert(3);
	a.Insert(6);
	a.Insert(4);
	a.Insert(7);
	a.Insert(11);

	a.TraverseInOrder(Display);
	cout << "\n\n";
	a.TraverseBreadth(Display);

	a.Delete(1);// test delete
	a.Delete(3);

	AVLTree<int> b(a); //copy ctor && assignment op
	cout << "\n\nPress Enter...\n";
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
	cout << " " << num << "\n";
}