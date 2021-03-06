#pragma once
#include "stdafx.h"
#include "Mark.cpp"

class MaxMaxFront : public Mark {
public:
	//Returns value of max mark
	int bound(int *var, int set, Task &task , int *buf) {
		int i = 0;
		task.jobs.refresh();

		for (; i < set; i++) {
			buf[i] = var[i];
			task.jobs.Complete(var[i]);
		}

		int maxNum = 0;
		while (i < task.n) {
			maxNum = task.jobs.FindMaxInFront();
			buf[i] = maxNum;
			i++;
			task.jobs.Complete(maxNum);
		}

		return task.procs->crit(buf, task.jobs, task.n);
	}
};