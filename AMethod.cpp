#pragma once
//#include "stdafx.h"
#include "IMethod.cpp"
#include "ArrFunctions.cpp"
#include "transport.cpp"
#include <ctime>

class AMethod : public IMethod {
protected:
	int n, minF, countVar;
	//vector<int> var_, best_;
	int *var_, *best_;
	double time_;

	void PrintBest() {
		std::cout << std::endl << "Best result: ";
		ArrFunctions::printArr(best_, n);
	}

private:
	void FirstUpd() {
		minF = 0;
		countVar = 0;

		/*var_.resize(n);
		best_.resize(n);*/
		delete[] var_;
		delete[] best_;
		var_ = new int[n];
		best_ = new int[n];
		ArrFunctions::clearArr(var_, n);
	}
public:
	AMethod() {
		var_ = NULL;
		best_ = NULL;
	}

	virtual int Solve(Task &task) {
		n = task.n;
		FirstUpd();
		Update();
		for (int i = 0; i < n; i++)
			minF += task.jobs[i];
		minF++;//Best array will filled at least once

		time_ = clock();
		Start(task, 0);
		time_ = (clock() - time_) / CLOCKS_PER_SEC;

		return minF;
	}

	virtual void Update() = 0;

	virtual void Start(Task &task, int set) = 0;

	virtual void PrintRes() {
		std::ostringstream tmp;
		GetRes(tmp);
		std::cout << tmp.str();
		PrintBest();
	}

	virtual void GetRes(std::ostringstream &res) = 0;

	virtual void GetAddInfo(std::ostringstream &info) {
		info << "AMethod: No info.";
	}

	double GetTime() {
		return time_;
	}

	int getCountVar() {
		return countVar;
	}

	void MTPrepare(transport *data) {
		n = data->task->n;
		FirstUpd();
		Update();
		for (int i = 0; i < n; i++)
			minF += data->task->jobs[i];
		minF++;//Best array will filled at least once

		ArrFunctions::copyArr(var_, data->var, n);
	}

	int GetMin() {
		return minF;
	}

	int* GetBest() {
		return best_;
	}

	virtual ~AMethod() {
		delete[] var_;
		delete[] best_;
	}
};