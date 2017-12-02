#pragma once
#include "stdafx.h"
#include <list>
#include <mutex>
#include "Task.cpp"

class MultiSearch
{
private:

	struct trData {
		int *var;
		int set;
		Task *task;
		int n;
	};
	std::mutex mutexObj;
	int bestF;
	int *best;
	double time;
public:
	MultiSearch();

	void startSearch(Task &task);

	void search(trData *data);

	double getTime();

	void PrintRes(int n);

	int GetMinF();

	~MultiSearch();
};