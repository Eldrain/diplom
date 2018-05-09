#pragma once
#include "AMethod.cpp"
#include "MaxModule.cpp"
#include "MinModule.cpp"
#include "BackModule.cpp"

class FrontAlg : public AMethod {
private:
	eld::vector<Module*> modules_;
public:
	
	FrontAlg() : AMethod(3, "FrontAlg") {
		modules_.resize(3);
		modules_[0] = new MaxModule();
		modules_[1] = new MinModule();
		modules_[2] = new BackModule();
	}

	void Update() {
	}

	void Start(Task &task, int set) {
		int f = 0;
		for (int i = 0; i < modules_.size(); i++) {
			modules_[i]->update(task.jobs);
			f = solveByModule(modules_[i], task, set);
			if (f < minF) {
				minF = f;
				ArrFunctions::copyArr(best, var, n);
			}
		}
	}

	int solveByModule(Module *mod, Task &task, int set) {
		int index = 0;
		task.jobs.refresh();
		for (int i = 0; i < set; i++) {
			task.jobs.Complete(var[i]);
		}
		for (int i = set; i < n; i++) {
			index = mod->next(task.jobs);
			task.jobs.Complete(index);
			var[i] = index;
		}

		return task.procs.crit(var, task.jobs, n);
	}

	/*int alg3(Task &task) {
		int index = 0, diff = 0, minProc = 0;
		task.jobs.refresh();
		task.procs.prepare();

		index = task.jobs.front.findMin(task.jobs);
		sol3[0] = index;
		task.jobs.complete(index);
		for (int i = 1; i < jobCount - 1; i++) {
			minProc = task.procs.minTime();
			diff = task.procs.maxTime() - minProc;

			index = getMin(diff, task) - 1;
			sol3[i] = index + 1;
			task.jobs.complete(index + 1);

			task.procs.procs[minProc].allTime += task.jobs[index];
		}
		sol3[jobCount - 1] = 1;
		f3 = task.procs.crit(sol3, task.jobs, jobCount);
		return f3;
	}*/

	/*int getMin(int diff, Task &task) {
		int min = 0;// jobs->front.stack.first->info;

		for (int i = 0; i < n; i++) {
			var_[i] = abs(task.jobs[i] - diff);
			if (var_[i] < var_[min - 1] && task.jobs.FindInFront(i + 1))
				min = i + 1;
		}
		return min;
	}*/

	int abs(int a) {
		if(a > 0)
			return a;
		else
			return -a;
	}

	~FrontAlg() {
		for (int i = 0; i < modules_.size(); i++) {
			delete modules_[i];
			modules_[i] = NULL;
		}
	}
};