#pragma once
#include "stdafx.h"
#include "Jobs.cpp"
#include "processor.cpp"

class IValue {
public:
	virtual int Value(int *var, Jobs &jobs, int set, sort::vector<processor> &pr, int m) = 0;

	virtual ~IValue() {

	}
};