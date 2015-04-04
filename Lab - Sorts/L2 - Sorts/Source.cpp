/***************************************************************************************************
* Author:						Tanna McClure
* File:							Source.cpp
* Date Created:					1/24/2015
*
* Overview:
*		Program creates integers in arrays and then sorts them using several different sorts
* 
* Input:
*		none
*
* Output:
*		the time each sort takes for each structure it sorts   -   measured in MICROSECONDS
*	
***************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::cin;
#include "Array_1D.h"
#include <iomanip>
#include <time.h>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;
#include <fstream>
using std::ofstream;

void Set(int set[], int size);
void Reset(int size, const int set[], int ar[], Array_1D<int> & m_ar, vector<int> & v_ar);

template <typename T, typename N>
void ForceBubble(T &ar, int length);

template <typename T, typename N>
void FlaggedBubble(T& ar, int length);

template <typename T, typename N>
void SelectionSort(T& ar, int length);

template <typename T, typename N>
void InsertionSort(T &ar, int length);

template <typename T, typename N>
void ShellSort(T &ar, int length);

template <typename T, typename N>
void HeapSort(T& ar, int length);
template <typename T, typename N>
void HeapMoveDown(T & data, int index, int last);

template <typename T, typename N>
void QuickSort(T &ar, int length);
template <typename T, typename N>
void QuickSort(T & ar, int first, int last);

template <typename T, typename N>
void MergeSort(T &ar, int length);
template <typename T, typename N>
void MergeSort(T &ar, N * temp, int left, int right);
template <typename T, typename N>
void Merge(T &ar, N * temp, int left, int mid, int right);

template <typename T, typename N>
void BinaryInsertionSort(T& ar, int length); //extra credit

template <typename T, typename N>
void ShakerSort(T& ar, int length); //extra credit 


int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int size = atoi(argv[1]);
	ofstream fout("results.txt");
	int * original = new int[size],
		* ar       = new int[size];
	Array_1D<int> mar(size);
	vector<int>   var(size);

	Set(original, size);
	Reset(size, original, ar, mar, var);

//**************************************************************************************************
//			Shell Sort
//**************************************************************************************************
	auto start = high_resolution_clock::now();
	ShellSort<int *, int>(ar, size);
	auto end = high_resolution_clock::now();
	auto time = end - start;
	cout << std::left << std::setw(12) << "ShellSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::left << std::setw(12) << "ShellSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	ShellSort<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	ShellSort<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";

	Reset(size, original, ar, mar, var);
//**************************************************************************************************
//			Heap Sort
//**************************************************************************************************
	start = high_resolution_clock::now();
	HeapSort<int *, int>(ar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << std::setw(12) << "HeapSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::setw(12) << "HeapSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	HeapSort<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	HeapSort<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";

	Reset(size, original, ar, mar, var);
//**************************************************************************************************
//			Merge Sort
//**************************************************************************************************
	start = high_resolution_clock::now();
	MergeSort<int *, int>(ar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << std::setw(12) << "MergeSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::setw(12) << "MergeSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	MergeSort<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	MergeSort<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";

	Reset(size, original, ar, mar, var);
//**************************************************************************************************
//			Quick Sort
//**************************************************************************************************
	start = high_resolution_clock::now();
	QuickSort<int *, int>(ar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << std::setw(12) << "QuickSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::setw(12) << "QuickSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	QuickSort<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	QuickSort<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";

	Reset(size, original, ar, mar, var);
//**************************************************************************************************
//			ForceBubble Sort
//**************************************************************************************************
	start = high_resolution_clock::now();
	ForceBubble<int *, int>(ar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << std::setw(12) << "ForceBubble:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::setw(12) << "ForceBubble:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	ForceBubble<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	ForceBubble<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";

	Reset(size, original, ar, mar, var);
//**************************************************************************************************
//			FlaggedBubble Sort
//**************************************************************************************************
	start = high_resolution_clock::now();
	FlaggedBubble<int *, int>(ar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << std::setw(12) << "FlagBubble:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::setw(12) << "FlagBubble:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	FlaggedBubble<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	FlaggedBubble<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";

	Reset(size, original, ar, mar, var);
//**************************************************************************************************
//			Selection Sort
//**************************************************************************************************
	start = high_resolution_clock::now();
	SelectionSort<int *, int>(ar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << std::setw(12) << "Selection:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::setw(12) << "Selection:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	SelectionSort<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";

	start = high_resolution_clock::now();
	SelectionSort<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";

	Reset(size, original, ar, mar, var);
//**************************************************************************************************
//			Insertion Sort
//**************************************************************************************************
	start = high_resolution_clock::now();
	InsertionSort<int *, int>(ar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << std::setw(12) << "Insertion:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::setw(12) << "Insertion:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 << "s ";

	start = high_resolution_clock::now();
	InsertionSort<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 << "s ";

	start = high_resolution_clock::now();
	InsertionSort<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 << "s\n";

	Reset(size, original, ar, mar, var);
//**************************************************************************************************
//			Binary Insertion Sort
//**************************************************************************************************
	start = high_resolution_clock::now();
	BinaryInsertionSort<int *, int>(ar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << std::setw(12) << "BinaryInser:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::setw(12) << "BinaryInser:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 << "s ";

	start = high_resolution_clock::now();
	BinaryInsertionSort<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 << "s ";

	start = high_resolution_clock::now();
	BinaryInsertionSort<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 << "s\n";

	Reset(size, original, ar, mar, var);
//**************************************************************************************************
//			Shaker Sort
//**************************************************************************************************
	start = high_resolution_clock::now();
	ShakerSort<int *, int>(ar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << std::setw(12) << "ShakerSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << std::setw(12) << "ShakerSort:" << "native: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 << "s ";

	start = high_resolution_clock::now();
	ShakerSort<Array_1D<int>, int>(mar, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s ";
	fout << "    Array_1D: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 << "s ";

	start = high_resolution_clock::now();
	ShakerSort<vector<int>, int>(var, size);
	end = high_resolution_clock::now();
	time = end - start;
	cout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 <<"s\n";
	fout << "    vector: "
		<< std::setw(8) << duration_cast<microseconds>(time).count() << (char)230 << "s\n";


//**************************************************************************************************
	fout.close();
	delete[] original;
	delete[] ar;
	
	return 0;
}

/***************************************************************************************************
*	Purpose: sets the values of the default unsorted array
*
*	Entry: the array to set
*
*	Exit: the array is filled with random integers
***************************************************************************************************/
void Set(int set[], int size)
{
	srand((unsigned int)time(0));

	for (int i(0); i < size; i++)
		set[i] = rand();
}

