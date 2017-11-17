#pragma once
#include "stdafx.h"
#include "Marks.cpp"

class BBMarks : public Marks {
	int n, *buf;
public:
	BBMarks() {
		n = 0;
		buf = NULL;
	}

	BBMarks(int n) {
		this->n = n;
		buf = new int[n];
	}

	void init(int n) {
		this->n = n;
		delete[] buf;
		buf = new int[n];
	}

	int minB(int *var, int set, Task &task) {
		task.procs.crit(var, task.jobs, set);

		int value = task.procs.adjustment(task.jobs.jobs[task.jobs.minTime()].time, n - set);

		return value;
	}

	int maxB(int *var, int set, Task &task) {
		int i = 0;
		task.jobs.refresh();

		for (; i < set; i++) {
			buf[i] = var[i];
			task.jobs.complete(var[i]);
		}

		int maxNum = 0;
		while (i < n) {
			maxNum = task.jobs.front.findMax(task.jobs);
			buf[i] = maxNum;
			i++;
			task.jobs.complete(maxNum);
		}

		//std::cout << std::endl << "\nbuffer: ";
		//printArr(buffer, n);
		return task.procs.crit(buf, task.jobs, n);
	}

	int* getBuf() 
	{
		return buf;
	}

	~BBMarks() {
		delete[] buf;
		buf = NULL;
	}
};