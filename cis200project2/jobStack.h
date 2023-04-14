#pragma once
#include <iostream>
struct job {
	char jobType;
	int processingTime;
	int typeNumber;
	int jobNumber;
	int arrivalTime;
	int waitTime = 0;
};


class jobStack
{
private:
	job jobSet[5000];
	int jobCount = 0;
public:
	jobStack();
	void push(job inputJob);
	job pop();
	bool isEmpty();
	bool isFull();
	void print();
	int peekArrivalTime();
	void quickSort(int low, int high);
	void swap(job* a, job* b);
	int partition(int low, int high);
	int getCount() { return jobCount; }
	~jobStack();
};