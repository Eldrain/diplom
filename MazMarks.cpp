#pragma once
#include "stdafx.h"
#include "Marks.cpp"

class MazMarks : public Marks {
public:

	int minB(std::vector<int> &var, int set, Task &task) {
        int crit = task.procs.crit(var, task.jobs, set);
        
        int m = task.m;
        int minTime = 0;
        int bound = 0;

        while(task.jobs.front_size() != 0) {
            minTime = task.jobs.FindMinInFront();
            bound += task.jobs[minTime - 1];
            task.jobs.CompleteJobs(m);
        }

		return crit + bound;
	}

	int maxB(std::vector<int> &var, int set, Task &task) {
		int i = 0;
		task.jobs.refresh();

		for (; i < set; i++) {
			buf_[i] = var[i];
			task.jobs.Complete(var[i]);
		}

		int maxNum = 0;
		while (i < buf_.size()) {
			maxNum = task.jobs.FindMaxInFront();
			buf_[i] = maxNum;
			i++;
			task.jobs.Complete(maxNum);
		}

		return task.procs.crit(buf_, task.jobs, buf_.size());
	}

	~MazMarks() {

	}
    
};