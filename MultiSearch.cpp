//#include "stdafx.h"
#include "MultiSearch.h"
#include "ArrFunctions.cpp"
#include <thread>
#include <vector>

MultiSearch::MultiSearch()
{
	best = NULL;	
}


void MultiSearch::search(/*int *var, int set, Task &task, int n*/trData *data) {	
	//trData *data = (trData*) datav;
	mutexObj.lock();
	if (!data->task->jobs.checkVar(data->var, data->set))
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

		mutexObj.lock();//pthread_mutex_lock(&mutexObj);
		f = data->task->procs.crit(data->var, data->task->jobs, data->set);

		if (f < bestF) {
			bestF = f;
			ArrFunctions::copyArr(best, data->var, data->n);
		}
		mutexObj.unlock();//pthread_mutex_unlock(&mutexObj);
	}
}

void MultiSearch::startSearch(Task &task) 
{
	bestF = 0;
	delete[] best;
	best = new int[task.n];

	for (int i = 0; i < task.n; i++) {
		bestF += task.jobs.jobs[i].time; // ���������������� �������� �������. �� ����� ���� ���������� ����� ���������� ������.
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

		/*std::thread trd;
		pthread_t newThread;*/
		threads.emplace_back(&MultiSearch::search, this, data);//push_back(newThread);
		//int code = pthread_create(&threads[i], NULL, &MultiSearch::search, this, data);
		// if(code != 0)
		// {
		// 	std::cout << "Create thread error!!!";
		// 	//system.exit(0);
		// }
	}
	mutexObj.unlock();
	for (int i = 0; i < n; i++)
	{
		//pthread_join(threads[i], NULL);
		threads[i].join();
		//std::cout << std::endl << i + 1 << " thread окончил работу.";
		delete[] var[i];
		var[i] = NULL;
	}
	//delete[] tasks;
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
