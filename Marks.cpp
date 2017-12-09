#pragma once
#include "stdafx.h"
#include "Task.cpp"

class Marks {
protected:
	sort::vector<int> buf_;
public:
	Marks() {
	}

	Marks(int n) {
		buf_.resize(n);
	}

	void init(int n) {
		buf_.resize(n);
	}

	virtual int minB(sort::vector<int> &var, int set, Task &task) = 0;

	virtual int maxB(sort::vector<int> &var, int set, Task &task) = 0;

	virtual sort::vector<int> &GetBuf() {
		return buf_;
	}

	virtual ~Marks() {
	}
};