#include "stdafx.h"
#include "MultiSearch.h"
#include "ArrFunctions.cpp"
#include <vector>

MultiSearch::MultiSearch()
{
	best = NULL;	
}

void MultiSearch::search(int *var, int set, Task &task, int n) {	
	if (!task.jobs.checkVar(var, set))
	{
		return;
	}

	if (set < n) {
		int j = 0;
		for (int i = 0; i < n; i++) {
			j = 0;
			while (var[j] != 0)
				if (var[j] == i + 1)
					break;
				else
					j++;
			if (j == set) {
				var[set] = i + 1;
				search(var, set + 1, task, n);
				var[set] = 0;
			}
		}
	}
	else {
		int f = 0;	
		f = task.procs.crit(var, task.jobs, set);

		mutexObj.lock();
		if (f < bestF) {
			bestF = f;
			ArrFunctions::copyArr(best, var, n);
		}
		mutexObj.unlock();
	}
}

void MultiSearch::startSearch(Task &task) 
{
	bestF = 0;
	delete[] best;
	best = new int[task.n];

	for (int i = 0; i < task.n; i++) {
		bestF += task.jobs.jobs[i].time; // переопределенный оператор индекса. На самом деле возвращает время выполнения работы.
	}
	bestF++;
	time = clock();
	int **var = new int*[task.n];
	int n = task.n;
	//boost::thread_group g;
	std::vector<std::thread> threads;
	Task *tasks = new Task[task.n];

	for (int i = 0; i < n; i++) {
		var[i] = new int[n];
		tasks[i] = task;
		ArrFunctions::clearArr(var[i], n);
		//std::thread tr(&MultiSearch::search, this, var[i], 0, std::ref(task), task.n);
		threads.emplace_back(&MultiSearch::search, this, var[i], 0, std::ref(tasks[i]), n);
		//thrd[i] = std::thread(&MultiSearch::search, this, var[i], 0, std::ref(task), n);
	}

	for (int i = 0; i < n; i++)
	{
		threads[i].join();
		delete[] var[i];
		var[i] = NULL;
	}
	delete[] tasks;
	delete[] var;
	var = NULL;

	time = (clock() - time) / 1000;
}

double MultiSearch::getTime() {
	return time;
}

void MultiSearch::PrintRes(int n) {
	ArrFunctions::printArr(best, n);
}

int MultiSearch::GetMinF() {
	return bestF;
}

MultiSearch::~MultiSearch()
{
	delete[] best;
}
