#pragma once
#include "stdafx.h"
#include "Task.cpp"
#include "ArrFunctions.cpp"
#include <ctime>

class AMethod {
protected:
	int *var, *best, n, m, minF, countVar;
	double time;
	
	void copyArr(int *arr1, int *arr2, int n) {
		for (int i = 0; i < n; i++)
			arr1[i] = arr2[i];
	}

	void printArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << ", ";
	}

	void clearArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			arr[i] = 0;
	}

	virtual void update() {
		countVar = 0;
		delete[] var;
		delete[] best;
		var = new int[n];
		best = new int[n];
	}
public:
	virtual int solve(Task &task) = 0;

	void printRes() {
		std::cout << std::endl << "Best result: ";
		ArrFunctions::printArr(best, n);
	}

	double getTime() {
		return time;
	}

	int getCountVar() {
		return countVar;
	}

	virtual ~AMethod() {
		delete[] var;
		delete[] best;
	}
};