/***************************************************************************************************
*	Purpose: resets all the arrays to the original unsorted values
*
*	Entry: the original array and all the ones to change and the size
*
*	Exit: arrays are all changed
***************************************************************************************************/
void Reset(int size, const int set[], int ar[], Array_1D<int> & m_ar, vector<int> &v_ar)
{
	for (int i(0); i < size; i++)
		ar[i] = m_ar[i] = v_ar[i] = set[i];
}

/***************************************************************************************************
*	Purpose: Forced Bubble sort
*
*	Entry: the array and the length of the array
*
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void ForceBubble(T & ar, int length)
{
	for (int i(0); i < length; i++)
		for (int j(0); j < length - 1; j++)
			if (ar[j] > ar[j + 1])
			{
				N temp = ar[j];
				ar[j] = ar[j + 1];
				ar[j + 1] = temp;
			}
}

/***************************************************************************************************
*	Purpose: flagged bubble sort
*
*	Entry: the array and the length of the array
*
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void FlaggedBubble(T &ar, int length)
{
	bool sorted = false;

	for (int i(0); !sorted && i < length; i++)
	{
		sorted = true;
		for (int j(0); j < length - 1; j++)
		{
			if (ar[j] > ar[j + 1])
			{
				N temp = ar[j];
				ar[j] = ar[j + 1];
				ar[j + 1] = temp;
				sorted = false;
			}
		}
	}
}

/***************************************************************************************************
*	Purpose: Selection Sort - flagged
*
*	Entry: the array and the length of the array
*
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void SelectionSort(T& ar, int length )
{
	bool sorted = false;

	for (int iteration(0); iteration < length - 1 && !sorted; iteration++)
	{
		int max(0), travel(0);
		sorted = true;
		while(travel < length - iteration - 1)
		{
			travel++;
			if (ar[travel] > ar[max])
				max = travel;
			else
				sorted = false;
		}
		if (!sorted)
		{
			N temp = ar[travel];
			ar[travel] = ar[max];
			ar[max] = temp;
		}
	}
}

/***************************************************************************************************
*	Purpose: insertion sort
*
*	Entry: the array and the length of the array
* 
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void InsertionSort(T &ar, int length)
{
	for (int i(0); i < length; i++)
	{
		N temp = ar[i];
		int pos = i;
		for (; pos > 0 && temp < ar[pos - 1]; pos--)
			ar[pos] = ar[pos - 1];
		ar[pos] = temp;
	}
}

/***************************************************************************************************
*	Purpose: Shell sort
*
*	Entry: the array and the length of the array
*
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void ShellSort(T &ar, int length)
{
	vector<int> incr;
	for (int h(1); h < length;)
	{
		incr.push_back(h);
		h = 3 * h + 1;
	}

	for (int i(incr.size() - 1); i >= 0; i--)
	{
		int gap = incr[i];
		for (int gapCount(gap); gapCount < 2 * gap; gapCount++)
		{
			for (int j(gapCount); j < length;)
			{
				N temp = ar[j];
				int k = j;
				while (k - gap >= 0 && temp < ar[k - gap])
				{
					ar[k] = ar[k - gap];
					k = k - gap;
				}
				ar[k] = temp;
				j = j + gap;
			}
		}
	}
}

/***************************************************************************************************
*	Purpose: Heap sort
*
*	Entry: the array and the length of the array
*
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void HeapSort(T &ar, int length)
{
	for (int i(length / 2); i >= 0; i--)
		HeapMoveDown<T,N>(ar, i, length - 1);
	
	for (int i(length - 1); i > 0; i--)
	{
		N temp = ar[0];
		ar[0] = ar[i];
		ar[i] = temp;
		HeapMoveDown<T, N>(ar, 0, i - 1);
	}
}

/***************************************************************************************************
*	Purpose: moves down the values to rearrange it into a heap
*
*	Entry: the array, the index to move down, and the last position
*
*	Exit: the heap has been rearranged
***************************************************************************************************/
template <typename T, typename N>
void HeapMoveDown(T & data, int index, int last)
{
	int largest = index * 2 + 1;

	while (largest <= last)
	{
		if (largest < last && (data[largest] < data[largest+1]))
			largest++;
		if (data[index] < data[largest])
		{
			N temp = data[largest];
			data[largest] = data[index];
			data[index] = temp;
		}
		index = largest;
		largest = index * 2 + 1;
	}
}

