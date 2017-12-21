#pragma once
#include "stdafx.h"
#include "BBreal.cpp"
#include "FrontAlg.cpp"
#include "threadpool.cpp"
#include <vector>
#include <mutex>
#include "transport.cpp"
#include "MarkFactory.cpp"

//template <class T>
class MTBB : public AMethod {
private:
	struct data {
		std::mutex max_mutex;
		int maximum;
		int *var;
		int set;
		Task *task;
		Marks *marks;
	};

	eld::threadpool threadpool_;
	std::mutex stack_mutex_;
	int thread_count_;
	ObjectStack<data> stack;	
public:
	MTBB(int thread_count = 10) : threadpool_(thread_count), thread_count_(thread_count){}

	void Update() {
		stack.clear();
	}

	void Start(Task &task, int set)
	{	
		for (int i = 0; i < thread_count_; i++) {
			data *elem = new data();

			elem->maximum = UINT32_MAX;
			elem->marks = MarkFactory::CreateBestMarks();
			elem->task = new Task();
			elem->task->CloneFrom(task);
			elem->set = 0;
			elem->var = new int[task.n];
			ArrFunctions::clearArr(elem->var, task.n);

			stack.push(elem);
		}

		search(stack.pop()->info);

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

	void search(data *data) {
		if (!data->task->jobs.Check(data->var, data->set)) {
			std::unique_lock<std::mutex> locker(stack_mutex_);
			stack.push(data);
		}

		//countVar++;
		if (data->set < data->task->n) {
			int j = 0;
			for (int i = 0; i < n; i++) {
				j = 0;
				while (data->var[j] != 0)
					if (data->var[j] == i + 1)
						break;
					else
						j++;
				if (j == data->set) {
					data->var[data->set] = i + 1;
					if (!data->task->jobs.Check(data->var, data->set + 1)) {
						data->var[data->set] = 0;
						continue;
					}

					int mx = data->marks->maxB(data->var, data->set + 1, *data->task);
					int mn = data->marks->minB(data->var, data->set + 1, *data->task);

					{
						std::unique_lock<std::mutex> locker(data->max_mutex);
						if (mx < data->maximum)
							data->maximum = mx;
					}
					if (mn == mx) {
						if (mn < minF) {
							minF = mn;
							for (int i = 0; i < n; i++)
								best_[i] = var_[i];
						}
					}
					else {
						std::unique_lock<std::mutex> locker(data->max_mutex);
						if (mn <= data->maximum) {
							std::unique_lock<std::mutex> locker(stack_mutex_);
							ObjectStack<MTBB::data>::elem *elem = stack.pop();
							
							if (elem != nullptr) {
								MTBB::data *new_data = elem->info;
								elem->info = nullptr;
								delete elem;

								ArrFunctions::copyArr(new_data->var, data->var, data->task->n);
								new_data->set = data->set + 1;
								//~~~~~~~~~~~~~~~~~~~~~FINISH HERE~~~~~~~~~~~~~~~~~~~~~~
							}
							else {

							}
							 = stack.pop();
						}
					}

					var_[set] = 0;
				}
			}
		}
		else {
			int f = 0;
			f = task.procs.crit(var_, task.jobs, set);

			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best_[i] = var_[i];
			}
		}
		return minF;
	}

	void Prepare(Task &task) {
		FrontAlg front;
		front.Solve(task);
		minF = front.GetMin();
		ArrFunctions::copyArr(best_, front.GetBest(), n);
	}

	void GetRes(std::ostringstream &res) {
		res << "\nMTBB (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
	}

	/*void PrintRes() {
		std::cout << "\nMTBB (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}*/

	~MTBB() {
	}
};