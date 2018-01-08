#pragma once
#include "stdafx.h"
#include "IFModule.cpp"
#include "ArrFunctions.cpp"

class BackModule : public IFModule {
public:
	BackModule() : pairs_(nullptr) {}
	
	void update(Jobs &jobs) {
		delete[] pairs_;
		pairs_ = new int[jobs.get_count()];
		calc_hook hook(jobs, 1, 0, pairs_);
		//ArrFunctions::printArr(pairs_, jobs.get_count());
	}

	int next(Jobs &jobs) {
		int i = 0;
		int max = 0;
		for (; i < jobs.get_count(); i++) {
			if (pairs_[i] > pairs_[max]) {
				max = i;
			}
		}
		pairs_[max] = 0;
		return max + 1;
	}

	virtual ~BackModule() {
		delete[] pairs_;
	}

private:
	int *pairs_;

	class calc_hook {
	public:
		calc_hook(Jobs &jobs, int n, int f, int *pairs) {
			f += jobs[n - 1];
			if (pairs[n - 1] < f) {
				pairs[n - 1] = f;
			}
			else {
				f = pairs[n - 1];
			}
			
			if (jobs.CountPrev(n) != 0) {
				int cur_prev = jobs.GetNextPrev(n, jobs.get_count() + 1);
				
				while (cur_prev != 0) {
					calc_hook hook(jobs, cur_prev, f, pairs);
					cur_prev = jobs.GetNextPrev(n, cur_prev);
				} 
			}
		}

		~calc_hook() {
		}
	};
};