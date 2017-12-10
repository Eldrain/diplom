#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include <thread>
#include <mutex>
#include <vector>

class MultiSearch : public AMethod {
private:
	struct trData {
		int *var;
		int set;
		Task *task;
		int n;
	};
	std::mutex mutexObj;
	double time;
public:
	void Update() {
	}

	void Start(Task &task)
	{	
		//sort::vector<int> *var = new sort::vector<int>[task.n];
		int **var = new int*[task.n];
		std::vector<std::thread> threads;
		trData *datas = new trData[n];

		mutexObj.lock();
		for (int i = 0; i < n; i++) {
			var[i] = new int[task.n];
			//var[i].resize(n);
			ArrFunctions::clearArr(var[i], n);
			var[i][0] = i + 1;

			trData *data = &datas[i];
			data->var = var[i];
			data->set = 1;
			data->n = n;
			data->task = &task;

			threads.emplace_back(&MultiSearch::Search, this, data);
		}
		mutexObj.unlock();

		for (int i = 0; i < n; i++) {
			threads[i].join();
		}

		for (int i = 0; i < task.n; i++) {
			delete[] var[i];
		}

		delete[] var;
		delete[] datas;
		var = NULL;
	}

	void Search(trData *data) {
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
					Search(data);
					data->set--;
					data->var[data->set] = 0;
				}
			}
		}
		else {
			int f = 0;

			mutexObj.lock();
			f = data->task->procs.crit(data->var, data->task->jobs, data->set);

			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best_[i] = data->var[i];
			}
			mutexObj.unlock();
		}
	}

	void PrintRes() {
		std::cout << "\nMultithreading sort out (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();		
	}

	~MultiSearch(){
	}
};