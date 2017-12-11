#include "stdafx.h"
#include "AMethod.cpp"
#include "MarkFactory.cpp"

class BB : public AMethod {//Method Branches and Bounds
public:
	double timeClip, timeCrit, timeCheck, bufTime, minTime, maxTime;
	Marks *marks;

	BB() {
		marks = MarkFactory::CreateBestMarks();
	}

	void PrintRes() {
		std::cout << "\nA-B clip (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}

	void Update() {
		marks->init(n);
	}

	void Start(Task &task) {
		int maximum = minF;

		timeCrit = timeCheck = bufTime = minTime = maxTime = 0;
		minF = clip(0, maximum, task);

		int set = countSet(best_);
		if (set < n) {	
			marks->maxB(best_, set, task);
			ArrFunctions::copyArr(best_, marks->GetBuf(), n);
			/*int *buffer = marks->GetBuf();

			for (int i = set; i < n; i++)
				best_[i] = buffer[i];*/
		}
	}

	int clip(int set, int &maximum, Task &task) {
		if (!task.jobs.Check(var_, set)) {
			return minF;
		}

		countVar++;
		if (set < n) {
			int j = 0;
			for (int i = 0; i < n; i++) {
				j = 0;
				while (var_[j] != 0)
					if (var_[j] == i + 1)
						break;
					else
						j++;
				if (j == set) {
					var_[set] = i + 1;
					if (!task.jobs.Check(var_, set + 1)) {
						var_[set] = 0;
						continue;
					}
					bufTime = clock();
					int mx = marks->maxB(var_, set + 1, task);
					maxTime += (clock() - bufTime) / 1000;
					
					bufTime = clock();
					int mn = marks->minB(var_, set + 1, task);
					minTime += (clock() - bufTime) / 1000;

					if (mx < maximum)
						maximum = mx;
					if (mn == mx) {
						if (mn < minF) {
							minF = mn;
							for (int i = 0; i < n; i++)
								best_[i] = var_[i];
						}
					}
					else if (mn <= maximum)
						clip(set + 1, maximum, task);

					var_[set] = 0;
				}
			}
		} else {
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

	~BB() {
		delete marks;
		//delete[] buf_;
	}
};