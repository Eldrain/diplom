#include "stdafx.h"
#include "Task.cpp"

class Marks {
	virtual int min(int *var, int set, Task &task) = 0;

	virtual int max(int *var, int set, Task &task) = 0;
};