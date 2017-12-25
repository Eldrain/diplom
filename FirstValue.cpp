#pragma once
#include "stdafx.h"
#include "IValue.cpp" 

class FirstValue : public IValue {
public:
	int Value(int *var, Jobs &jobs, int set, sort::vector<processor> &pr, int m) {
		for (int i = 0; i < m; i++) {
			pr[i].reset();
		}

		if (set == 0)
			return 0;
		int workTime = 0, minWork = 0, f = 0, completeJob = 0;
		int n = jobs.get_count();

		jobs.refresh();
		int nextJob = 0;
		while (true) {
			//if (nextJob < n) {
			for (int i = 0; i < m; i++)
				if (jobs.FindInFront(var[nextJob]) && pr[i].mWork == 0) {
				pr[i].mWork = jobs[var[nextJob] - 1];//[]
				pr[i].mJob = var[nextJob];
				nextJob++;
				if (nextJob == n)
					break;
				}
			//}


			minWork = jobs[0];//[]

			for (int i = 0; i < m; i++)
				if (pr[i].mWork > 0 && minWork > pr[i].mWork)
					minWork = pr[i].mWork;

			int res = 0;
			for (int i = 0; i < m; i++) {
				pr[i].buf += minWork;

				if (pr[i].mWork > 0) {
					pr[i].mWork -= minWork;
					pr[i].mAll += pr[i].buf;
					pr[i].buf = 0;

					if (pr[i].mWork == 0) {
						jobs.Complete(pr[i].mJob);

						completeJob++;
						if (completeJob == set) {
							res = i;
						}

					}
				}
				else if (pr[i].mWork < 0)
					std::cout << "\nProcNum Error!";
			}

			if (completeJob == set) {
				return pr[res].mAll;
			}
		}
	}

	~FirstValue() {
	}
};