/***************************************************************************************************
*	Purpose: Quick sort
*
*	Entry: the array and the length of the array
*
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void QuickSort(T &ar, int length)
{
	if (length >= 2)
	{
		int max = 0;
		for (int i(1); i < length; i++)
			if (ar[max] < ar[i])
				max = i;
		N temp = ar[max];
		ar[max] = ar[length - 1];
		ar[length - 1] = temp;
		QuickSort<T,N>(ar, 0, length - 2);
	}
}

/***************************************************************************************************
*	Purpose: Quick sort
*
*	Entry: the array and the first and last positions for this sort
*
*	Exit: array is sorted
***************************************************************************************************/

template <typename T, typename N>
void QuickSort(T & ar, int first, int last)
{
	int small = first + 1;
	int large = last;
	int pivot = ar[first];
	while (small <= large)
	{
		while (ar[small] < pivot)
			small++;
		while (ar[large] > pivot)
			large--;
		if (small < large)
		{
			N temp = ar[small];
			ar[small] = ar[large];
			ar[large] = temp;
			small++;
			large--;
		}
		else
			small++;
	}
	N temp = ar[large];
	ar[large] = ar[first];
	ar[first] = temp;
	if (first < large - 1)
		QuickSort<T, N>(ar, first, large - 1);
	if (last > large + 1)
		QuickSort<T, N>(ar, large + 1, last);
}

