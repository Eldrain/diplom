#pragma once
#include "stdafx.h"
#include "Generator.cpp"
#include "MethodSet.cpp"
#include "stdlib.h"
//#include <vld.h>

class test {
private:
	Generator gen;
public:
	test() {
		//srand(time(0));
	}

	void timeTest(int startN, int finishN, int m, int maxTime, int retry, void callback(Solution*) ) {
		Task task;
		MethodSet set;

		//set.addSortOut();
		//set.addAbBound();
		//set.addBaB();
		set.addFrontAlg();
		set.addMtBab();
		task.ResizeProcs(m);

		for (int i = startN; i < finishN + 1; i++) {
			std::cout << "======================== " << i << " Jobs ========================";
			gen.GenerateTree(task, i, maxTime, retry);
			set.solve(callback, task);
			std::cout << std::endl << std::endl;
		}
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