#include "jobStack.h"
#include "minHeap.h"
#include <random>
#include "Processor.h"
#include <fstream>
#include <iostream>

using namespace std;

void createJobStack(jobStack& inputJobs);

int main()
{
	jobStack inputJobs;
	MinHeap jobHeap(5000);
	ofstream logFile;
	logFile.open("log.txt");
	float heapAvg = 0;
	int maxQueue = 0;
	long int idleCount = 0;
	int jobsCompleted = 0;
	int aCount = 0, bCount = 0, cCount = 0, dCount = 0;
	int activeCycle = 0, totalProcessingTime = 0;
	int jobsInterrupted = 0;
	int totalWaitTime = 0;
	float averageWaitTime = 0;
	int userCPU;

	createJobStack(inputJobs);


	// Print a welcome message to the console
	cout << "Welcome to the Test Processor Program!" << endl;

	// Loop until the user enters a valid input
	do {

		cout << "How many processors would you like to use in this test?" << endl;
		cin >> userCPU;

		// If the user entered an invalid input, print an error message
		if (userCPU < 0) {
			cout << "Invalid Input" << endl;
		}
	} while (userCPU < 1);

	// Create an array of Processor objects based on the user input
	Processor* CPU = new Processor[userCPU];


	for (int time = 0; time < 10000; time++) {

		// If the current time is greater than or equal to 500, log time and job information
		if (time >= 500) {
			logFile << time << ") ";
		}

		// Check if any of the processors have completed a job
		for (int i_cpu = 0; i_cpu < userCPU; i_cpu++) {
			if (CPU[i_cpu].isComplete() && CPU[i_cpu].isFull()) {
				// If a job has completed, pop it from the processor and log the completed job information
				job tempJob;
				tempJob = CPU[i_cpu].pop();

				if (time >= 500) {
					logFile << "Job " << tempJob.jobType << " " << tempJob.typeNumber << " Completed; ";
					jobsCompleted++;
				}
			}
		}

		// Add arriving jobs to the job heap and log job information if time is greater than or equal to 500
		while (inputJobs.peekArrivalTime() == time) {
			job tempJob = inputJobs.pop();

			jobHeap.insertKey(tempJob);

			if (time >= 500) {
				logFile << "Arrival Job " << tempJob.jobType << ": Overall Job " << tempJob.jobNumber
					<< ", Job " << tempJob.jobType << " " << tempJob.typeNumber
					<< ", Processing Time " << tempJob.processingTime << "; ";

				// Count job types
				switch (tempJob.jobType)
				{
				case 'A':
					aCount++;
					break;
				case 'B':
					bCount++;
					break;
				case 'C':
					cCount++;
					break;
				case 'D':
					dCount++;
					break;
				}
			}
		}


		// interrupt for type D jobs
			// iterate through each CPU to check if they are empty or if there are jobs in the heap
		for (int i_cpu = 0; i_cpu < userCPU; i_cpu++) {
			// if the CPU is empty or the heap is empty, continue to the next iteration
			if (CPU[i_cpu].isEmpty() || jobHeap.size() == 0) {
				continue;
			}

			// get the minimum job from the heap
			job temp = jobHeap.getMin();

			// if the job is of type D, swap it with the lowest priority job in the CPU and add the displaced job to the heap
			if (temp.jobType == 'D') {
				job displacedJob;
				job Djob;
				displacedJob = CPU[i_cpu].pop();
				Djob = jobHeap.extractMin();
				CPU[i_cpu].push(Djob);
				jobHeap.insertKey(displacedJob);

				if (time >= 500) {
					jobsInterrupted++;
					// output to log file
					logFile << "Interrupt Job " << displacedJob.jobType << " " << displacedJob.typeNumber
						<< ", Total Interrupted Jobs: " << jobsInterrupted << ", New high priority job goes into Processor " << i_cpu + 1
						<< ", Job " << displacedJob.jobType << " " << displacedJob.typeNumber
						<< "Added to heap with processing time " << displacedJob.processingTime << ";";
				}
			}
			// if the job is not of type D, break out of the loop
			else {
				break;
			}



		}

		// Add to CPU
		// iterate through each CPU and assign jobs from the heap if the CPU is empty
		for (int i_cpu = 0; i_cpu < userCPU; i_cpu++) {
			// if the heap is empty, break out of the loop
			if (jobHeap.isEmpty()) {
				if (time >= 500) {
					logFile << "Heap Empty; ";
				}
				break;
			}
			// if the CPU is empty, assign the minimum job from the heap to the CPU
			else if (CPU[i_cpu].isEmpty()) {
				job tempJob = jobHeap.extractMin();
				totalWaitTime = totalWaitTime + tempJob.waitTime;
				tempJob.waitTime = 0; //reset in case it is displaced in interrupt
				CPU[i_cpu].push(tempJob);

				if (time >= 500) {
					logFile << "Begin Processing Job " << tempJob.jobType << " " << tempJob.typeNumber
						<< " in CPU " << i_cpu + 1 << " , end time " << time + tempJob.processingTime << "; ";
				}
			}
		}

		// Process the jobs in each CPU
		bool activeJob = false;

		for (int i_cpu = 0; i_cpu < userCPU; i_cpu++) {
			// Check if CPU is idle
			if (CPU[i_cpu].isEmpty()) {
				if (time >= 500) {
					logFile << "CPU " << i_cpu + 1 << ": Idle Time ";
					idleCount++;
				}
			}
			// If CPU is not idle, process the job
			else {
				job tempJob = CPU[i_cpu].peekJob();
				CPU[i_cpu].processJobOne();
				activeJob = true;
				if (time >= 500) {
					logFile << "CPU " << i_cpu + 1 << ": Job " << tempJob.jobType << " " << tempJob.jobNumber << "; ";
					totalProcessingTime++;
				}
			}
		}

		// Increase wait time for jobs in heap
		jobHeap.addWaitTime();

		// Update active cycle count and heap statistics
		if (activeJob == true && time >= 500)
			activeCycle++;

		if (time >= 500) {
			heapAvg = heapAvg + (jobHeap.size() - heapAvg) / time;
			if (jobHeap.size() > maxQueue)
				maxQueue = jobHeap.size();

			logFile << endl;
		}

	}

	//inputJobs.print();

	//jobHeap.print();

	//final report
	int totalJobsArrived = aCount + bCount + cCount + dCount;
	totalWaitTime = totalWaitTime + jobHeap.getRemainingWaitTime();
	averageWaitTime = totalWaitTime / totalJobsArrived;
	//output to log.txt
	logFile << endl << "Performance Metrics - Calculated from cycle 500 on" << endl;
	logFile << "Final Queue Size: " << jobHeap.size() << endl;
	logFile << "Average queue size: " << heapAvg << endl;
	logFile << "Average time in queue: " << averageWaitTime << " time units" << endl;
	logFile << "Idle time: " << idleCount << " time units." << endl;
	logFile << "Total Jobs Arrived: " << totalJobsArrived << endl;
	logFile << "Total number of jobs A arrived: " << aCount << endl;
	logFile << "Total number of jobs B arrived: " << bCount << endl;
	logFile << "Total number of jobs C arrived: " << cCount << endl;
	logFile << "Total number of jobs D arrived: " << dCount << endl;
	logFile << "Total wait time in queue: " << totalWaitTime << " time units." << endl;
	logFile << "Maximum jobs in queue: " << maxQueue << endl;
	logFile << "Jobs interrupted " << jobsInterrupted << endl;
	logFile << "Total jobs completed: " << jobsCompleted << endl;
	logFile << "Number of processor(s) used: " << userCPU << endl;
	logFile << "Total number of time units the processors(s) run: " << activeCycle << endl;
	logFile << "Total time processor(s) spent processing is: " << totalProcessingTime << " time units" << endl;

	//output to console
	cout << endl << "Performance Metrics - Calculated from cycle 500 on" << endl;
	cout << "Final Queue Size: " << jobHeap.size() << endl;
	cout << "Average queue size: " << heapAvg << endl;
	cout << "Average time in queue: " << averageWaitTime << " time units" << endl;
	cout << "Idle time: " << idleCount << " time units." << endl;
	cout << "Total Jobs Arrived: " << totalJobsArrived << endl;
	cout << "Total number of jobs A arrived: " << aCount << endl;
	cout << "Total number of jobs B arrived: " << bCount << endl;
	cout << "Total number of jobs C arrived: " << cCount << endl;
	cout << "Total number of jobs D arrived: " << dCount << endl;
	cout << "Total wait time in queue: " << totalWaitTime << " time units." << endl;
	cout << "Maximum jobs in queue: " << maxQueue << endl;
	cout << "Jobs interrupted " << jobsInterrupted << endl;
	cout << "Total jobs completed: " << jobsCompleted << endl;
	cout << "Number of processor(s) used: " << userCPU << endl;
	cout << "Total number of time units the processors(s) run: " << activeCycle << endl;
	cout << "Total time processor(s) spent processing is: " << totalProcessingTime << " time units" << endl;
	logFile.close();
	logFile.close();
	//jobHeap.print();

	cout << "Report information is in the file log.txt" << endl;
	cout << "Thank you, have a nice day!" << endl;

	system("pause");
	return 0;
}

