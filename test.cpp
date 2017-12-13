#pragma once
#include "stdafx.h"
#include "Schedule.cpp"
#include "stdlib.h"
//#include <vld.h>

using namespace std;
class test {
public:
	test() {
		//srand(time(0));
	}

	void timeTest(int startN, int finishN, int m, int maxTime, int retry) {
		Schedule sch;
		sch.CreateBaseSet();
		double averangeF = 0;

		for (int i = startN; i < finishN + 1; i++) {		
			sch.Generate(i, m, maxTime, retry);
			sch.PrintJobs();
			//cout << endl << endl << i << " JOBS:\nTimes: ";	
			sch.Solve();
		}

		sch.PrintStat();
	}


	//Return count of differents in arrays 
	int compare(int *arr1, int *arr2, int len) {
		int count = 0;

		for (int i = 0; i < len; i++)
			if (arr1[i] != arr2[i])
				count++;
		return count;
	}	

	void printArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << ", ";
	}

	~test() {
	}
};