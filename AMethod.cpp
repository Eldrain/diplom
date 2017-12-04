#pragma once
#include "stdafx.h"
#include "Task.cpp"
#include "ArrFunctions.cpp"
#include <ctime>

class AMethod {
protected:
	int n, minF, countVar;
	std::vector<int> var_, best_;
	double time_;
	
private:
	void FirstUpd() {
		minF = 0;
		countVar = 0;
		var_.resize(n);
		best_.resize(n);	
		ArrFunctions::clearArr(var_);
	}

public:

	int Solve(Task &task) {
		n = task.n;
		FirstUpd();
		Update();
		for (int i = 0; i < n; i++)
			minF += task.jobs[i];
		minF++;//Best array will filled at least once

		time_ = clock();
		Start(task);
		time_ = (clock() - time_) / CLOCKS_PER_SEC;

		return minF;
	}

	virtual void Update() = 0;

	virtual void Start(Task &task) = 0;

	virtual void PrintRes() = 0;

	void PrintBest() {
		std::cout << std::endl << "Best result: ";
		ArrFunctions::printArr(best_);
	}	

	double GetTime() {
		return time_;
	}

	int getCountVar() {
		return countVar;
	}

	virtual ~AMethod() {
	}
};