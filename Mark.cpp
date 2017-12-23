#pragma once
//#include "stdafx.h"
#include "Task.cpp"

class Mark {//Class for declaration marks
public:
	//Returns value of mark
	virtual int bound(int *var, int set, Task &task, int *buf) = 0;
};