#pragma once
#include "stdafx.h"
#include <list>
#include "Task.cpp"
#include <mutex>

class MultiSearch
{
private:
	struct trData {
		int *var;
		int set;
		Task *task;
		int n;
	};
	//std::list<std::thread> threads;
	std::mutex mutexObj;
	int bestF;
	int *best;
	double time;
public:
	MultiSearch();

	void startSearch(Task &task);

	void search(/*int *var, int set, Task &task, int n*/trData *data);

	double getTime();

	void PrintRes(int n);

	int GetMinF();

	~MultiSearch();
};