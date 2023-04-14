#include "minHeap.h" 

MinHeap::MinHeap(int cap)

{

	heap_size = 0;

	capacity = cap;

	heaparray = new job[cap];

} 

void MinHeap::insertKey(job k)
{

	if (heap_size == capacity)
	{
		std::cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	heap_size++;

	int i = heap_size - 1;

	heaparray[i] = k;


	while (i != 0 && (heaparray[parent(i)].processingTime > heaparray[i].processingTime || heaparray[i].jobType == 'D'))

		swap(&heaparray[i], &heaparray[parent(i)]);

	i = parent(i);



	if (i == 0) {


		if ((heap_size > 1 && (((heaparray[1].processingTime) < (heaparray[0].processingTime)) || (heaparray[1].jobType == 'D')))) {

			swap(&heaparray[1], &heaparray[0]);

		}

		if (heap_size > 2 && (heaparray[2].processingTime < heaparray[0].processingTime || heaparray[2].jobType == 'D')) {

			swap(&heaparray[2], &heaparray[0]);

		}

	}
}

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


void MinHeap::print()

{

	for (int arr_i = 0; arr_i < heap_size; arr_i++) {

		std::cout << "Type " << heaparray[arr_i].jobType

			<< "Arrival Time " << heaparray[arr_i].arrivalTime

			<< "Job Number " << heaparray[arr_i].jobNumber

			<< "Type Number " << heaparray[arr_i].typeNumber

			<< "Processing Time " << heaparray[arr_i].processingTime << std::endl;

	}

}


void MinHeap::addWaitTime()

{

	if (heap_size > 0) {

		for (int arr_i = 0; arr_i < heap_size; arr_i++) {

			heaparray[arr_i].waitTime++;

		}

	}



}