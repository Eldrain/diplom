#include "stdafx.h"
#include "MultiSearch.h"
#include "ArrFunctions.cpp"


MultiSearch::MultiSearch()
{
	best = NULL;	
}

void MultiSearch::startSearch(Task &task) 
{
	bestF = 0;
	for (int i = 0; i < task.n; i++)
		bestF += task.jobs.jobs[i].time; // переопределенный оператор индекса. На самом деле возвращает время выполнения работы.

	time = clock();
	int **var = new int*[task.n];
	for (int i = 0; i < task.n; i++) {
		var[i] = new int[task.n];
		ArrFunctions::clearArr(var[i], task.n);
		threads.push_front(*new std::thread(&search, var[i], 0, task, task.n));
	}

	for (int i = 0; i < task.n; i++)
	{
		//threads.;
	}

	time = (clock() - time) / 1000;
}

void MultiSearch::search(int *var, int set, Task &task, int n) {
	mutexObj.lock();
	if (!task.jobs.checkVar(var, set)) 
	{
		return;
	}
	mutexObj.unlock();

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

		mutexObj.lock();
		f = task.procs.crit(var, task.jobs, set);

		if (f < bestF) {
			bestF = f;
			ArrFunctions::copyArr(best, var, n);
		}
		mutexObj.unlock();
	}
}

double MultiSearch::getTime() {
	return time;
}

MultiSearch::~MultiSearch()
{
	delete[] best;
}
