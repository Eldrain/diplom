#pragma once
#include "stdafx.h"
#include "Task.cpp"
#include <sstream>
#include <string>

class IMethod {
public:

	virtual int Solve(Task &task) = 0;

	virtual void PrintRes() = 0;

	virtual void GetRes(std::ostringstream &res) = 0;

	virtual void GetAddInfo(std::ostringstream &info) = 0;

	virtual ~IMethod() {
	}
};