#pragma once
#include <iostream>
#include "jobStack.h"

// A class for Min Heap
class MinHeap
{
	job* heaparray;
	int capacity;
	int heap_size;
public:
	// Constructor
	MinHeap(int capacity);

	// to heapify a subtree with root at given index
	void MinHeapify(int);

	// to get index of parent of node at index i
	int parent(int i) { return (i - 1) / 2; }

	// to get index of left child of node at index i
	int left(int i) { return (2 * i + 1); }

	// to get index of right child of node at index i
	int right(int i) { return (2 * i + 2); }

	// to extract the root which is the minimum element
	job extractMin();

	// Returns the minimum key (key at root) from min heap
	job getMin() { return heaparray[0]; }

	// Inserts a new key 'k'
	void insertKey(job k);

	bool isEmpty();

	void swap(job* x, job* y);

	void print();

	int size() { return heap_size; }

	void addWaitTime();

	int getRemainingWaitTime();
};
