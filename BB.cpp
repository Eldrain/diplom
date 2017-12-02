#include "stdafx.h"
#include "AMethod.cpp"
#include "BBMarks.cpp"

class BB : public AMethod {
public:
	int *buf;
	double timeClip, timeCrit, timeCheck, bufTime, minTime, maxTime;
	Marks *marks;

	BB() {
		marks = new BBMarks();
	}

	void update() {
		AMethod::update();

		marks->init(n);
		delete[] buf;
		buf = new int[n];
	}

	int solve(Task &task) {
		minF = 0;
		countVar = 0;

		n = task.n;
		update();
		for (int i = 0; i < n; i++)
			minF += task.jobs.jobs[i].time; // ���������������� �������� �������. �� ����� ���� ���������� jobs.����� ���������� ������.
		clearArr(var, n);
		minF++; //��� ������� (��� ����, ����� best ���������� ���� �� ���� ���

		int maximum = minF;

		timeCrit = timeCheck = bufTime = minTime = maxTime = 0;
		time = clock();
		minF = clip(0, maximum, task);
		time = (clock() - time) / CLOCKS_PER_SEC;

		int set = countSet(best, n);
		if (set < n) {
			marks->maxB(best, set, task);
			for (int i = set; i < n; i++)
				best[i] = buf[i];
		}
		return minF;
	}

	int clip(int set, int &maximum, Task &task) {
		if (!task.jobs.checkVar(var, set)) {
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
					if (!task.jobs.checkVar(var, set + 1)) {
						var[set] = 0;
						continue;
					}
					bufTime = clock();
					int mx = marks->maxB(var, set + 1, task);
					maxTime += (clock() - bufTime) / 1000;
					
					bufTime = clock();
					int mn = marks->minB(var, set + 1, task);
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
			f = task.procs.crit(var, task.jobs, set);

			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best[i] = var[i];
			}
		}
		return minF;
	}

	int countSet(int *var, int n) {
		int set = 0;
		for (int i = 0; i < n; i++)
			if (var[i] == 0)
				return set;
			else
				set++;
		return set;
	}

	~BB() {
		delete[] buf;
		delete marks;
		marks = NULL;
	}
};