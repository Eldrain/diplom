#pragma once
//#include "stdafx.h"
//#include "AMethod.cpp"
#include "BB.cpp"
#include <thread>
#include <vector>
#include <mutex>
#include "transport.cpp"

template <class T1, class T2>
class NextMT : public AMethod {
private:
	std::mutex mut;
	const int maxThreads;
	int cur_threads_;
	double time;

public:
	NextMT(int max_threads_count = 25) : maxThreads(max_threads_count) {
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

			threads.emplace_back(&NextMT::Search, this, data);
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
		T1 b(MarkFactory::create<T2>());
		b.MTPrepare(data);

		/*int maximum = b.GetMin();
		int set = data->set;
		int f = b.clip(set, maximum, *data->task);

		set = b.countSet(best_);

		if (set < n) {
			b.marks->maxB(best_, set, *data->task);
			ArrFunctions::copyArr(best_, b.marks->GetBuf(), n);
		}*/
		b.Start(*data->task, data->set);
		int f = b.GetMin();

		countVar += b.getCountVar();
		mut.lock();
		if (f < minF) {
			minF = f;
			for (int i = 0; i < n; i++)
				best_[i] = b.GetBest()[i];
		}
		mut.unlock();
	}

	void GetRes(std::ostringstream &res) {
		res << "\nNextMT aB (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
	}

	/*void PrintRes() {
		std::cout << "\nNextMT aB (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}*/

	~NextMT() {
	}
};