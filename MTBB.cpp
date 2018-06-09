#pragma once
#include "ObjectStack.cpp"
#include "FrontAlg.cpp"
#include "threadpool.cpp"
#include <vector>
#include <mutex>
#include "MarkFactory.cpp"

class MTBB : public AMethod {
private:
	class solution {
	public:
		int maximum;
		int *var;
		int set;
		int countVar;
		Task *task;
		Mark *min;
		Mark *max;
		int *buf;

		~solution() {
			delete max;
			delete min;
			delete task;
			delete[] var;
		}
	};

	eld::threadpool threadpool_;
	std::mutex stack_mutex_;
	std::mutex min_mutex;
	int thread_count_;
	ObjectStack<solution> stack;	
	MarkFactory markFactory;
public:
	MTBB(int thread_count = 10) : AMethod(4, "Multi-Thread B&B"), threadpool_(thread_count), thread_count_(thread_count){}

	void Update() {
		stack.clear();
	}

	void Start(Task &task, int set)
	{	
		for (int i = 0; i < thread_count_; i++) {
			solution *sol = new solution();
			
			sol->maximum = INT32_MAX;
			sol->max = markFactory.createSecondMax();//createBestMax();
			sol->min = markFactory.createMinPath();//createMinPath();
			sol->buf = new int[task.n];
			sol->task = new Task();
			sol->task->CloneFrom(task);
			sol->set = 0;
			sol->var = new int[task.n];
			sol->countVar = 0;
			ArrFunctions::clearArr(sol->var, task.n);

			stack.push(sol);
		}
		ObjectStack<solution>::elem *elem = stack.pop();
		solution *data = elem->info;
		elem->info = nullptr;
		delete elem;
		Prepare(task);
		//std::cout << "\nMTBB: prepare minimum = " << minF;
		data->maximum = minF;

		search(data, false);
		threadpool_.join();
		
		countVar = 0;
		ObjectStack<MTBB::solution>::Iterator *i = stack.GetIterator();
		if (i == nullptr) {
			return;
		}
		do {
			countVar += i->current_->info->countVar;
		} while(i->get_next());
	}

	void search(solution *data, bool save_data) {
		if (!data->task->jobs.Check(data->var, data->set)) {
			std::unique_lock<std::mutex> locker(stack_mutex_);
			stack.push(data);
			return;
		}
		data->countVar++;

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

					int mx = data->max->bound(data->var, data->set + 1, *data->task, data->buf);
					int mn = data->min->bound(data->var, data->set + 1, *data->task, data->buf);
					
					if (mx < data->maximum) {
						data->maximum = mx;
					}
					
					if (mn == mx) {
						min_mutex.lock();
						if (mn < minF) {
							minF = mn;
							for (int i = 0; i < n; i++)
								best[i] = data->var[i];
						}
						min_mutex.unlock();
					}
					else {		
						if (mn <= data->maximum) {
							ObjectStack<solution>::elem *elem = nullptr;
							
							stack_mutex_.lock();
							elem = stack.pop();
							stack_mutex_.unlock();
							
							if (elem != nullptr) {
								solution *new_data = elem->info;
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
								data->set++;
								search(data, true);
								data->set--;
							}
							
						}
					}
					data->var[data->set] = 0;
				}
			}
		}
		else {
			int f = 0;
			f = data->task->procs->crit(data->var, data->task->jobs, data->set);

			std::unique_lock<std::mutex> locker(min_mutex);
			if (minF < f) {
				data->maximum = minF;
			} 
			else if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best[i] = var[i];
			}
		}
		if (!save_data) {
			std::unique_lock<std::mutex> locker(stack_mutex_);
			stack.push(data);
		}
	}

	void Prepare(Task &task) {
		FrontAlg front;
		Solution *sol = front.Solve(task);
		minF = sol->getMin();
		// TODO: delete this log
		std::cout << std::endl << "prepare minimum: " << minF;
		ArrFunctions::copyArr(best, sol->getArr(), n);
		delete sol;
	}

	~MTBB() {
	}
};