#pragma once
#include "stdafx.h"
#include "AProcs.cpp"
#include "Procs.cpp"

class FastProcs : public AProcs {
private:
	//ADAPTER
	Procs procs;
	class processor  {
	public:
		int mJob;
		int mWork;
		int mAll;
		bool busy;

		processor() : mJob(0), mWork(0), mAll(0), busy(false) {}

		void reset() {
			mJob = mWork = mAll = 0;
			busy = false;
		}

		bool work(int time) {
			if (mWork <= time) {
				mWork = 0;
				busy = false;
			}
			else {
				mWork -= time;
			}

			return !busy;
		}
	};

	processor *pr;
public:
	FastProcs(int m = 1) : AProcs(m)  {
		pr = new processor[m];
		procs.resize(m);
	}

	int crit(int *var, Jobs &jobs, int set) {
		int pointer = 0;
		int allTime = 0;
		jobs.refresh();
		int unbusy = m;
		int i;
		int minTime;

		while (pointer != set) {
			unbusy = m;

			while (jobs.FindInFront(var[pointer]) && unbusy > 0) {
				for (i = 0; i < m; i++) {
					if (pr[i].busy == false) {
						break;
					}
				}
				pr[i].busy = true;
				pr[i].mWork = jobs[var[pointer] - 1];
				pointer++;
				unbusy--;
			}
			minTime = INT_MAX;

			for (i = 0; i < m; i++) {
				if (pr[i].mWork < minTime) {
					minTime = pr[i].mWork;
				}
			}

			allTime += minTime;
			for (i = 0; i < m; i++) {
				if (pr[i].busy == true) {
					pr[i].mAll = minTime;
				}
				if (pr[i].work(minTime) && pointer == set) {
					break;
				}
			}

		}

		return allTime;
	}

	void resize(int m) {
		this->m = m;
		delete[] pr;
		pr = new processor[m];
		procs.resize(m);
	}

	
	int adjustment(int jt, int n) {
		int index = 0;

		while (n != 0) {
			index = MinBusy();
			pr[index].mAll += jt;
			n--;
		}

		return pr[MaxBusy()].mAll;
	}

	int MaxBusy() {
		int i = 0;
		int index = 0;
		for (; i < m; i++) {
			if (pr[i].mWork > pr[index].mWork) {
				index = i;
			}
		}
		return index;
	}

	int MinBusy() {
		int i = 0;
		int index = 0;
		for (; i < m; i++) {
			if (pr[i].mWork < pr[index].mWork) {
				index = i;
			}
		}
		return index;
	}

	int GetMaxTime() {
		return pr[MaxBusy()].mAll;
	}

	int GetTime(int index) {
		return pr[index].mAll;
	}

	~FastProcs() {
		delete[] pr;
	}
};