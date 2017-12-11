#pragma once
#include "stdafx.h"
#include "Task.cpp"

class Marks {
protected:
	//vector<int> buf_;
	int *buf_;
	int n_;
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
		delete[] buf_;
		buf_ = new int[n];
		n_ = n;
		//buf_.resize(n);
	}

	virtual int minB(int *var, int set, Task &task) = 0;

	virtual int maxB(int *var, int set, Task &task) = 0;

	int* GetBuf() {
		return buf_;
	}

	virtual ~Marks() {
		delete[] buf_;
	}
};