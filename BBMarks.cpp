#pragma once
#include "stdafx.h"
#include "Marks.cpp"

class BBMarks : public Marks {
public:

	int minB(int *var, int set, Task &task) {
		task.procs.crit(var, task.jobs, set);

		int value = task.procs.adjustment(task.getTime(task.jobs.MinTime()), n - set);

		return value;
	}

	int maxB(int *var, int set, Task &task) {
		int i = 0;
		task.jobs.refresh();

		for (; i < set; i++) {
			buf[i] = var[i];
			task.jobs.Complete(var[i]);
		}

		int maxNum = 0;
		while (i < n) {
			maxNum = task.jobs.FindMaxInFront();
			buf[i] = maxNum;
			i++;
			task.jobs.Complete(maxNum);
		}

		return task.procs.crit(buf, task.jobs, n);
	}

	~BBMarks() {
	}
};