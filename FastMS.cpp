#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include <thread>
#include <vector>

class FastMS : public AMethod {
private:
	struct trData {
		int *var;
		int set;
		Task *task;
		int n;
	};
	double time;
public:
	void Update() {
	}

	void Start(Task &task, int set)
	{
		Task *task_arr = new Task[task.n];
		int **var = new int*[task.n];
		std::vector<std::thread> threads;
		trData *datas = new trData[n];

		
		for (int i = 0; i < n; i++) {
			var[i] = new int[task.n];
			task_arr[i].CloneFrom(task);
			//var[i].resize(n);
			ArrFunctions::clearArr(var[i], n);
			var[i][0] = i + 1;

			trData *data = &datas[i];
			data->var = var[i];
			data->set = 1;
			data->n = n;
			data->task = &task_arr[i];

			threads.emplace_back(&FastMS::Search, this, data);
		}

		for (int i = 0; i < n; i++) {
			threads[i].join();
		}

		for (int i = 0; i < task.n; i++) {
			delete[] var[i];
		}

		delete[] var;
		delete[] datas;
		delete[] task_arr;
	}

	void Search(trData *data) {
		if (!data->task->jobs.Check(data->var, data->set))
		{
			return;
		}

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

			//f = data->task->crit(data->var, data->set);
			f = data->task->procs.crit(data->var, data->task->jobs, data->set);

			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best_[i] = data->var[i];
			}
		}
	}

	void GetRes(std::ostringstream &res) {
		res << "\nFast MS sort out (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
	}

	/*void PrintRes() {
		std::cout << "\nFast MS sort out (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}*/

	~FastMS(){
	}
};