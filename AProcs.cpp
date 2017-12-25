#pragma once
#include "stdafx.h"
#include "IProcs.cpp"

class AProcs : public IProcs {
protected:
	int m;

public:
	AProcs(int m = 1) : m(m) {}

	virtual int crit(int *var, Jobs &jobs, int set) = 0;

	virtual void resize(int m) = 0;

	int size() {
		return m;
	}
};