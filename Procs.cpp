#pragma once
#include "IProcs.cpp"
#include "ArrFunctions.cpp"

class Procs : public IProcs {
private:
	struct processor {
		int mJob; // number of processing job
		int mWork; //
		int buf;
		int mAll; // All time
		bool busy; // flag bussines	
	};

	int maxTime() {
		int max = 0;
		for (int i = 0; i < count; i++)
			if (procs[max].mAll < procs[i].mAll)
				max = i;
		return max;
	}

	void reset(processor *pr) {
		pr->mJob = pr->mWork = pr->mAll = pr->buf = 0;
		pr->busy = false;
	}

	bool work(processor *pr, int time) {
		if (pr->mWork <= time) {
			pr->mWork = 0;
			pr->busy = false;
		}
		else {
			pr->mWork -= time;
		}

		return !pr->busy;
	}

	void prepare() {
		for (int i = 0; i < count; i++) {
			reset(&procs[i]);
		}
	}

	int count;
public:
	eld::vector<processor> procs;

	Procs() {
		count = 0;
	}

	Procs(int m) {
		this->count = m;
		procs.resize(m);
	}

	int size() {
		return count;
	}

	void resize(int m) {
		this->count = m;
		procs.resize(m);
	}

	int crit(int *var, Jobs &jobs, int set) {
		prepare();

		if (set == 0)
			return 0;
		int workTime = 0, minWork = 0, f = 0, completeJob = 0;
		int n = jobs.get_count();

		jobs.refresh();
		int nextJob = 0;
		while (true) {
			//if (nextJob < n) {
			for (int i = 0; i < count; i++)
				if (jobs.FindInFront(var[nextJob]) && procs[i].mWork == 0) {
				procs[i].mWork = jobs[var[nextJob] - 1];//[]
				procs[i].mJob = var[nextJob];
				nextJob++;
				if (nextJob == n)
					break;
				}
			//}


			minWork = jobs[0];//[]

			for (int i = 0; i < count; i++)
				if (procs[i].mWork > 0 && minWork > procs[i].mWork)
					minWork = procs[i].mWork;

			int res = 0;
			for (int i = 0; i < count; i++) {
				procs[i].buf += minWork;

				if (procs[i].mWork > 0) {
					procs[i].mWork -= minWork;
					procs[i].mAll += procs[i].buf;
					procs[i].buf = 0;

					if (procs[i].mWork == 0) {
						jobs.Complete(procs[i].mJob);

						completeJob++;
						if (completeJob == set) {
							res = i;
						}

					}
				}
				else if (procs[i].mWork < 0)
					std::cout << "\nProcNum Error!";
			}

			if (completeJob == set) {
				return procs[res].mAll;
			}
		}
	}

	int getMinTime() {
		int min = 0;
		for (int i = 0; i < count; i++) {
			if (procs[min].mAll > procs[i].mAll) {
				min = i;
			}
		}
		return min;
	}

	int getMaxTime() {
		return procs[maxTime()].mAll;
	}

	int getTime(int index) {
		return procs[index].mAll;
	}

	int getJobNum(int procIndex) {
		return procs[procIndex].mJob;
	}

	~Procs() {
	}
};