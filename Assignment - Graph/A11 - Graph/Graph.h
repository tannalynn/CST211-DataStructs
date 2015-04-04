/***************************************************************************************************
* Author:						Tanna McClure
* File:							Graph.h
* Date Created:					3/2/2015
*
* Modification Date: 			3/3/2015
* Modification: 				finished commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Graph
*
*	Purpose: 
*		Graph Class
*
*	Manager Functions: 
*		Graph();
*			Default Constructor
*		Graph(const Graph<T> & copy);
*			Copy Constructor
*		~Graph();
*			Destructor
*		Graph<T> & operator = (const Graph<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		void InsertVertex(const V & data);
*			Inserts a vertex into the graph containing the data passed in
*		void DeleteVertex(const V & data);
*			Deletes a vertex containing the data passed in from the list
*		void InsertEdge(const V & from_data, const V & to_data, const E & edge, int weight);
*			Inserts an edge between two vertices
*		void DeleteEdge(const V & from, const V & to, E edge, int weight);
*			Deletes an edge between two vertices
*		void DepthFirst(void(*visit)(const V & data));
*			Traverses the graph depth first
*		void BreadthFirst(void(*visit)(const V & data));
*			Traverses the graph breadth first
*		bool IsEmpty() const;
*			Checks if the list is empty
*
***************************************************************************************************/
#ifndef GRAPH_H
#define GRAPH_H
#include "Vertex.h"
#include "Exception.h"
#include <list>
using std::list;
#include <queue>
using std::queue;
#include <stack>
using std::stack;

template <typename V, typename E>
class Graph
{
public:
			//Default Constructor
	Graph();
			//Copy Constructor
	Graph(const Graph<V, E> & copy);
			//Destructor
	~Graph();
			//Assignment Operator
	Graph<V, E> & operator = (const Graph<V, E> & rhs);

