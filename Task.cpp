#pragma once
#include "stdafx.h"
#include "Procs.cpp"

class Task {
public:
	int n, m;
	Jobs jobs;
	Procs procs;
	
	Task() {
		m = 0;
		n = 0;
		//procs = new FastProcs();
	}

	/*int crit(int *var, int set) {
		return procs->crit(var, jobs, set);
	}*/

	void ResizeProcs(int m) {
		this->m = m;
		procs.resize(m);
	}


	int getTime(int jobNum) {
		return jobs[jobNum];
	}

	void PrintJobs() {
		jobs.Print();
	}

	//Create clone of parent
	void CloneFrom(Task &parent) {
		ResizeProcs(parent.m);
		jobs.CloneFrom(parent.jobs);
		n = jobs.get_count();
	}

	~Task() {
		//delete procs;
	}
};