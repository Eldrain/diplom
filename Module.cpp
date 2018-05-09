#pragma once
#include "Jobs.cpp"

// Front alg Module for selection next element
// in solution's array
class Module {
public:

	virtual void update(Jobs &jobs) = 0;

	virtual int next(Jobs &jobs) = 0;

	virtual ~Module() {}
};