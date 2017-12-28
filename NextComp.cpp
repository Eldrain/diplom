#pragma once
#include "stdafx.h"
#include "INextComp.cpp"

class NextComp :public INextComp {//class for choose next job for fulfitting on calculation MinMigozzi mark
public:
	NextComp(int size) : INextComp(size) {}

	int next(Jobs &jobs) {
		Stack<int>::Iterator *i = jobs.GetFrontIterator();
		return 0;
	}

	int dif(Jobs &jobs) {
		int size = set.size();
		int dif = 0;

		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
				if (i == j) {
					continue;
				}
				dif += abs(jobs[set[i]] - jobs[set[j]]);
			}
		}

		return dif;
	}

	int abs(int n) {
		if (n < 0) {
			return -n;
		}
		return n;
	}
	virtual ~NextComp() {
	}

};