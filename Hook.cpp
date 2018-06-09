#pragma once

#include "Jobs.cpp"
#include "ArrFunctions.cpp"

// Class fro calculating critical path
class Hook {
public:
	Hook() : pairs(NULL) {}

	// Update buffer array
	void update(int n) {
		delete[] pairs;
		len = n;
		pairs = new int[len];
		//	
	}

	// Calculate order of fulfiting jobs use critical path
	// jobsCount[out] - count jobs in 
	// order[out] - array with sorted jobs 
	void calculateHooks(Jobs &jobs, int *order, int &jobsCount) {
		jobsCount = jobs.getUncompleteCount();
		ArrFunctions::clearArr(pairs, len);
		hook hk(jobs, 1, 0, pairs);
		int j;
		int max = 0;

		// sort jobs by descending values int pairs
		for (int i = 0; i < jobsCount; i++) {
			for (j = 0; j < len; j++) {
				if (pairs[max] < pairs[j]) {
					max = j;
				}
			}
			order[i] = max + 1;
			pairs[max] = 0;
		}
	}

	~Hook() {
		delete[] pairs;
	}
private:
	// pairs is store value of approximate optimum for all jobs
	// in order moves out first to tails
	int *pairs;
	int len;
	// Calculate pairs_ in constructor
	class hook {
	public:
		hook(Jobs &jobs, int n, int f, int *pairs) {
			if (jobs.isComplete(n)) {
				pairs[n - 1] = 0;
				return;
			}
			f += jobs[n - 1];
			// Update app optimum
			if (pairs[n - 1] < f) {
				pairs[n - 1] = f;
			}
			else {
				f = pairs[n - 1];
			}

			if (jobs.CountPrev(n) != 0) {
				// Get one of previous jobs
				int cur_prev = jobs.GetNextPrev(n, jobs.get_count() + 1);

				// While previous job is having
				while (cur_prev != 0) {
					// Cling new hook
					hook hk(jobs, cur_prev, f, pairs);
					cur_prev = jobs.GetNextPrev(n, cur_prev);
				}
			}
		}

		~hook() {
		}
	};
};