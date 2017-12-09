#pragma once
#include "stdafx.h"
#include "Marks.cpp"

class BBMarks : public Marks {
public:

	int minB(sort::vector<int> &var, int set, Task &task) {
		task.procs.crit(var, task.jobs, set);

		int value = task.procs.adjustment(task.getTime(task.jobs.MinTime()), var.size() - set);

		return value;
	}

	int maxB(sort::vector<int> &var, int set, Task &task) {
		int i = 0;
		task.jobs.refresh();

		for (; i < set; i++) {
			buf_[i] = var[i];
			task.jobs.Complete(var[i]);
		}

		int maxNum = 0;
		while (i < var.size()) {
			maxNum = task.jobs.FindMaxInFront();
			buf_[i] = maxNum;
			i++;
			task.jobs.Complete(maxNum);
		}

		return task.procs.crit(buf_, task.jobs, buf_.size());
	}

	~BBMarks() {
	}
};