/***************************************************************************************************
*	Purpose: Merge sort
*
*	Entry: the array and the length of the array
*
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void MergeSort(T &ar, int length)
{
	N * temp = new N[length];

	MergeSort(ar, temp, 0, length - 1);

	delete[] temp;
}

/***************************************************************************************************
*	Purpose: Merge sort  4 parameters
*
*	Entry: the array, temp array, left and right indexes
*
*	Exit: Sorted
***************************************************************************************************/
template <typename T, typename N>
void MergeSort(T &ar, N * temp, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		MergeSort(ar, temp, left, mid);
		MergeSort(ar, temp, mid + 1, right);
		Merge(ar, temp, left, mid + 1, right);
	}
}

/***************************************************************************************************
*	Purpose: Merges the arrays
*
*	Entry: merges and sorts
*
*	Exit: merged
***************************************************************************************************/
template <typename T, typename N>
void Merge(T &ar, N * temp, int left, int right, int right_end)
{
	int left_end = right - 1,
		temp_pos = left,
		num_elements = right_end - left + 1,
		left_temp = left,
		right_temp = right;

	while (left_temp <= left_end && right_temp <= right_end)
	{
		if (ar[left_temp] <= ar[right_temp])
		{
			temp[temp_pos] = ar[left_temp];
			left_temp++;
			temp_pos++;
		}
		else
		{
			temp[temp_pos] = ar[right_temp];
			right_temp++;
			temp_pos++;
		}
	}
	for (int i(left_temp); i <= left_end; i++, temp_pos++)
		temp[temp_pos] = ar[i];
	for (int i(right_temp); i <= right_end; i++, temp_pos++)
		temp[temp_pos] = ar[i];

	for (int i(left); i <= right_end; i++)
		ar[i] = temp[i];

}

/***************************************************************************************************
*	Purpose: Binary insertion sort
*
*	Entry: the array and the length of the array
*
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void BinaryInsertionSort(T& ar, int length)
{
	for (int i(0); i < length; i++)
	{
		N temp = ar[i];
		int left = 0;
		int right = i;
		while (left < right) //binary part
		{
			int middle = (left + right) / 2;
			if (temp >= ar[middle])
				left = middle + 1;
			else
				right = middle;
		}
		int pos = i;
		for (; pos > left; pos--)
			ar[pos] = ar[pos - 1];
		ar[pos] = temp;
	}
}

/***************************************************************************************************
*	Purpose: Shaker sort
*
*	Entry: the array and the length of the array
*
*	Exit: array is sorted
***************************************************************************************************/
template <typename T, typename N>
void ShakerSort(T& ar, int length)
{
	for (int i(0); i < length; i++)
	{
		for (int j(i); j < length - i - 1; j++)
			if (ar[j] > ar[j + 1])
			{
				N temp = ar[j];
				ar[j] = ar[j + 1];
				ar[j + 1] = temp;
			}
		
		for (int j(length - i - 2); j > i; j--)
			if (ar[j] < ar[j - 1])
			{
				N temp = ar[j];
				ar[j] = ar[j - 1];
				ar[j - 1] = temp;
			}
	}
}