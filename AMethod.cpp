#pragma once
#include "stdafx.h"
#include "IMethod.cpp"
#include "ArrFunctions.cpp"
#include <ctime>

class AMethod : public IMethod {
protected:
	int n;
	int minF;
	int *var;
	int *best;
	double time;
	int countVar;

	// Statistics
	Stats *stats;
private:
	int methodId;
	std::string methodName;

	void FirstUpd() {
		minF = 0;
		countVar = 0;
		delete[] var;
		var = new int[n];
		best = new int[n];
		ArrFunctions::clearArr(var, n);
	}
public:
	AMethod(int metId, std::string metName) : methodId(metId), methodName(metName), var(NULL), best(NULL), stats(NULL) {}

	virtual Solution* Solve(Task &task) {
		n = task.n;
		FirstUpd();
		Update();
		for (int i = 0; i < n; i++) {
			minF += task.jobs[i];
		}
		minF++;//Best array will filled at least once

		time = clock();
		Start(task, 0);
		time = (clock() - time) / CLOCKS_PER_SEC;

		Solution *sol = new Solution(methodId, methodName, best, task.n, task.m, minF, time, countVar);
		best = NULL;

		if (stats) {
			stats->add(minF, time, countVar);
		}
		return sol;
	}

	virtual void Update() = 0;

	virtual void Start(Task &task, int set) = 0;

	void setStats(Stats *stats) {
		this->stats = stats;
	}

	virtual ~AMethod() {
		delete[] var;
	}
};