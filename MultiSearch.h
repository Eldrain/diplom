#pragma once
#include <list>
#include <thread>
#include <mutex>
#include "Task.cpp"

class MultiSearch
{
private:
	std::list<std::thread> threads;
	std::mutex mutexObj;
	int bestF;
	int *best;
	double time;
public:
	MultiSearch();

	void startSearch(Task &task);

	void search(int *var, int set, Task &task, int n);

	double getTime();

	~MultiSearch();
};