#pragma once
#include "Mark.cpp"

class MinSimple : public Mark {
public:
	
	// Add to base time tail from 'k' min time jobs.
	// k = task.n - set
	int bound(int *var, int set, Task &task, int *buf) {
		task.procs->crit(var, task.jobs, set);
		int minTime = task.jobs[task.jobs.MinTime()];
		int minProcIndex = 0;
		int maxProcIndex = 0;

		for (int i = 0; i < task.m; i++) {
			buf[i] = task.procs->getTime(i);
			if (buf[i] < buf[minProcIndex]) {
				minProcIndex = i;
			}
		}
		
		for (int k = 0; k < task.n - set; k++) {
			buf[minProcIndex] += minTime;
			for (int i = 0; i < task.m; i++) {
				if (buf[i] < buf[minProcIndex]) {
					minProcIndex = i;
				}	
			}
		}

		for (int i = 0; i < task.m; i++) {
			if (buf[i] > buf[maxProcIndex]) {
				maxProcIndex = i;
			}
		}
		
		return buf[maxProcIndex];
	}
};