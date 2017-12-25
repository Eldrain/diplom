#pragma once
#include "stdafx.h"
#include "IValue.cpp" 

class FastValue : public IValue {
public:
	int Value(int *var, Jobs &jobs, int set, sort::vector<processor> &pr, int m) {
		int pointer = 0;
		int allTime = 0;
		jobs.refresh();
		int unbusy = m;
		int i;
		int minTime;

		while (pointer != set) {
			unbusy = m;

			while (jobs.FindInFront(var[pointer]) && unbusy > 0) {
				for (i = 0; i < m; i++) {
					if (pr[i].busy == false) {
						break;
					}
				}
				pr[i].busy = true;
				pr[i].mWork = jobs[var[pointer] - 1];
				pointer++;
				unbusy--;
			}
			minTime = INT_MAX;

			for (i = 0; i < m; i++) {
				if (pr[i].mWork < minTime) {
					minTime = pr[i].mWork;
				}
			}

			allTime += minTime;
			for (i = 0; i < m; i++) {
				if (pr[i].busy == true) {
					pr[i].mAll = minTime;
				}
				if (pr[i].work(minTime) && pointer == set) {
					break;
				}
			}

		}

		return allTime;
	}

	~FastValue() {

	}
};