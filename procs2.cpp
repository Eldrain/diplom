#pragma once
#include "stdafx.h"
#include "relations.cpp"

class processor {
public:
	class proc {
	public:
		int nowJob, workTime, bufTime, allTime;
		
		proc() {
			clear();
		}
		void clear() {
			nowJob = 0;
			workTime = 0;
			bufTime = 0;
			allTime = 0;
		}
	};

	int m, n, *times;
	proc *procs;
	relations relat, rel;

	processor() {
		m = 0;
	}

	processor(int m, int n, int *times, relations &rel) {
		this->m = m;
		this->n = n;
		procs = new proc[m];
		this->times = times;
		relat = rel;
	}

	void copy(int *arr1, int *arr2, int n) {
		for (int i = 0; i < n; i++) 
			arr1[i] = arr2[i];	
	}

	int crit(int *arr1) {
		int workTime = 0, minWork = 0, getJob = 0, f = 0, completeJob = 0;
		int *arr = new int[n];

		rel = relat;
		copy(arr, arr1, n); // Костыль
		readyProcs();

		relations::job *nowJob = NULL;
		while (true) {
			for (int i = 0; i < m; i++)
				if (procs[i].workTime == 0 && getJob < n) {
				nowJob = rel.packet.find(arr[getJob]);
				if (nowJob) {
					procs[i].workTime = times[nowJob->n - 1];
					procs[i].nowJob = nowJob->n;
					getJob++;
				}
				}

			minWork = times[0];

			for (int i = 0; i < m; i++)
				if (procs[i].workTime > 0 && minWork > procs[i].workTime)
					minWork = procs[i].workTime;

			for (int i = 0; i < m; i++) {
				procs[i].allTime += minWork;

				if (procs[i].workTime > 0) {
					procs[i].workTime -= minWork;
					if (procs[i].workTime == 0) {
						rel.complete(procs[i].nowJob);
						completeJob++;
						if (completeJob == n) {
							delete arr;
							return procs[i].allTime;
						}
					}
				}
				else if (procs[i].workTime < 0)
					std::cout << "\nProcNum Error!";
			}
		}
	}

	void procsTime(int *arr, int set) {
		int workTime = 0, minWork = 0, getJob = 0, f = 0, completeJob = 0;
		
		rel = relat;
		readyProcs();
		if (set == 0)
			return;

		relations::job *nowJob = NULL;
		while (true) {
			for (int i = 0; i < m; i++)
				if (procs[i].workTime == 0 && getJob < n) {
				nowJob = rel.packet.find(arr[getJob]);
				if (nowJob) {
					procs[i].workTime = times[nowJob->n - 1];
					procs[i].nowJob = nowJob->n;
					getJob++;
				}
				}

			minWork = times[0];

			for (int i = 0; i < m; i++)
				if (procs[i].workTime > 0 && minWork > procs[i].workTime)
					minWork = procs[i].workTime;

			for (int i = 0; i < m; i++) {
				if (procs[i].workTime > 0) {
					procs[i].allTime += minWork + procs[i].bufTime;
					procs[i].bufTime = 0;
					procs[i].workTime -= minWork;
					if (procs[i].workTime == 0) {
						rel.complete(procs[i].nowJob);
						completeJob++;
						if (completeJob == set)
							return;
					}
				}
				else {
					procs[i].bufTime += minWork;
					if (procs[i].workTime < 0)
						std::cout << "\nProcNum Error!";
				}
			}
		}
	}

	void readyProcs() {
		for (int i = 0; i < m; i++)
			procs[i].clear();
	}

	void clearArr(int *arr, int n) {
		n--;
		while (n != -1) {
			arr[n] = 0;
			n--;
		}
	}
	~processor() {
		delete procs;
	}
};