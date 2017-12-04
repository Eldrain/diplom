#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include <thread>
#include <mutex>

class MultiSearch : public AMethod {
private:
	struct trData {
		std::vector<int> var;
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
		std::vector<int> *var = new std::vector<int>[task.n];
		std::vector<std::thread> threads;
		trData *datas = new trData[n];

		mutexObj.lock();
		for (int i = 0; i < n; i++) {
			var[i].resize(n);
			ArrFunctions::clearArr(var[i]);
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
				best_ = data->var;
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