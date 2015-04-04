/***************************************************************************************************
* Author:						Tanna McClure
* File:							Source.cpp
* Date Created:					2/11/2015
*
* Overview:
*		tests functionality of iterators
* 
* Input:
*		none
*
* Output:
*		each node in forwards and backwards
*	
***************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
using std::cout;
using std::cin;
using std::string;

#include "ForwardIterator.h"
#include "BackwardsIterator.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DoubleLinkedList<string> list;
	list.Append("First");
	list.Append("Second");
	list.Append("Third");
	list.Append("Fourth");

	ForwardIterator<string> fi(&list);
	cout << "Forwards: \n";
	for (fi.Reset(); !fi.IsDone(); fi.MoveNext())
		cout << "\t" << fi.GetCurrent().c_str() << "\n";
	

	BackwardsIterator<string> bi(&list);
	cout << "\n\nBackwards:\n";
	for (bi.Reset(); !bi.IsDone(); bi.MoveNext())
		cout << "\t" << bi.GetCurrent().c_str() << "\n";

	ForwardIterator<string> fi2(fi);
	cout << "\n\nForwards (made w/ copy ctor): \n";
	for (fi2.Reset(); !fi2.IsDone(); fi2.MoveNext())
		cout << "\t" << fi2.GetCurrent().c_str() << "\n";

	BackwardsIterator<string> bi2(bi);
	cout << "\n\nBackwards (made w/ copy ctor):\n";
	for (bi2.Reset(); !bi2.IsDone(); bi2.MoveNext())
		cout << "\t" << bi2.GetCurrent().c_str() << "\n";

	DoubleLinkedList<string> list2;
	list2.Append("First - 2");
	list2.Append("Second - 2");
	list2.Append("Third - 2");
	list2.Append("Fourth - 2");
	ForwardIterator<string> fi3(&list2);
	fi2 = fi3;
	cout << "\n\nForwards (made w/ = op): \n";
	for (fi2.Reset(); !fi2.IsDone(); fi2.MoveNext())
	{
		fi2.GetCurrent().append(" - added"); //able to change the node
		cout << "\t" << fi2.GetCurrent().c_str() << "\n";
	}

	BackwardsIterator<string> bi3(&list2);
	bi2 = bi3;
	cout << "\n\nBackwards (made w/ = op):\n";
	for (bi2.Reset(); !bi2.IsDone(); bi2.MoveNext())
		cout << "\t" << bi2.GetCurrent().c_str() << "\n";

	DoubleLinkedList<const string> list3;
	list3.Append("const First"); 
	list3.Append("const Second");
	list3.Append("const Third"); 
	cout << "\n\nForwards w/ consts: \n";
	ForwardIterator<const string> cfi(&list3);
	for (cfi.Reset(); !cfi.IsDone(); cfi.MoveNext())
		cout << "\t" << cfi.GetCurrent().c_str() << "\n";
	cout << "\n\n";
	const DoubleLinkedList<const string> cl(list3);
	ForwardIterator<const string> ccfi(&cl);
	for (ccfi.Reset(); !ccfi.IsDone(); ccfi.MoveNext())
		cout << "\t" << ccfi.GetCurrent().c_str() << "\n";

	cin.get();
	return 0;
}