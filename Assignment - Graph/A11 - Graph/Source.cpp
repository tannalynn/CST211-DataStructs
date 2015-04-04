/***************************************************************************************************
* Author:						Tanna McClure
* File:							Source.cpp
* Date Created:					3/3/2015
*
* Overview:
*		Tests the graph class 
* 
* Input:
*		none
*
* Output:
*		result of test
*	
***************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
using std::cout;
using std::cin;
using std::string;

#include "Graph.h"

void Print(const string & str);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<string, string> graph;

	graph.InsertVertex("A"); //insert vertex
	graph.InsertVertex("B");
	graph.InsertVertex("C");
	graph.InsertVertex("D");
	graph.InsertVertex("E");
	graph.InsertVertex("F");

	graph.InsertEdge("A", "B", "A to B", 0); //insert edge
	graph.InsertEdge("A", "C", "A to C", 0);
	graph.InsertEdge("B", "C", "B to C", 0);
	graph.InsertEdge("B", "D", "B to D", 0);
	graph.InsertEdge("D", "F", "D to F", 0);
	graph.InsertEdge("F", "E", "E to F", 0);
	
	graph.DeleteEdge("D", "F", "D to F", 0); //delete edge

	graph.InsertEdge("D", "E", "D to E", 0);
	graph.InsertEdge("C", "D", "C to D", 0);
	graph.InsertEdge("A", "D", "A to D", 0);

	Graph<string, string> graph2(graph), graph3; //copy constructor

	if (graph3.IsEmpty()) // is empty
		cout << "Empty graph is empty\n\n";

	graph.DeleteVertex("B"); //delete vertex
	graph.DeleteVertex("B"); //ok to delete something that's not there

	graph3 = graph; //assignment operator

	graph3.DepthFirst(Print); //depth first traversal
	cout << "\n\n\n";
	graph3.BreadthFirst(Print); //breadth first traversal

	cin.get();
	return 0;
}

void Print(const string & str)
{
	cout << "\n" << str.c_str();
}