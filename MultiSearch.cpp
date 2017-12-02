#pragma once
#include "stdafx.h"
#include "MultiSearch.h"
#include "ArrFunctions.cpp"
#include <thread>
#include <vector>

MultiSearch::MultiSearch()
{
	best = NULL;	
}

void MultiSearch::search(trData *data) {	
	mutexObj.lock();
	if (!data->task->jobs.Check(data->var, data->set))
	{
		mutexObj.unlock();
		return;
	}
	mutexObj.unlock();

	if (data->set < data->n) {
		int j = 0;
		for (int i = 0; i < data->n; i++) {
			j = 0;
			while (data->var[j] != 0)
				if (data->var[j] == i + 1)
					break;
				else
					j++;
			if (j == data->set) {
				data->var[data->set] = i + 1;
				data->set++;
				search(data);
				data->set--;
				data->var[data->set] = 0;
			}
		}
	}
	else {
		int f = 0;	

		mutexObj.lock();
		f = data->task->procs.crit(data->var, data->task->jobs, data->set);

		if (f < bestF) {
			bestF = f;
			ArrFunctions::copyArr(best, data->var, data->n);
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
		bestF += task.jobs[i];
	}
	bestF++;
	time = clock();

	int **var = new int*[task.n];
	int n = task.n;
	std::vector<std::thread> threads;
	//Task *tasks = new Task[task.n];
	trData *datas = new trData[n];

	mutexObj.lock();
	for (int i = 0; i < n; i++) {
		var[i] = new int[n];
		//tasks[i] = task;
		ArrFunctions::clearArr(var[i], n);
		var[i][0] = i + 1;

		trData *data = &datas[i];
		data->var = var[i];
		data->set = 1;
		data->n = n;
		data->task = &task;


		threads.emplace_back(&MultiSearch::search, this, data);
	}
	mutexObj.unlock();
	for (int i = 0; i < n; i++)
	{
		threads[i].join();
		delete[] var[i];
		var[i] = NULL;
	}

	delete[] var;
	delete[] datas;
	var = NULL;

	time = (clock() - time) / CLOCKS_PER_SEC;
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
