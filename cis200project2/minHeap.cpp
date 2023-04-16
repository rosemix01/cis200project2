#include "minHeap.h"


// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	heaparray = new job[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(job k)
{
	if (heap_size == capacity)
	{
		std::cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	heaparray[i] = k;

	// Fix the min heap property if it is violated
	while (i != 0 && (heaparray[parent(i)].processingTime > heaparray[i].processingTime || heaparray[i].jobType == 'D'))
	{
		swap(&heaparray[i], &heaparray[parent(i)]);
		i = parent(i);
	}

	//fixes problem where root isn't swapped out
	if (i == 0) {
		if (heap_size > 1 && (heaparray[1].processingTime < heaparray[0].processingTime || heaparray[1].jobType == 'D')) {
			swap(&heaparray[1], &heaparray[0]);
		}
		if (heap_size > 2 && (heaparray[2].processingTime < heaparray[0].processingTime || heaparray[2].jobType == 'D')) {
			swap(&heaparray[2], &heaparray[0]);
		}
	}
}

//Returns true if there are no objects in the heap
bool MinHeap::isEmpty()
{
	if (heap_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

// A utility function to swap two elements
void MinHeap::swap(job* x, job* y)
{
	job temp = *x;
	*x = *y;
	*y = temp;

}

//Prints out the objects in the Heap, starting at the root
void MinHeap::print()
{
	for (int arr_i = 0; arr_i < heap_size; arr_i++) {
		std::cout << "Type " << heaparray[arr_i].jobType << " "
			<< "Arrival Time " << heaparray[arr_i].arrivalTime << " "
			<< "Job Number " << heaparray[arr_i].jobNumber << " "
			<< "Type Number " << heaparray[arr_i].typeNumber << " "
			<< "Processing Time " << heaparray[arr_i].processingTime << std::endl;
	}
}

//Increases the wait time in all job objects in the queue
void MinHeap::addWaitTime()
{
	if (heap_size > 0) {
		for (int arr_i = 0; arr_i < heap_size; arr_i++) {
			heaparray[arr_i].waitTime++;
		}
	}

}

//Returns the sum of the wait times of all job objects

int MinHeap::getRemainingWaitTime()
{
	int totalWait = 0;
	if (heap_size > 0) {
		for (int arr_i = 0; arr_i < heap_size; arr_i++) {
			totalWait = totalWait + heaparray[arr_i].waitTime;
		}
	}
	return totalWait;
}

// Method to remove minimum element (or root) from min heap
job MinHeap::extractMin()
{
	if (heap_size <= 0) {
		return { ' ',0,0,0,0 };
	}

	if (heap_size == 1)
	{
		heap_size--;
		return heaparray[0];
	}

	// Store the minimum value, and remove it from heap
	job root = heaparray[0];
	heaparray[0] = heaparray[heap_size - 1];
	heap_size--;
	MinHeapify(0);

	return root;
}

// A recursive method to heapify a subtree with root at given index
void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && heaparray[l].processingTime < heaparray[i].processingTime)
		smallest = l;
	if (r < heap_size && heaparray[r].processingTime < heaparray[smallest].processingTime)
		smallest = r;
	if (smallest != i)
	{
		swap(&heaparray[i], &heaparray[smallest]);
		MinHeapify(smallest);
	}
}