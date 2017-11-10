#pragma once
#include "stdafx.h"
#include "Task.cpp"
#include "ArrFunctions.cpp"
#include <ctime>


class AMethod {
protected:
	int *var, *best, n, m, minF;

	virtual void update() {
		delete[] var;
		delete[] best;
		var = new int[n];
		best = new int[n];
	}

public:
	virtual int solve(Task &task) = 0;

	void printRes() {
		std::cout << std::endl << "Best resulst: ";
		ArrFunctions::printArr(best, n);
	}

	virtual ~AMethod() {
		delete[] var;
		delete[] best;
	}
};