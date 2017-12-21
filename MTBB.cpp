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
		//std::mutex max_mutex;
		int maximum;
		int *var;
		int set;
		Task *task;
		Marks *marks;
		~data() {
			delete marks;
			delete task;
			delete[] var;
		}
	};

	eld::threadpool threadpool_;
	std::mutex stack_mutex_;
	std::mutex min_mutex;
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
			
			elem->maximum = INT32_MAX;
			elem->marks = MarkFactory::CreateBestMarks();
			elem->marks->init(task.n);
			elem->task = new Task();
			elem->task->CloneFrom(task);
			elem->set = 0;
			elem->var = new int[task.n];
			ArrFunctions::clearArr(elem->var, task.n);

			stack.push(elem);
		}
		ObjectStack<data>::elem *elem = stack.pop();
		data *data = elem->info;
		elem->info = nullptr;
		delete elem;
		threadpool_.async_task(&MTBB::search, this, data, false);
		threadpool_.join();
	}

	void search(data *data, bool save_data) {
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
						//std::unique_lock<std::mutex> locker(data->max_mutex);
						if (mx < data->maximum)
							data->maximum = mx;
					}
					if (mn == mx) {
						std::unique_lock<std::mutex> locker(min_mutex);

						if (mn < minF) {
							minF = mn;
							for (int i = 0; i < n; i++)
								best_[i] = data->var[i];
						}

						/*std::unique_lock<std::mutex> locker1(stack_mutex_);
						stack.push(data);*/
					}
					else {		
						if (mn <= data->maximum) {
							ObjectStack<MTBB::data>::elem *elem = nullptr;
							
							std::unique_lock<std::mutex> locker(stack_mutex_);
							elem = stack.pop();
							locker.unlock();
							
							if (elem != nullptr) {
								MTBB::data *new_data = elem->info;
								elem->info = nullptr;
								delete elem;

								ArrFunctions::copyArr(new_data->var, data->var, data->task->n);
								new_data->set = data->set + 1;
								if (new_data->maximum < data->maximum) {
									data->maximum = new_data->maximum;
								}
								else
								{
									new_data->maximum = data->maximum;
								}
								
								threadpool_.async_task(&MTBB::search, this, new_data, false);
							}
							else {
								search(data, true);
							}
							data->var[data->set] = 0;
						}
					}
				}
			}
		}
		else {
			int f = 0;
			f = data->task->procs.crit(data->var, data->task->jobs, data->set);

			std::unique_lock<std::mutex> locker(min_mutex);
			if (minF < f) {
				data->maximum = minF;
			} 
			else if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best_[i] = var_[i];
			}
		}
		if (!save_data) {
			std::unique_lock<std::mutex> locker(stack_mutex_);
			stack.push(data);
		}
		//return minF;
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