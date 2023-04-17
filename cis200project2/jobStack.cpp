#include "jobStack.h"
#include <iostream>

// This is the default constructor for the job stack class
jobStack::jobStack() {

}

// This function adds a job to the top of the stack
void jobStack::push(job inputJob) {
    jobCount++;  // increment the number of jobs in the stack
    jobSet[jobCount - 1] = inputJob;  // add the input job to the top of the stack
}

// This function removes and returns the job at the top of the stack
job jobStack::pop() {
    job tempJob = jobSet[jobCount - 1];  
    jobSet[jobCount - 1] = { ' ',0, 0,0,0 };  
    jobCount--;  
    return tempJob;  
}

// This function checks if the stack is empty
bool jobStack::isEmpty() {
    return jobCount == 0;  // return true if the stack has no jobs
}

// This function checks if the stack is full
bool jobStack::isFull() {
    return jobCount == 5000;  // return true if the stack has 5000 jobs
}

// This function prints all the jobs in the stack in reverse order
void jobStack::print() {
    for (int arr_i = jobCount - 1; arr_i >= 0; arr_i--) {
        std::cout << "Type " << jobSet[arr_i].jobType
            << "Arrival Time " << jobSet[arr_i].arrivalTime
            << "Job Number " << jobSet[arr_i].jobNumber
            << "Type Number " << jobSet[arr_i].typeNumber
            << "Processing Time " << jobSet[arr_i].processingTime << std::endl;
    }
}

// This function returns the arrival time of the job at the top of the stack
int jobStack::peekArrivalTime() {
    return jobSet[jobCount - 1].arrivalTime;
}

// This function sorts the jobs in the stack by their arrival time using the quicksort algorithm
void jobStack::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

// This function swaps two jobs
void jobStack::swap(job* a, job* b) {
    job t = *a;
    *a = *b;
    *b = t;
}

// This function partitions the stack for quicksort
int jobStack::partition(int low, int high) {
    job pivot = jobSet[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (jobSet[j].arrivalTime >= pivot.arrivalTime) {
            i++;
            swap(&jobSet[i], &jobSet[j]);
        }
    }
    swap(&jobSet[i + 1], &jobSet[high]);
    return (i + 1);
}

// This is the destructor for the job stack class
jobStack::~jobStack() {

}
