/***************************************************************************************************
* Author:						Tanna McClure
* File:							HashTable.h
* Date Created:					3/10/2015
*
* Modification Date: 			3/12/2015
* Modification: 				finished
*		  
*	Class: HashTable
*
*	Purpose: 
*		holds data
*
*	Manager Functions: 
*		HashTable(int(*hash)(K key), int size = 10);
*			2 arg Constructor
*		HashTable(const HashTable<T> & copy);
*			Copy Constructor
*		~HashTable();
*			Destructor
*		HashTable<T> & operator = (const HashTable<T> & rhs);
*			Assignment operator
*
*	Methods: 
*		void Insert(K key, T data);
*			Insert an element to the table
*		void SetHash(int(*hash)(K key));
*			takes a new hash function to use
*		void SetSize(int size);
*			sets the size of the vector
*		void Delete(K key);
*			removes an element from the table
*		void Traverse(void(*visit)(const T & data));
*			traverses the table
*		T & operator[] (K key);
*			[] operator
*
***************************************************************************************************/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <list>
using std::list;
using std::pair;

template <typename K, typename T>
class HashTable
{
public:
			//2 arg Constructor
	HashTable(int(*hash)(K key), int size = 10);
			//Copy Constructor
	HashTable(const HashTable<K, T> & copy);
			//Destructor
	~HashTable();
			//Assignment Operator
	HashTable<K, T> & operator = (const HashTable<K, T> & rhs);

			//Insert an element to the table
	void Insert(K key, T data);
			//takes a new hash function to use
	void SetHash(int(*hash)(K key));
			//sets the size of the vector
	void SetSize(int size);
			//removes an element from the table
	void Delete(K key);
			//traverses the table
	void Traverse(void(*visit)(const T & data));
			//[] operator
	T & operator[] (K key);


private:
	vector<list<pair<K, T>>> m_table;
	int(*m_hash)(K key);

			//remakes the table
	void Rehash(vector<list<pair<K, T>>> temp);
};
/***************************************************************************************************
*									Function Definitions
***************************************************************************************************/
/***************************************************************************************************
*	Purpose: 2 arg Constructor
*
*	Entry: none
*
*	Exit: object created
***************************************************************************************************/
template <typename K, typename T>
HashTable<K, T>::HashTable(int(*hash)(K key), int size): m_hash(hash)
{ 
	m_table.resize(size);
}
/***************************************************************************************************
*	Purpose: Copy Constructor
*
*	Entry: the object to copy
*
*	Exit: object created
***************************************************************************************************/
template <typename K, typename T>
HashTable<K, T>::HashTable(const HashTable<K, T> & copy): m_table(copy.m_table), m_hash(copy.m_hash)
{ }
/***************************************************************************************************
*	Purpose: Destructor
*
*	Entry: none
*
*	Exit: object destroyed
***************************************************************************************************/
template <typename K, typename T>
HashTable<K, T>::~HashTable()
{ 
	m_hash = nullptr;
}
/***************************************************************************************************
*	Purpose: Assignment Operator
*
*	Entry: the object to copy
*
*	Exit: object copied
***************************************************************************************************/
template <typename K, typename T>
HashTable<K, T> & HashTable<K, T>::operator = (const HashTable<K, T> & rhs)
{
	if(this != &rhs)
	{
		m_hash = rhs.m_hash;
		m_table = rhs.m_table;
	}
	return *this;
}
/***************************************************************************************************
*	Purpose: inserts an element to the table
*
*	Entry: the key and the data
*
*	Exit: element inserted
***************************************************************************************************/
template <typename K, typename T>
void HashTable<K, T>::Insert(K key, T data)
{
	int pos = m_hash(key) % m_table.size();
	m_table[pos].emplace_back(key, data);
}
/***************************************************************************************************
*	Purpose: resets the hash function and remakes the table
*
*	Entry: the new hash function pointer
*
*	Exit: table remade
***************************************************************************************************/
template <typename K, typename T>
void HashTable<K, T>::SetHash(int(*hash)(K key))
{
	if (m_hash != hash)
	{
		m_hash = hash;
		vector<list<pair<K, T>>> temp = m_table;
		m_table.clear();
		m_table.resize(temp.size());
		Rehash(temp);
	}
}
/***************************************************************************************************
*	Purpose: changes the size of the table
*
*	Entry: the new size
*
*	Exit: table is resized
***************************************************************************************************/
template <typename K, typename T>
void HashTable<K, T>::SetSize(int size)
{
	if (size != m_table.size())
	{
		vector<list<pair<K, T>>> temp = m_table;
		m_table.clear();
		m_table.resize(size);
		Rehash(temp);
	}
}
/***************************************************************************************************
*	Purpose: removes an element from the table using the key
*
*	Entry: the key of the item to remove
*
*	Exit: element has been deleted from table
***************************************************************************************************/
template <typename K, typename T>
void HashTable<K, T>::Delete(K key)
{
	int pos = m_hash(key) % m_table.size(); //find position
	list<pair<K, T>>::iterator iter = m_table[pos].begin();
	bool found = false;

	while (iter != m_table[pos].end() && !found)
	{
		if (iter->first == key)
		{
			iter = m_table[pos].erase(iter);
			found = true;
		}
		else
			++iter;
	}
}
/***************************************************************************************************
*	Purpose: reconstructs the table
*
*	Entry: none
*
*	Exit: table remade
***************************************************************************************************/
template <typename K, typename T>
void HashTable<K, T>::Rehash(vector<list<pair<K, T>>> temp)
{
	for (list<pair<K, T>> lst : temp)
		for (pair<K, T> pr : lst)
			m_table[m_hash(pr.first) % m_table.size()].emplace_back(pr);
}
/***************************************************************************************************
*	Purpose: traverses the table
*
*	Entry: the visit function
*
*	Exit: each element in table has been visited
***************************************************************************************************/
template <typename K, typename T>
void HashTable<K, T>::Traverse(void(*visit)(const T & data))
{
	for (list<pair<K, T>> & lst : m_table)
		for (pair<K, T> & pr : lst)
			visit(pr.second);
}
/***************************************************************************************************
*	Purpose: returns a reference to an element in the table
*
*	Entry: the key of the element
*
*	Exit: returns the element requested
***************************************************************************************************/
template <typename K, typename T>
T & HashTable<K, T>::operator[](K key)
{
	int pos = m_hash(key) % m_table.size();
	T * ret = nullptr;
	for (pair<K, T> & pr : m_table[pos])
		if (key == pr.first)
			ret = &pr.second;
	return *ret;
}
#endif