//Description: Creates the job stack
//Precondition : a jobStack object
//Postcondition : returns the job stack
void createJobStack(jobStack& inputJobs)
{
	ofstream myfile;
	myfile.open("job_data.txt");
	jobStack tempJobs;
	int jobCount = 0;

	job tempA = { 'A', 0,0,0,0, 0 };
	job tempB = { 'B', 0,0,0,0, 0 };
	job tempC = { 'C', 0,0,0,0, 0 };
	job tempD = { 'D', 0,0,0,0, 0 };

	for (int time = 0; time < 10000; time++) {

		//create A Type jobs
		if (time % 5 == 0) {
			tempA.arrivalTime = time + 4 + rand() % 3;
			if (tempA.arrivalTime < 10000) {
				jobCount++;
				tempA.jobNumber = jobCount;
				tempA.processingTime = 1 + rand() % 5;
				tempA.typeNumber++;
				tempJobs.push(tempA);
			}
		}

		//create type B jobs
		if (time % 10 == 0) {
			tempB.arrivalTime = time + 9 + rand() % 3;
			if (tempB.arrivalTime < 10000) {
				jobCount++;
				tempB.jobNumber = jobCount;
				tempB.processingTime = 6 + rand() % 5;
				tempB.typeNumber++;
				tempJobs.push(tempB);
			}
		}

		//create type C jobs
		if (time % 25 == 0) {
			tempC.arrivalTime = time + 24 + rand() % 3;
			if (tempC.arrivalTime < 10000) {
				jobCount++;
				tempC.jobNumber = jobCount;
				tempC.processingTime = 11 + rand() % 5;
				tempC.typeNumber++;
				tempJobs.push(tempC);
			}
		}

		//create type D jobs
		if (time % 30 == 0) {
			tempD.arrivalTime = time + 24 + rand() % 11;
			if (tempD.arrivalTime < 10000) {
				jobCount++;
				tempD.jobNumber = jobCount;
				tempD.processingTime = 8 + rand() % 5;
				tempD.typeNumber++;
				tempJobs.push(tempD);
			}
		}

	}
	//outputs the job data in reverse (start at the bottom of the text file and go up)
	//The job data being used is in the correct order, just the text file is in reverse
	while (tempJobs.isEmpty() != true) {
		job temp = tempJobs.pop();
		inputJobs.push(temp);
		myfile << temp.jobNumber << " " << temp.arrivalTime << " " << temp.processingTime << "\n";
	}

	inputJobs.quickSort(0, inputJobs.getCount() - 1);

}