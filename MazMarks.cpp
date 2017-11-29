#include "stdafx.h"
#include "Marks.cpp"

class MazMarks : public Marks {
public:

    int minB(int *var, int set, Task &task) {
		//if(set == task.n - 1)
		//	return maxB(var, set, task);
		task.jobs.front.print();
        int crit = task.procs.crit(var, task.jobs, set);
        
        int m = task.m;
        int minTime = 0;
        int bound = 0;

        while(task.jobs.front.GetSize() != 0) {
            minTime = task.jobs.front.findMin(task.jobs);
            bound += task.jobs[minTime - 1];
            task.jobs.CompleteJobs(m);
        }
       // std::cout << "\nMin bound = " << crit + bound;

		return crit + bound;
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

		return task.procs.crit(buf, task.jobs, n);
	}

	~MazMarks() {

	}
    
};