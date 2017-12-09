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
	}

	Task(std::string filename) {
		//loadTask(filename);
	}

	void createProcs(int m) {
		this->m = m;
		procs.create(m);
	}


	int getTime(int jobNum) {
		return jobs[jobNum];
	}

	void PrintJobs() {
		jobs.Print();
	}
};