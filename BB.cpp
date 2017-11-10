#include "stdafx.h"
#include "AMethod.cpp"

class BB : public AMethod {
public:
	int countVar, *buf;
	double timeClip, timeCrit, timeCheck, bufTime, minTime, maxTime;

	void update() {
		AMethod::update();

		delete[] buf;
		buf = new int[n];
	}

	int AMethod::solve(Task &task) {
		minF = 0;
		countVar = 0;

		n = task.n;
		update();
		for (int i = 0; i < n; i++)
			minF += task.jobs.jobs[i].time; // переопределенный оператор индекса. На самом деле возвращает jobs.время выполнения работы.
		ArrFunctions::clearArr(var, n);
		minF++; //для цепочки (для того, чтобы best заполнился хотя бы один раз

		int maximum = minF;

		timeCrit = timeCheck = bufTime = minTime = maxTime = 0;
		timeClip = clock();
		minF = clip(0, maximum, task);
		timeClip = (clock() - timeClip) / 1000;

		int set = countSet(best, n);
		if (set < n) {
			max(best, set, task);
			for (int i = set; i < n; i++)
				best[i] = buf[i];
		}
		return minF;
	}

	int clip(int set, int &maximum, Task &task) {
		bufTime = clock();
		if (!task.jobs.checkVar(var, set)) {
			timeCheck += (clock() - bufTime) / 1000;
			return minF;
		}
		timeCheck += (clock() - bufTime) / 1000;

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
					int mx = max(var, set + 1, task);
					maxTime += (clock() - bufTime) / 1000;
					
					bufTime = clock();
					int mn = min(var, set + 1, task);
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

			bufTime = clock();
			f = task.procs.crit(var, task.jobs, set);
			timeCrit += (clock() - bufTime) / 1000;
			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best[i] = var[i];
			}
		}
		return minF;
	}

	int min(int *var, int set, Task &task) {
		task.procs.crit(var, task.jobs, set);
		
		int value = task.procs.adjustment(task.jobs.jobs[task.jobs.minTime()].time, n - set);
		
		return value;
	}

	int max(int *var, int set, Task &task) {
		int i = 0;
		task.jobs.refresh();

		for (; i < set; i++) {
			buf[i] = var[i];
			task.jobs.complete(var[i]);
		}

		int maxNum = 0;
		while (i < n) {
			maxNum = task.jobs.front.findMax(task.jobs);
			buf[i] = maxNum;
			i++;
			task.jobs.complete(maxNum);
		}

		//std::cout << std::endl << "\nbuffer: ";
		//printArr(buffer, n);
		return task.procs.crit(buf, task.jobs, n);
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
	}
};