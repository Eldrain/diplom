#pragma once
#include "stdafx.h"
#include "Jobs.cpp"
#include "processor.cpp"

class Procs {
private:
	//IValue *value;
	int count;
public:
	sort::vector<processor> procs;

	Procs() {
		count = 0;
		//value = new FirstValue();
		//procs = NULL;
	}

	Procs(int m) {
		this->count = m;
		procs.resize(m);
		//value = new FirstValue();
		//procs = new processor[m];
	}

	void resize(int m) {
		this->count = m;
		procs.resize(m);
		/*delete procs;
		procs = new processor[m];*/
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

	//Set count jobs in schedule with duration == jobTime. It's for calculate SimpleMin mark
	int adjustment(int jobTime, int count) {
		int minNum = 0, maxNum = 0;

		while (count != 0) {
			for (int i = 0; i < this->count; i++)
				if (procs[i].mAll < procs[minNum].mAll)
					minNum = i;
			procs[minNum].mAll += jobTime;
			count--;
		}

		for (int i = 0; i < this->count; i++)
			if (procs[i].mAll > procs[maxNum].mAll)
				maxNum = i;
		return procs[maxNum].mAll;
	}

	int MinBusy() {
		int min = 0;
		for (int i = 0; i < count; i++)
			if (procs[min].mAll > procs[i].mAll)
				min = i;
		return min;
	}

	//������ ���������� � ������������ ����������
	int maxTime() {
		int max = 0;
		for (int i = 0; i < count; i++)
			if (procs[max].mAll < procs[i].mAll)
				max = i;
		return max;
	}

	int GetMaxTime() {
		return procs[maxTime()].mAll;
	}

	int GetTime(int index) {
		return procs[index].mAll;
	}
	
	void prepare() {
		for (int i = 0; i < count; i++)
			procs[i].reset();
	}

	int getCount() {
		return count;
	}

	~Procs() {
		//delete[] procs;
	}
};