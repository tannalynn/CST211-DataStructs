/***************************************************************************************************
* Author:						Tanna McClure
* File:							Source.cpp
* Date Created:					3/8/2015
*
* Overview:
*		Fills a graph with data from a file and then finds the shortest path between two points
* 
* Input:
*		the starting and ending point for the path
*
* Output:
*		displays the path, total miles, and total time.
*	
***************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <list>
using std::list;
#include <vector>
using std::vector;
#include "Graph.h"

struct path
{
	string name; //name of edge
	int prev = -1; //position in array of previous city in shortest path
};

struct city
{
	vector<Edge<string, string>> roads;
	string name;
	path prev;   //the path from the previous city in the shortest path
	int distance = 99999999; //total distance to this point - default is insanely high b/c reasons
	bool processed = false;
};

void ReadFile(string filename, Graph<string, string> & dir);
list<city> Dijkstra(const Graph<string, string> & dir, string start, string endpoint);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graph<string, string> directions;
	list<city> shortest;
	string from, to;
	ReadFile("file.txt", directions);

	cout << "Starting point?: ";
	getline(cin, from);
	cout << "\nEnd point?: ";
	getline(cin, to);

	cout << "\n\n\n";
	try
	{
		if (!directions.IsEmpty())
			shortest = Dijkstra(directions, from, to);
		int miles = 0;
		double time = 0;

		for (city c : shortest) //display the shortest path found by Dijkstra's
		{
			if (c.prev.prev != -1)
				cout << "  take  " << c.prev.name << "\n to ";
			cout << c.name;

			if (c.prev.name == "I-5")
				time += (c.distance - miles) / 65.0;
			else
				time += (c.distance - miles) / 55.0;
			miles += (c.distance - miles);
		}

		cout << "\nTotal miles: " << miles << "     " << "Total time: " << time << "\n\n";
	}
	catch (Exception e)
	{
		cout << e << "\n\n";
	}

	cin.get();
	return 0;
}

/***************************************************************************************************
*	Purpose: reads the graphs data from the file
*
*	Entry: the name of the file and the graph to store the data in
*
*	Exit: returns nothing
***************************************************************************************************/
void ReadFile(string filename, Graph<string, string> & dir)
{
	ifstream in(filename.c_str());

	if (in.is_open())
	{
		while (!in.eof())
		{
			string from, to, hwy;
			int weight;
			
			getline(in, from, ',');
			getline(in, to, ',');
			getline(in, hwy, ',');
			in >> weight;
			in.get(); //remove \n

			try{ dir.InsertVertex(from); }	catch (...) { } //throws exception if it's already in there
			try { dir.InsertVertex(to); }	catch (...) { } //so just trying it
			dir.InsertEdge(from, to, hwy, weight); //inserts the edge
		}
	}
}

/***************************************************************************************************
*	Purpose: Finds the shortest distance between two paths
* 
*	Entry: the graph to do the thing to, the from and the to
* 
*	Exit: the shortest path
***************************************************************************************************/
list<city> Dijkstra(const Graph<string, string> & dir, string start, string endpoint)
{
	vector<city> cities;
	for (Vertex<string, string> & v : dir.GetVertices())
	{
		city temp;
		temp.name = v.GetData();  
		list <Edge<string, string>> edges = v.GetEdges();
		temp.roads = { begin(edges), end(edges) }; //    vector<Edge<string,string>>(begin(...), ....);
		cities.push_back(temp);
	}

	int current = -1;
	for (int i(0); i < cities.size(); i++)
		if (cities[i].name == start)
			current = i;

	if (current == -1)
		throw Exception("Exception: Dijkstra's: Invalid Starting Point");

	cities[current].distance = 0;
	cities[current].processed = true;

	int processed = 1;
	while (processed < cities.size())
	{
		cities[current].processed = true;

		for (Edge<string, string> e : cities[current].roads)
		{
			int destination = -1;
			bool found = false;
			int size = cities.size();
			while (destination < size && !found)
			{
				destination++;
				if (cities[destination].name == e.GetDestination()->GetData())
					found = true;
			}

			int distance = cities[current].distance + e.GetWeight();

			if (!cities[destination].processed)
				if (cities[destination].distance > distance)
				{
					cities[destination].distance = distance;
					cities[destination].prev.name = e.GetEdgeData();
					cities[destination].prev.prev = current;
				}
		}
		
		processed++;

		for (int j(0), d(99999999); j < cities.size(); j++)
			if (!cities[j].processed && cities[j].distance < d)
			{
				current = j;
				d = cities[j].distance;
			}
	}

	current = -1;
	for (int i(0); i < cities.size(); i++)
		if (cities[i].name == endpoint)
			current = i;

	if (current == -1)
		throw Exception("Exception: Dijkstra's: Invalid Ending Point");

	list<city> shortest;
	while (current != -1)
	{
		shortest.push_front(cities[current]);
		current = cities[current].prev.prev;
	}

	return shortest;
}