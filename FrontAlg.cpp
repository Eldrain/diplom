#pragma once
#include "stdafx.h"
#include "AMethod.cpp"

class FrontAlg : public AMethod {
public:
	std::vector<int> sol1, sol2, sol3;
	int f1, f2, f3;

	FrontAlg() {
		f1 = 0;
		f2 = 0;
		f3 = 0;
	}

	void PrintRes() {
		std::cout << "\nFrontAlg (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.";
		PrintBest();
	}

	void Update() {
		sol1.resize(n);
		sol2.resize(n);
		sol3.resize(n);
	}

	void Start(Task &task) {
		alg1(task);
		alg2(task);

		if (f1 > f2) {
			minF = f2;
			best_ = sol2;
		}
		else {
			minF = f1;
			best_ = sol1;
		}
	}

	int alg1(Task &task) {
		int index = 0;
		task.jobs.refresh();

		for (int i = 0; i < n; i++) {
			index = task.jobs.FindMaxInFront();
			task.jobs.Complete(index);
			sol1[i] = index;
		}
		f1 = task.procs.crit(sol1, task.jobs, n);
		return f1;
	}

	int alg2(Task &task) {
		int index = 0;
		task.jobs.refresh();
		for (int i = 0; i < n; i++) {
			index = task.jobs.FindMinInFront();
			task.jobs.Complete(index);
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

	int getMin(int diff, Task &task) {
		int min = 0;// jobs->front.stack.first->info;

		for (int i = 0; i < n; i++) {
			var_[i] = abs(task.jobs[i] - diff);
			if (var_[i] < var_[min - 1] && task.jobs.FindInFront(i + 1))
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
	}
};