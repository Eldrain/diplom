#include "stdafx.h"
#include "AMethod.cpp"

class SortOut : public AMethod {
public:
	double timeSO, timeCrit, timeCheck, buf;

	void Update() {

	}

	void PrintRes() {
		std::cout << "\nSort out (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}

	void Start(Task &task) {
		timeCrit = timeCheck = buf = 0;
		minF = sortOut(0, task);
	}

	int sortOut(int set, Task &task) {
		if (!task.jobs.Check(var_, set)) {
			return minF;
		}

		countVar++;
		if (set < n) {
			int j = 0;
			for (int i = 0; i < n; i++) {
				j = 0;
				while (var_[j] != 0) {
					if (var_[j] == i + 1)
						break;
					else
						j++;
				}
				if (j == set) {
					var_[set] = i + 1;
					sortOut(set + 1,task);
					var_[set] = 0;
				}
			}
		}
		else {
			int f = 0;
			f = task.procs.crit(var_, task.jobs, set);

			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					best_[i] = var_[i];
			}
		}
		return minF;
	}
};