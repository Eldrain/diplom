#pragma once
#include "stdafx.h"
#include "Jobs.cpp"

class INextComp {//class for choose next job for fulfitting on calculation MinMigozzi mark
protected:
	sort::vector<int> set;
public:
	INextComp(int count) {
		set.resize(count);
	}
	virtual int next(Jobs::Front &front) = 0;

	int get(int n) {
		return set[n - 1];
	}

	int GetSize() {
		return set.size();
	}

	virtual ~INextComp() {
	}

};