			//Inserts a vertex into the graph containing the data passed in
	void InsertVertex(const V & data);
			//Deletes a vertex containing the data passed in from the list
	void DeleteVertex(const V & data);
			//Inserts an edge between two vertices
	void InsertEdge(const V & from_data, const V & to_data, const E & edge, int weight);
			//Deletes an edge between two vertices
	void DeleteEdge(const V & from, const V & to, const E & edge, int weight);
			//Traverses the graph depth first
	void DepthFirst(void(*visit)(const V & data));
			//Traverses the graph breadth first
	void BreadthFirst(void(*visit)(const V & data));
			//Checks if the list is empty
	bool IsEmpty() const;

private:
	list<Vertex<V, E>> m_vertices;
	int m_count; 
};
/***************************************************************************************************
*									Function Definitions										
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: none
*
*	Exit: object created
***************************************************************************************************/
template <typename V, typename E>
Graph<V, E>::Graph():m_count(0), m_vertices()
{ }
/***************************************************************************************************
*	Purpose: copy constructor
*
*	Entry: the object to copy
*
*	Exit: object created
***************************************************************************************************/
template <typename V, typename E>
Graph<V, E>::Graph(const Graph<V, E> & copy):m_count(copy.m_count), m_vertices(copy.m_vertices)
{ }
/***************************************************************************************************
*	Purpose: destructor
*
*	Entry: none
*
*	Exit: object destroyed
***************************************************************************************************/
template <typename V, typename E>
Graph<V, E>::~Graph()
{
	m_count = 0;
}
/***************************************************************************************************
*	Purpose: assignment operator
*
*	Entry: the object to copy
*
*	Exit: this is now the same as rhs
***************************************************************************************************/
template <typename V, typename E>
Graph<V, E> & Graph<V, E>::operator=(const Graph<V, E> & rhs)
{
	if (this != &rhs)
	{
		m_count = rhs.m_count;
		m_vertices.clear();
		for (Vertex<V, E> ver : rhs.m_vertices)
			m_vertices.emplace_back(ver.m_data);

		for (Vertex<V, E> ver : rhs.m_vertices)
			for (Edge<V, E> edge : ver.m_edges)
				InsertEdge(ver.m_data, edge.m_destination->m_data, edge.m_edge_data, edge.m_weight);
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: inserts a new vertex into the graph
*
*	Entry: the data to insert into the graph
*
*	Exit: new vertex in graph
***************************************************************************************************/
template <typename V, typename E>
void Graph<V, E>::InsertVertex(const V & data)
{
	for each(Vertex<V, E> var in m_vertices)
		if (var.m_data == data)
			throw Exception("Exception:   Graph - InsertVertex:   Already in graph");

	m_vertices.emplace_back(data);
	m_count++;
}
/***************************************************************************************************
*	Purpose: deletes a vertex from the graph
*
*	Entry: the data of the vertex to delete
*
*	Exit: data removed from graph it was there, otherwise nothing happens
***************************************************************************************************/
template <typename V, typename E>
void Graph<V, E>::DeleteVertex(const V & data)
{
	list<Edge<V, E>> edges;

	//delete all edges that go to the vertex being deleted
	for (Vertex<V, E> & vertex : m_vertices)
		for (Edge<V, E> & edge : vertex.m_edges)
			if (edge.m_destination->m_data == data)
				edges.emplace_back(&vertex, edge.m_destination, edge.m_edge_data, edge.m_weight);

	for (Edge<V, E> & edge : edges)
		DeleteEdge(edge.m_origin->m_data, edge.m_destination->m_data, edge.m_edge_data, edge.m_weight);

	m_vertices.remove(data);
	m_count = m_vertices.size();
}
/***************************************************************************************************
*	Purpose: Inserts a Bidirectional edge
*
*	Entry: the two ends of the edge, the edge data, and the weight
*
*	Exit: edge added to both the origin and destination
***************************************************************************************************/
template <typename V, typename E>
void Graph<V, E>::InsertEdge(const V & from_data, const V & to_data, const E & edge, int weight)
{
	Vertex<V, E> * from = nullptr, * to = nullptr;
	bool exists = false;

	for (Vertex<V, E> & fver : m_vertices)
		if (fver.m_data == from_data)
		{
			for (Edge<V, E> & e : fver.m_edges)
				if (e.m_destination->m_data == to_data  && e.m_edge_data == edge)
					exists = true;

			if (!exists)
				for (Vertex<V, E> & tver : m_vertices)
					if (tver.m_data == to_data)
					{
						fver.m_edges.emplace_back(&fver, &tver, edge, weight);
						from = &fver;
						tver.m_edges.emplace_back(&tver, &fver, edge, weight);
						to = &tver;
					}
		}

	if (!exists && (!from || !to))
		throw Exception("Exception: Graph - InsertEdge:  something doesn't exist");
}
/***************************************************************************************************
*	Purpose: Deletes an edge between two vertices
*
*	Entry: the data in both ends, the edge data, and the weight
*
*	Exit: edge removed
***************************************************************************************************/
template <typename V, typename E>
void Graph<V, E>::DeleteEdge(const V & from_data, const V & to_data, const E & edge, int weight)
{
	Vertex<V, E> * from = nullptr, *to = nullptr;

	for (Vertex<V, E> & vertex : m_vertices)
	{
		if (vertex.m_data == from_data)
			from = &vertex;
		if (vertex.m_data == to_data)
			to = &vertex;
	}

	if (!from || !to) //one of them doesn't exist
		throw Exception("Exception:   Graph  -  DeleteEdge:  One or both don't exist");

	from->m_edges.remove(Edge<V, E>(from, to, edge, weight));
	to->m_edges.remove(Edge<V, E>(from, to, edge, weight));
}
/***************************************************************************************************
*	Purpose: Depth first traversal
*
*	Entry: the function to call for each element
*
*	Exit: traversed
***************************************************************************************************/
template <typename V, typename E>
void Graph<V, E>::DepthFirst(void(*visit)(const V & data))
{
	stack<Vertex<V, E> *> depth;
	depth.push(&m_vertices.front()); //starting vertex
	depth.top()->m_processed = true;

	while (!depth.empty())
	{
		Vertex<V, E> * top = depth.top();
		visit(top->m_data);
		depth.pop(); //remove element

		for(Edge<V, E> e : top->m_edges)
			if (!e.m_destination->m_processed)
			{
				depth.push(e.m_destination);
				e.m_destination->m_processed = true;
			}
	}

	//set processed back to false for all
	for (Vertex<V, E> & ver : m_vertices)
		ver.m_processed = false;
}
/***************************************************************************************************
*	Purpose: Breadth first traversal
*
*	Entry: the function to call for each element 
*
*	Exit: traversed
***************************************************************************************************/
template <typename V, typename E>
void Graph<V, E>::BreadthFirst(void(*visit)(const V & data))
{
	queue<Vertex<V, E> *> breadth;
	breadth.push(&m_vertices.front()); //starting vertex
	breadth.front()->m_processed = true;

	while (!breadth.empty())
	{
		visit(breadth.front()->m_data);

		for(Edge<V,E> e : breadth.front()->m_edges)
			if (!e.m_destination->m_processed)
			{
				breadth.push(e.m_destination);
				e.m_destination->m_processed = true;
			}

		breadth.pop(); //remove element
	}

	//set processed back to false for all
	for (Vertex<V, E> & ver : m_vertices)
		ver.m_processed = false;
}
/***************************************************************************************************
*	Purpose: checks if the graph is empty
*
*	Entry: none
*
*	Exit: returns true if there is nothing in the list
***************************************************************************************************/
template <typename V, typename E>
bool Graph<V, E>::IsEmpty() const
{
	return (m_count == 0);
}
#endif