#pragma once 
/*void createJobStack(jobStack& inputJobs)
{

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
		} //create type C jobs
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

	while (tempJobs.isEmpty() != true) {
		inputJobs.push(tempJobs.pop());
	}

	inputJobs.quickSort(0, inputJobs.getCount() - 1);


}
*/

