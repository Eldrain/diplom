#pragma once
//#include "stdafx.h"
#include "Mark.cpp"

class MinSimple : public Mark {
public:
	//Returns value of min mark
	int bound(int *var, int set, Task &task, int *buf) {
		task.procs.crit(var, task.jobs, set);

		int value = task.procs.adjustment(task.getTime(task.jobs.MinTime()), task.n - set);

		return value;
	}
};