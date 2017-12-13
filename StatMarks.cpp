#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "Statistics.cpp"

template <class T>
class StatMarks : public Marks {
private:
	Statistics *stat;
	Marks *marks;

public:
	StatMarks(Statistics *st) : stat(st) {
		marks = new T();
	}

	int minB(int *var, int set, Task &task) {
		int min = marks->minB(var, set, task);
		stat->AddMin(min);
		return min;
	}

	int maxB(int *var, int set, Task &task) {
		int max = marks->maxB(var, set, task);
		stat->AddMax(max);
		return max;
	}

	void init(int n) {
		marks->init(n);
	}
	
	int* GetBuf() {
		return marks->GetBuf();
	}

	~StatMarks() {
		delete marks;
	}
};