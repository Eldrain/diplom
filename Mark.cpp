#pragma once
#include "stdafx.h"
#include "Task.cpp"

class Mark {
public:
	//Returns value of mark
	virtual int bound(int *var, int set, Task &task, int *buf) = 0;
};