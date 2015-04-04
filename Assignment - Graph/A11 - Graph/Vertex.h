/***************************************************************************************************
* Author:						Tanna McClure
* File:							Vertex.h
* Date Created:					3/2/2☺15
*
* Modification Date: 			3/2/2☺15
* Modification: 				wrote functions
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Vertex
*
*	Purpose: 
*		Contains the data and edges for that point on the graph
*
*	Manager Functions: 
*		Vertex();
*			Default Constructor
*		Vertex(const Vertex<T> & copy);
*			Copy Constructor
*		~Vertex();
*			Destructor
*		Vertex<T> & operator = (const Vertex<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		bool operator == (const Vertex<V, E> & copy) const; 
*			comparison operator - compares data only
*
***************************************************************************************************/
#ifndef VERTEX_H
#define VERTEX_H
#include "Edge.h"
#include <list>
using std::list;

template <typename V, typename E>
class Vertex
{
	template <typename V, typename E>
	friend class Graph;
public:
			//Default Constructor
	Vertex();
			//1 arg constructor
	Vertex(const V & data);
			//Copy Constructor
	Vertex(const Vertex<V, E> & copy);
			//Destructor
	~Vertex();
			//Assignment Operator
	Vertex<V, E> & operator = (const Vertex<V, E> & rhs);
			//comparison operator - compares data only
	bool operator == (const Vertex<V, E> & copy) const; 

private:
	V m_data;
	bool m_processed;
	list<Edge<V, E>> m_edges;
};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: Default Constructor
*
*	Entry: none
*
*	Exit: object created
***************************************************************************************************/
template <typename V, typename E>
Vertex<V, E>::Vertex(): m_processed(false)
{ }
/***************************************************************************************************
*	Purpose: 1 arg constructor
*
*	Entry: the data to put in the vertex
* 
*	Exit: object created
***************************************************************************************************/
template <typename V, typename E>
Vertex<V, E>::Vertex(const V & data):m_data(data), m_processed(false)
{ }
/***************************************************************************************************
*	Purpose: Copy Constructor
*
*	Entry: the object to copy
*
*	Exit: object created
***************************************************************************************************/
template <typename V, typename E>
Vertex<V, E>::Vertex(const Vertex<V, E> & copy):m_data(copy.m_data), m_processed(copy.m_processed),
												m_edges(copy.m_edges)
{ }
/***************************************************************************************************
*	Purpose: Destructor
*
*	Entry: none
*
*	Exit: object destroyed
***************************************************************************************************/
template <typename V, typename E>
Vertex<V, E>::~Vertex()
{
	m_processed = false;
}
/***************************************************************************************************
*	Purpose: Assignment Operator
*
*	Entry: the object to copy
*
*	Exit: object copied
***************************************************************************************************/
template <typename V, typename E>
Vertex<V, E> & Vertex<V, E>::operator=(const Vertex<V, E> & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_processed = false;
		//m_processed = rhs.m_processed;
		//m_edges = rhs.m_edges;
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: comparison operator - needed for list class
*
*	Entry: the vertex to compare to
*
*	Exit: true if the data in the vertices are the same
***************************************************************************************************/
template <typename V, typename E>
bool Vertex<V, E>::operator==(const Vertex<V, E> & copy) const
{
	return (m_data == copy.m_data);
}
#endif