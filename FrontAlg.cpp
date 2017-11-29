#pragma once
//#include "stdafx.h"
#include "AMethod.cpp"

class FrontAlg : public AMethod {
public:
	int *sol1, *sol2, *sol3, f1, f2, f3;

	FrontAlg() {
		f1 = 0;
		f2 = 0;
		f3 = 0;
	}

	void update() {
		AMethod::update();
		sol1 = best;
		delete[] sol2;
		delete[] sol3;
		sol2 = new int[n];
		sol3 = new int[n];
	}

	int solve(Task &task) {
		n = task.n;
		update();
		time = clock();
		alg1(task);
		alg2(task);
		time = (clock() - time) / CLOCKS_PER_SEC;
		//alg3();
		if (f1 > f2)
			return f2;
		else
			return f1;
	}

	//��������� ������������ ������������� �� ������
	int alg1(Task &task) {
		int index = 0;
		task.jobs.refresh();

		for (int i = 0; i < n; i++) {
			index = task.jobs.front.findMax(task.jobs);
			task.jobs.complete(index);
			sol1[i] = index;
		}
		f1 = task.procs.crit(sol1, task.jobs, n);
		return f1;
	}

	//��������� ������������ ������������ �� ������
	int alg2(Task &task) {
		int index = 0;
		task.jobs.refresh();
		for (int i = 0; i < n; i++) {
			index = task.jobs.front.findMin(task.jobs);
			task.jobs.complete(index);
			sol2[i] = index;
		}
		f2 = task.procs.crit(sol2, task.jobs, n);

		return f2;
	}

	//��������� ������������ �������� �� ������ �� ������ ������� � ������������������ ������ �����������
	/*int alg3(Task &task) {
		int index = 0, diff = 0, minProc = 0;
		task.jobs.refresh();
		task.procs.prepare();

		index = task.jobs.front.findMin(task.jobs);
		sol3[0] = index;
		task.jobs.complete(index);
		for (int i = 1; i < jobCount - 1; i++) {
			minProc = task.procs.minTime();
			diff = task.procs.maxTime() - minProc;

			index = getMin(diff, task) - 1;
			sol3[i] = index + 1;
			task.jobs.complete(index + 1);

			task.procs.procs[minProc].allTime += task.jobs[index];
		}
		sol3[jobCount - 1] = 1;
		f3 = task.procs.crit(sol3, task.jobs, jobCount);
		return f3;
	}*/

	//��������� ������ � ���������� ����������� �������� ������� � ���.
	int getMin(int diff, Task &task) {
		int min = 0;// jobs->front.stack.first->info;

		for (int i = 0; i < n; i++) {
			var[i] = abs(task.jobs[i] - diff);
			if (var[i] < var[min - 1] && task.jobs.front.find(i + 1))
				min = i + 1;
		}
		return min;
	}

	int abs(int a) {
		if(a > 0)
			return a;
		else
			return -a;
	}

	void printBest1() {
		std::cout << std::endl << "Best sol1: ";
		for (int i = 0; i < n; i++)
			std::cout << sol1[i] << ", ";
	}

	void printBest2() {
		std::cout << std::endl << "Best sol2: ";
		for (int i = 0; i < n; i++)
			std::cout << sol2[i] << ", ";
	}

	void printBest3() {
		std::cout << std::endl << "Best sol3: ";
		for (int i = 0; i < n; i++)
			std::cout << sol3[i] << ", ";
	}

	~FrontAlg() {
		delete[] sol2;
		delete[] sol3;
		sol1 = NULL;
		sol2 = NULL;
		sol3 = NULL;
	}
};