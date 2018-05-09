#pragma once
#include "stdafx.h"
#include "AMethods.cpp"

class SortOut : public AMethod {
public:
	double timeSO, timeCrit, timeCheck, buf;

	void Update() {
	}

	void Start(Task &task, int set) {
		timeCrit = timeCheck = buf = 0;
		minF = sortOut(set, task);
	}

	int sortOut(int set, Task &task) {
		if (!task.jobs.Check(var, set)) {
			return minF;
		}

		countVar++;
		if (set < n) {
			int j = 0;
			for (int i = 0; i < n; i++) {
				j = 0;
				while (var[j] != 0) {
					if (var[j] == i + 1)
						break;
					else
						j++;
				}
				if (j == set) {
					var[set] = i + 1;
					sortOut(set + 1, task);
					var[set] = 0;
				}
			}
		}
		else {
			int f = 0;
			f = task.procs.crit(var, task.jobs, set);

			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best[i] = var[i];
			}
		}
		return minF;
	}
};