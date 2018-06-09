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
		MarkFactory markFactory;

		set.addSortOut(true);
		//set.addAbBound(markFactory.createBestMin(), markFactory.createBestMax(), true);
		set.addAbBound(markFactory.createMinPath(), markFactory.createSecondMax(), true);
		set.addBaB(markFactory.createMinPath(), markFactory.createSecondMax(), true);
		set.addFrontAlg(true);
		set.addMtBab(true);
		task.ResizeProcs(m);

		for (int i = startN; i < finishN + 1; i++) {
			std::cout << "*********************** " << i << " Jobs ***********************";
			gen.GenerateTree(task, i, maxTime, retry);
			set.solve(callback, task);
			std::cout << std::endl << std::endl;
		}

		set.printStats();
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

	void testHook() {
		int n = 8, m = 3;
		Hook hook;
		Task task;
		task.ResizeProcs(m);
		gen.GenerateTree(task, 8, 30, 6);
		task.jobs.Print();
		int *var = new int[n];
		ArrFunctions::clearArr(var, n);
		for (int i = 0; i < 3; i++) {
			int num = 0;
			for (; num < n; num++) {
				if (task.jobs.FindInFront(num + 1)) {
					break;
				}
			}
			task.jobs.Complete(num + 1);
			var[i] = num + 1;
			task.jobs.Print();
		}
		std::cout << "\nBefore hooking: ";
		ArrFunctions::printArr(var, n);
		int count = 0;
		hook.update(n);
		hook.calculateHooks(task.jobs, var + 3, count);
		std::cout << "\nAfter hooking: ";
		ArrFunctions::printArr(var, n);
		std::cout << "\nJobsCount: " << count;
	}

	~test() {
	}
};