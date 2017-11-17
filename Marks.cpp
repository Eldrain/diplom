#pragma once
#include "stdafx.h"
#include "Task.cpp"

class Marks {
public:
	virtual int minB(int *var, int set, Task &task) = 0;

	virtual int maxB(int *var, int set, Task &task) = 0;

	virtual int* getBuf() = 0;

	virtual ~Marks() {
	}
};