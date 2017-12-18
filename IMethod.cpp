#pragma once
#include "stdafx.h"
#include "Task.cpp"

class IMethod {
public:

	virtual int Solve(Task &task) = 0;

	virtual void PrintRes() = 0;

	virtual void GetRes(std::string &res) = 0;

	virtual void GetAddInfo(std::string &info) = 0;

	virtual ~IMethod() {
	}
};