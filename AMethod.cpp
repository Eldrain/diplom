#pragma once
#include "stdafx.h"
#include "Task.cpp"
#include <ctime>

class AMethod {
protected:
	int *var, *best, n, m, minF;

	void printArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << ", ";
	}

	void clearArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			arr[i] = 0;
	}

	virtual void update() {
		delete[] var;
		delete[] best;
		var = new int[n];
		best = new int[n];
	}

public:
	virtual int solve(Task &task) = 0;

	void printRes() {
		std::cout << std::endl << "Best sort out: ";
		printArr(best, n);
	}

	~AMethod() {
		delete[] var;
		delete[] best;
	}
};