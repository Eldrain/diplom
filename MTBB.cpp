#pragma once
#include "stdafx.h"
//#include "AMethod.cpp"
#include "BBreal.cpp"
#include "FrontAlg.cpp"
#include <thread>
#include <vector>
#include <mutex>
#include "transport.cpp"

//template <class T>
class MTBB : public AMethod {
private:
	std::mutex mut;
	const int maxThreads;
	int cur_threads_;
	double time;

public:
	MTBB(int max_threads_count = 25) : maxThreads(max_threads_count) {
		cur_threads_ = 0;
	}

	void Update() {
	}

	void Start(Task &task, int set)
	{
		Task *task_arr = new Task[task.n];
		int **var = new int*[task.n];
		std::vector<std::thread> threads;
		transport *dt = new transport[n];

		FrontAlg front;
		front.Solve(task);
		minF = front.GetMin();
		ArrFunctions::copyArr(best_, front.GetBest(), n);

		for (int i = 0; i < n; i++) {
			var[i] = new int[task.n];
			task_arr[i].CloneFrom(task);
			//var[i].resize(n);
			ArrFunctions::clearArr(var[i], n);
			var[i][0] = i + 1;

			transport *data = &dt[i];
			data->var = var[i];
			data->set = 1;
			data->n = n;
			data->task = &task_arr[i];

			threads.emplace_back(&MTBB::Search, this, data);
		}

		for (int i = 0; i < n; i++) {
			threads[i].join();
		}

		for (int i = 0; i < task.n; i++) {
			delete[] var[i];
		}

		delete[] var;
		delete[] dt;
		delete[] task_arr;
	}

	void Search(transport *data) {
		BBreal b;
		b.MTPrepare(data);

		int set = data->set;
		int maximum = minF;
		b.tree.addInWave(data->var, maximum, maximum, 0);
		b.tree.addWave();

		int f = b.clip(set, maximum, *data->task);

		//Impossible solution
		if (f == 0)
			return;
		set = b.countSet(b.GetBest());

		if (set < n) {
			b.marks->maxB(b.GetBest(), set, *data->task);
			ArrFunctions::copyArr(b.GetBest(), b.marks->GetBuf(), n);
		}
		/*b.Start(*data->task, data->set);
		int f = b.GetMin();*/

		countVar += b.getCountVar();
		mut.lock();
		if (f < minF) {
			minF = f;
			int *buffer = b.GetBest();
			for (int i = 0; i < n; i++)
				best_[i] = buffer[i];
		}
		mut.unlock();
	}

	void PrintRes() {
		std::cout << "\nMTBB (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}

	~MTBB() {
	}
};