#pragma once
#include "stdafx.h"
#include "Task.cpp"

class Marks {
protected:
	int n, *buf;
public:
	Marks() {
		n = 0;
		buf = NULL;
	}

	Marks(int n) {
		this->n = n;
		buf = new int[n];
	}

	void init(int n) {
		this->n = n;
		delete[] buf;
		buf = new int[n];
	}

	virtual int minB(int *var, int set, Task &task) = 0;

	virtual int maxB(int *var, int set, Task &task) = 0;

	virtual int* getBuf() {
		return buf;
	}

	virtual ~Marks() {
		delete[] buf;
	}
};