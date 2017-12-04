#pragma once
#include "stdafx.h"
#include "Task.cpp"

class Marks {
protected:
	std::vector<int> buf_;
public:
	Marks() {
	}

	Marks(int n) {
		buf_.resize(n);
	}

	void init(int n) {
		buf_.resize(n);
	}

	virtual int minB(std::vector<int> &var, int set, Task &task) = 0;

	virtual int maxB(std::vector<int> &var, int set, Task &task) = 0;

	virtual std::vector<int> &GetBuf() {
		return buf_;
	}

	virtual ~Marks() {
	}
};