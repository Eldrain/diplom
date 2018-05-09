#pragma once
#include <Task.cpp>
#include <Solution.cpp>

class IMethod {
public:

	virtual Solution* Solve(Task &task) = 0;
	virtual ~IMethod() = 0;

};