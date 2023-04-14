#include "jobStack.h"
#include <iostream>

jobStack::jobStack() {

}

void jobStack::push(job inputJob) {
    jobCount++;
    jobSet[jobCount - 1] = inputJob;
}

job jobStack::pop() {
    job tempJob = jobSet[jobCount - 1];
    jobSet[jobCount - 1] = { ' ',0, 0,0,0 };
    jobCount--;
    return tempJob;
}

bool jobStack::isEmpty() {
    return jobCount == 0;
}

bool jobStack::isFull() {
    return jobCount == 5000;
}

void jobStack::print() {
    for (int arr_i = jobCount - 1; arr_i >= 0; arr_i--) {
        std::cout << "Type " << jobSet[arr_i].jobType
            << "Arrival Time " << jobSet[arr_i].arrivalTime
            << "Job Number " << jobSet[arr_i].jobNumber
            << "Type Number " << jobSet[arr_i].typeNumber
            << "Processing Time " << jobSet[arr_i].processingTime << std::endl;
    }
}

int jobStack::peekArrivalTime() {
    return jobSet[jobCount - 1].arrivalTime;
}

void jobStack::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void jobStack::swap(job* a, job* b) {
    job t = *a;
    *a = *b;
    *b = t;
}

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

jobStack::~jobStack() {

}