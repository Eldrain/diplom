//#include "stdafx.h"
#include "AMethod.cpp"

class SortOut : public AMethod {
public:
	double timeSO, timeCrit, timeCheck, buf;

	int solve(Task &task) {
		n = task.n;
		update();
		minF = 0;
		countVar = 0;
		for (int i = 0; i < n; i++)
			minF += task.jobs.jobs[i].time; // ���������������� �������� �������. �� ����� ���� ���������� ����� ���������� ������.
		clearArr(var, n);
		minF++; //��� ������� (��� ����, ����� best ���������� ���� �� ���� ���

		timeCrit = timeCheck = buf = 0;
		time = clock();
		minF = sortOut(0, task);
		time = (clock() - time) / CLOCKS_PER_SEC;

		return minF;
	}

	int sortOut(int set, Task &task) {
		buf = clock();
		if (!task.jobs.checkVar(var, set)) {
			timeCheck += (clock() - buf) / 1000;
			return minF;
		}
		timeCheck += (clock() - buf) / 1000;
		//std::cout << std::endl;
		//printArr(var, jobs->count);
		//std::cout << "| min = " << min(var, set) << "; max =  " << max(var, set);

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
					sortOut(set + 1,task);
					var[set] = 0;
				}
			}
		}
		else {
			int f = 0;
			//jobs->print();

			buf = clock();
			f = task.procs.crit(var, task.jobs, set);
			timeCrit += (clock() - buf) / 1000;

			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best[i] = var[i];
			}
		}
		return minF;
	}
};