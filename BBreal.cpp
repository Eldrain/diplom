#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include "Tree.cpp"
#include "BBMarks.cpp"
#include "MazMarks.cpp"

class BBreal : public AMethod {
public:
	int *buf;
	double timeClip, timeCrit, timeCheck, bufTime, minTime, maxTime;
	Tree tree;
	Marks *marks;

	BBreal() {
		marks = new MazMarks();
	}

	void update() {
		AMethod::update();
		tree.init(n);
		marks->init(n);

		delete[] buf;
		buf = new int[n];
	}

	int solve(Task &task) {
		minF = 0;

		n = task.n;
		update();
		for (int i = 0; i < n; i++)
			minF += task.jobs[i]; // ���������������� �������� �������. �� ����� ���� ���������� jobs.����� ���������� ������.
		clearArr(var, n);
		minF++;

		int maximum = minF;
		tree.addInWave(var, maximum, maximum, 0);
		tree.addWave();

		timeCrit = timeCheck = bufTime = minTime = maxTime = 0;
		time = clock();
		minF = clip(0, maximum, task);
		time = (clock() - time) / CLOCKS_PER_SEC;

		int set = countSet(best, n);
		
		if (set < n) {
			marks->maxB(best, set, task);
			int *buffer = marks->getBuf();
			for (int i = set; i < n; i++)
				best[i] = buffer[i];
		}
		return minF;
	}

	int clip(int set, int &maximum, Task &task) {

		while (!tree.isEmpty()) {
			tree.findPrsp();
			countVar+=tree.produce(task);
			tree.marks(*marks, task);
			tree.cut(maximum);
			tree.addWave();
		}

		minF = tree.getMin();
		ArrFunctions::copyArr(best, tree.best->arr, n);

		return tree.getMin();
	}

	int countSet(int *var, int n) {
		int set = 0;
		for (int i = 0; i < n; i++)
			if (var[i] == 0)
				return set;
			else
				set++;
		return set;
	}

	~BBreal() {
		delete[] buf;
		delete marks;
		marks = NULL;
	}
};