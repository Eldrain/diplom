#pragma once
#include "stdafx.h"
#include "Jobs.cpp"

class Procs {
private:
	int count;
public:
	class processor {
	public:
		int workTime, job, bufTime, allTime;

		processor() {
			prepare();
		}
		
		void prepare() {
			workTime = allTime = bufTime = 0;
			job = 0;
		}
	};

	sort::vector<processor> procs;

	Procs() {
		count = 0;
		//procs = NULL;
	}

	Procs(int m) {
		this->count = m;
		procs.resize(m);
		//procs = new processor[m];
	}

	void resize(int m) {
		this->count = m;
		procs.resize(m);
		/*delete procs;
		procs = new processor[m];*/
	}

	int crit(int *arr, Jobs &jobs, int set) {
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
					if (jobs.FindInFront(arr[nextJob]) && procs[i].workTime == 0) {
						procs[i].workTime = jobs[arr[nextJob] - 1];//[]
						procs[i].job = arr[nextJob];
						nextJob++;
						if (nextJob == n)
							break;
					}
			//}


			minWork = jobs[0];//[]

			for (int i = 0; i < count; i++)
				if (procs[i].workTime > 0 && minWork > procs[i].workTime)
					minWork = procs[i].workTime;

			for (int i = 0; i < count; i++) {
				procs[i].bufTime += minWork;

				if (procs[i].workTime > 0) {
					procs[i].workTime -= minWork;
					procs[i].allTime += procs[i].bufTime;
					procs[i].bufTime = 0;

					if (procs[i].workTime == 0) {
						jobs.Complete(procs[i].job);

						completeJob++;
						if (completeJob == set)
							return procs[i].allTime;

					}
				}
				else if (procs[i].workTime < 0)
					std::cout << "\nProcNum Error!";
			}
		}
	}

	//Complete set jobs and returns criterion value. In pointer save index of processor, where was
	/*int CritWithProcPointer(int *arr, Jobs &jobs, int set, int &pointer) {
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
				if (jobs.FindInFront(arr[nextJob]) && procs[i].workTime == 0) {
					procs[i].workTime = jobs[arr[nextJob] - 1];//[]
					procs[i].job = arr[nextJob];
					nextJob++;
					if (nextJob == n)
						break;
				}
			//}


			minWork = jobs[0];//[]

			for (int i = 0; i < count; i++)
				if (procs[i].workTime > 0 && minWork > procs[i].workTime)
					minWork = procs[i].workTime;

			for (int i = 0; i < count; i++) {
				procs[i].bufTime += minWork;

				if (procs[i].workTime > 0) {
					procs[i].workTime -= minWork;
					procs[i].allTime += procs[i].bufTime;
					procs[i].bufTime = 0;

					if (procs[i].workTime == 0) {
						jobs.Complete(procs[i].job);

						completeJob++;
						if (completeJob == set)
							return procs[i].allTime;

					}
				}
				else if (procs[i].workTime < 0)
					std::cout << "\nProcNum Error!";
			}
		}
	}*/

	//������(adjustment - ��������). ������� ������������ ��� �������� ������ ������: ���������� � ������
	//������� ���������� ��� k ����� � ����������� �������������
	int adjustment(int jobTime, int count) {
		int minNum = 0, maxNum = 0;

		while (count != 0) {
			for (int i = 0; i < this->count; i++)
				if (procs[i].allTime < procs[minNum].allTime)
					minNum = i;
			procs[minNum].allTime += jobTime;
			count--;
		}

		for (int i = 0; i < this->count; i++)
			if (procs[i].allTime > procs[maxNum].allTime)
				maxNum = i;
		return procs[maxNum].allTime;
	}

	//������ ���������� � ����������� ����������
	int minTime() {
		int min = 0;
		for (int i = 0; i < count; i++)
			if (procs[min].allTime > procs[i].allTime)
				min = i;
		return min;
	}

	//������ ���������� � ������������ ����������
	int maxTime() {
		int max = 0;
		for (int i = 0; i < count; i++)
			if (procs[max].allTime < procs[i].allTime)
				max = i;
		return max;
	}
	
	void prepare() {
		for (int i = 0; i < count; i++)
			procs[i].prepare();
	}

	int getCount() {
		return count;
	}

	~Procs() {
		//delete[] procs;
	}
};