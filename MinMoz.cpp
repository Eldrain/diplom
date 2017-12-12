#pragma once
#include "stdafx.h"
#include "Mark.cpp"

class MinMoz : public Mark {
public:
	//Returns value of min mark
	int bound(int *var, int set, Task &task, int *buf) {
		/*int crit = task.procs.crit(var, task.jobs, set);

		int m = task.m;
		int minTime = 0;
		int bound = 0;

		while (task.jobs.front_size() != 0) {
			minTime = task.jobs.FindMinInFront();
			bound += task.jobs[minTime - 1];
			task.jobs.CompleteJobs(m);
		}*/

		task.jobs.refresh();
		int bound = 0;
		int pointer = 0;

		while (pointer != task.n) {
			bound += task.jobs.CompleteJobs(task.m, var, pointer);
		}

		return bound;
	}
};