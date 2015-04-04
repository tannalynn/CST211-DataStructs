/***************************************************************************************************
* Author:						Tanna McClure
* File:							Edge.h
* Date Created:					3/2/2015
*
* Modification Date: 			3/3/2015
* Modification: 				Commenting
*		  
***************************************************************************************************/
/***************************************************************************************************
*	Class: Edge
*
*	Purpose: 
*		Contains the data for an edge connecting two vertices
*
*	Manager Functions: 
*		Edge();
*			Default Constructor
*		Edge(Vertex<V, E> * origin, Vertex<V, E> * dest, const E & edge, int weight):
*			4 arg constructor
*		Edge(const Edge<V, E> & copy);
*			Copy Constructor
*		~Edge();
*			Destructor
*		Edge<T> & operator = (const Edge<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		bool operator == (const Edge<V, E>& copy) const;
*			comparison operator
*
***************************************************************************************************/
#ifndef EDGE_H
#define EDGE_H

template <typename V, typename E>
class Vertex;

template  <typename V, typename E>
class Edge
{
	template <typename V, typename E>
	friend class Graph;
public:
			//Default Constructor
	Edge();
			// 4 arg ctor
	Edge(Vertex<V, E> * origin, Vertex<V, E> * dest, const E & edge, int weight);
			//Copy Constructor
	Edge(const Edge<V, E> & copy);
			//Destructor
	~Edge();
			//Assignment Operator
	Edge<V, E> & operator = (const Edge<V, E> & rhs);
			//comparison operator
	bool operator == (const Edge<V, E>& copy) const;

private:
	E m_edge_data;
	int m_weight;
	Vertex<V, E> * m_destination;
	Vertex<V, E> * m_origin;
};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: default constructor
*
*	Entry: the pointer to the destination - default to nullptr
*
*	Exit: object created
***************************************************************************************************/
template  <typename V, typename E>
Edge<V, E>::Edge(): m_weight(0), m_destination(nullptr), m_origin(nullptr)
{ }
/***************************************************************************************************
*	Purpose: 4 arg constructor
*
*	Entry: the edge data, pointer to destination and origin and weight
*
*	Exit: object created
***************************************************************************************************/
template  <typename V, typename E>
Edge<V, E>::Edge(Vertex<V, E> * origin, Vertex<V, E> * dest, const E & edge, int weight):
m_weight(weight), m_destination(dest), m_edge_data(edge), m_origin(origin)
{ }
/***************************************************************************************************
*	Purpose: Copy Constructor
*
*	Entry: the object to copy
*
*	Exit: object created
***************************************************************************************************/
template  <typename V, typename E>
Edge<V, E>::Edge(const Edge<V, E> & copy):m_weight(copy.m_weight), m_destination(copy.m_destination),
										  m_edge_data(copy.m_edge_data)
{ }
/***************************************************************************************************
*	Purpose: Destructor
*
*	Entry: none
*
*	Exit: object destroyed
***************************************************************************************************/
template  <typename V, typename E>
Edge<V, E>::~Edge()
{
	m_weight = 0;
	m_destination = nullptr;
}
/***************************************************************************************************
*	Purpose: Assignment Operator
*
*	Entry: the object to copy
*
*	Exit: object copied
***************************************************************************************************/
template  <typename V, typename E>
Edge<V, E> & Edge<V, E>::operator=(const Edge<V, E> & rhs)
{
	if (this != &rhs)
	{
		m_destination = rhs.m_destination;
		m_edge_data = rhs.m_edge_data;
		m_weight = rhs.m_weight;
		m_origin = rhs.m_origin;
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: Comparison operator
*
*	Entry: the edge to compare
*
*	Exit: true if they are the same
***************************************************************************************************/
template  <typename V, typename E>
bool Edge<V, E>::operator==(const Edge<V, E>& copy) const
{
	bool same = false;

	if (m_origin == copy.m_origin && m_destination == copy.m_destination &&
		m_edge_data == copy.m_edge_data && m_weight == copy.m_weight)
		same = true;

	return same;
}
#endif