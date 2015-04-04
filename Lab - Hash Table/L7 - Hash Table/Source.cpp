/***************************************************************************************************
* Author:						Tanna McClure
* File:							Source.cpp
* Date Created:					3/10/2015
*
* Overview:
*		tests hash table class
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
#include <string>
#include "HashTable.h"
using std::cout;
using std::cin;
using std::string;

struct Book
{
	Book(char * t, char * a, int p): m_title(t), m_author(a), m_pages(p) { }
	Book() { }
	string m_title;
	string m_author;
	int m_pages;
};
int asciihash(string i);
int hash2(string i);
void display(const Book & book);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HashTable<string, Book> table(asciihash); //ctor

	table.Insert("0001", Book("title" , "author" , 1)); //insert
	table.Insert("0082", Book("title2", "author2", 2));
	table.Insert("0003", Book("title3", "author3", 3));
	table.Insert("0934", Book("title4", "author4", 4));
	table.Insert("0005", Book("title5", "author5", 5));
	table.Insert("0006", Book("title6", "author6", 6));
	table.Insert("0307", Book("title7", "author7", 7));
	table.Insert("0008", Book("title8", "author8", 8));
	table.Insert("0008", Book("title9", "author9", 9));

	table["0005"].m_title = "chicken nuggets"; //[]
	HashTable<string, Book> copy(table); //copy ctor

	copy.SetHash(hash2); //set hash
	

	table = copy; // =
	copy.SetSize(4); //set size

	copy.Delete("0082"); //delete
	copy.Delete("0934");
	copy.Delete("0008");

	copy.Traverse(display); //traverse

	cin.get();
	return 0;
}

int asciihash(string str)
{
	int h = 0;

	for (int i(0); i < str.size(); i++)
		h += str.c_str()[i] * str.c_str()[i];

	return h;
}

int hash2(string str)
{
	int h = 0;

	for (int i(0); i < str.size(); i++)
		h += str.c_str()[i];

	return h;
}

void display(const Book & book)
{
	cout << book.m_title << "   by   " << book.m_author << "     pages: " << book.m_pages << "\n";
} 