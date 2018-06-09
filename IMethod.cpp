#pragma once
#include "stdafx.h"
#include "Task.cpp"
#include "Stats.cpp"
#include "Solution.cpp"

class IMethod {
public:

	virtual Solution* Solve(Task &task) = 0;
	virtual void setStats(Stats *stats) = 0;
	virtual ~IMethod() {}
};