#pragma once
#include "stdafx.h"
#include "Jobs.cpp"

class IProcs {
public:
	virtual int crit(int *var, Jobs &jobs, int set) = 0;

	virtual void resize(int m) = 0;

	virtual int size() = 0;

	virtual int adjustment(int, int) = 0;

	virtual int MinBusy() = 0;

	virtual int GetMaxTime() = 0;

	virtual int GetTime(int index) = 0;

	virtual ~IProcs() {

	}
};