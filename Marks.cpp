#pragma once
#include "stdafx.h"
#include "Mark.cpp"

class Marks {
protected:
	//vector<int> buf_;
	int *buf_;
	int n_;
	Mark *max;
	Mark *min;

	//Init objects of marks for work
	//virtual void initMarks() = 0;
public:
	Marks() {
		buf_ = NULL;
		n_ = 0;
	}

	Marks(int n) {
		buf_ = new int[n];
		//buf_.resize(n);
		n_ = n;
	}

	void init(int n) {
		//initMarks();
		delete[] buf_;
		buf_ = new int[n];
		n_ = n;
		//buf_.resize(n);
	}

	int minB(int *var, int set, Task &task) {
		return min->bound(var, set, task, buf_);
	}

	int maxB(int *var, int set, Task &task) {
		return max->bound(var, set, task, buf_);
	}

	int* GetBuf() {
		return buf_;
	}

	virtual ~Marks() {
		delete[] buf_;
		delete max;
		delete min;
	}
};