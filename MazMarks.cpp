#include "stdafx.h"
#include "Marks.cpp"

class MazMarks : public Marks {
public:

    int minB(int *var, int set, Task &task) {
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

	~MazMarks() {

	}
    
};