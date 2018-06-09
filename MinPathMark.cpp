#pragma once
#include "Mark.cpp"
#include "Hook.cpp"

class MinPathMark : public Mark {
private:
	Hook hook;
	int len;
public:
	MinPathMark() : len(0) {}

	// Value of critical path
	int bound(int *var, int set, Task &task, int *buf) {
		if (set == task.n) {
			return task.procs->crit(var, task.jobs, set);
		}
		if (len != task.n) {
			len = task.n;
			hook.update(len);
		}
		int jobsCount = -1;
		task.procs->crit(var, task.jobs, set);
		ArrFunctions::copyArr(buf, var, set);
		hook.calculateHooks(task.jobs, buf + set, jobsCount);
		if (jobsCount != task.n - set) {
			std::cout << "\nMinPathMark Error! Unexpected jobs count in sorted array";
		}

		task.jobs.refresh();
		return task.procs->crit(buf, task.jobs, task.n);
	}
};