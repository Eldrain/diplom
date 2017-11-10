#pragma once
#include <list>
#include <thread>
#include "Task.cpp"

class MultiSearch
{
private:
	std::list<std::thread> threads;
	int bestF;
	int *best;
public:
	MultiSearch(int countThreads);

	void startSearch(Task &task);

	~MultiSearch();
};