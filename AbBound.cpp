#pragma once
#include "stdafx.h"
#include "MarkMethod.cpp"
#include "MarkFactory.cpp"

class AbBound : public MarkMethod {//Method Branches and Bounds
public:
	double timeClip, timeCrit, timeCheck, bufTime, minTime, maxTime;

	AbBound() : MarkMethod(1, "Alpha-Beta alg") {}

	void Update() {
		delete[] buf;
		buf = new int[n];
	}

	void Start(Task &task, int set) {
		int maximum = minF;

		timeCrit = timeCheck = bufTime = minTime = maxTime = 0;
		minF = clip(set, maximum, task);

		set = countSet(best);
		if (set < n) {	
			max->bound(best, set, task, buf);
			ArrFunctions::copyArr(best, buf, n);
		}
	}

	int clip(int set, int &maximum, Task &task) {
		if (!task.jobs.Check(var, set)) {
			return minF;
		}

		countVar++;
		if (set < n) {
			int j = 0;
			for (int i = 0; i < n; i++) {
				j = 0;
				while (var[j] != 0)
					if (var[j] == i + 1)
						break;
					else
						j++;
				if (j == set) {
					var[set] = i + 1;
					if (!task.jobs.Check(var, set + 1)) {
						var[set] = 0;
						continue;
					}
					bufTime = clock();
					int mx = max->bound(var, set + 1, task, buf);
					maxTime += (clock() - bufTime) / 1000;
					
					bufTime = clock();
					int mn = min->bound(var, set + 1, task, buf);
					minTime += (clock() - bufTime) / 1000;

					if (mx < maximum)
						maximum = mx;
					if (mn == mx) {
						if (mn < minF) {
							minF = mn;
							for (int i = 0; i < n; i++)
								best[i] = var[i];
						}
					}
					else if (mn <= maximum)
						clip(set + 1, maximum, task);

					var[set] = 0;
				}
			}
		} else {
			int f = 0;
			//f = task.crit(var_, set);
			f = task.procs->crit(var, task.jobs, set);

			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best[i] = var[i];
			}
		}
		return minF;
	}

	int countSet(int *var) {
		int set = 0;
		for (int i = 0; i < n; i++)
			if (var[i] == 0)
				return set;
			else
				set++;
		return set;
	}

	int countSet(vector<int> &var) {
		int set = 0;
		for (int i = 0; i < n; i++)
			if (var[i] == 0)
				return set;
			else
				set++;
		return set;
	}

	~AbBound() {
	}
};