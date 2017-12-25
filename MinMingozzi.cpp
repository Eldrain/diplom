#pragma once
#include "stdafx.h"
#include "Mark.cpp"

class MinMingozzi : public Mark {
public:
	//Returns value of min mark
	int bound(int *var, int set, Task &task, int *buf) {

		int crit = task.procs.crit(var, task.jobs, set);
		int minProcTime = task.procs.GetTime(task.procs.MinBusy());
		int bound = 0;
		int pointer = 0;
		int lastProc = 0;

		for (; lastProc < task.m; lastProc++) {
			if (task.procs.procs[lastProc].mJob == var[set - 1]) {
				break;
			}
		}

		if (task.procs.procs[lastProc].mAll == crit) {
			if ((crit - task.jobs[var[set - 1] - 1]) >= minProcTime) {
				crit -= task.jobs[var[set - 1] - 1];
				task.jobs.Uncomplete(var[set - 1]);
				pointer = set - 1;
			}
			else {
				crit = minProcTime;
				pointer = set;
			}
		}
		else {
			int bound1 = task.procs.procs[lastProc].mAll - task.jobs[var[set - 1] - 1];
			if (minProcTime > bound1) {
				//if (minProcTime < bound1 + task.jobs[var[set - 1]]) {
				crit = minProcTime;
				pointer = set;
				//}
			}
			else {
				task.jobs.Uncomplete(var[set - 1]);
				crit = bound1;
				pointer = set - 1;
			}
			//bound += task.jobs.CompleteJobs(task.m - 1, var, pointer);
		}

		while (pointer != task.n) {
			bound += task.jobs.CompleteJobs(task.m, var, pointer);
		}

		return crit + bound;
	}
};