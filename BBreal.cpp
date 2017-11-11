#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include "Tree.cpp"
#include "BBMarks.cpp"

class BBreal : public AMethod {
public:
	int countVar, *buf;
	Tree tree;
	BBMarks mark;

	void update() {
		AMethod::update();
		tree.init(n);
		mark.init(n);

		delete[] buf;
		buf = new int[n];
	}

	int solve(Task &task) {
		minF = 0;
		countVar = 0;

		n = task.n;
		update();
		for (int i = 0; i < n; i++)
			minF += task.jobs.jobs[i].time; // переопределенный оператор индекса. На самом деле возвращает jobs.время выполнения работы.
		ArrFunctions::clearArr(var, n);
		minF++; //для цепочки (для того, чтобы best заполнился хотя бы один раз

		int maximum = minF;
		tree.addInWave(var, maximum, maximum, 0);
		tree.addWave();
		//Stack<Tree::leaf>::elem *prsp = new Stack<Tree::leaf>::elem(*first);
		//tree.setBest(prsp);

		time = clock();
		minF = clip(0, maximum, task);
		time = (clock() - time) / 1000;

		int set = countSet(best, n);
		if (set < n) {
			mark.maxB(best, set, task);
			for (int i = set; i < n; i++)
				best[i] = buf[i];
		}
		return minF;
	}

	int clip(int set, int &maximum, Task &task) {
		/*bufTime = clock();
		if (!task.jobs.checkVar(var, set)) {
			timeCheck += (clock() - bufTime) / 1000;
			return minF;
		}
		timeCheck += (clock() - bufTime) / 1000;*/

		while (!tree.isEmpty()) {
			tree.findPrsp();
			tree.produce(task);
			tree.marks(mark, task);
			tree.cut(maximum);
			tree.addWave();
		}

		minF = tree.getMin();
		ArrFunctions::copyArr(best, tree.best->arr, n);

		return tree.getMin();
	}

	/*int minB(int *var, int set, Task &task) {
		task.procs.crit(var, task.jobs, set);

		int value = task.procs.adjustment(task.jobs.jobs[task.jobs.minTime()].time, n - set);

		return value;
	}

	int max(int *var, int set, Task &task) {
		int i = 0;
		task.jobs.refresh();

		for (; i < set; i++) {
			buf[i] = var[i];
			task.jobs.complete(var[i]);
		}

		int maxNum = 0;
		while (i < n) {
			maxNum = task.jobs.front.findMax(task.jobs);
			buf[i] = maxNum;
			i++;
			task.jobs.complete(maxNum);
		}

		//std::cout << std::endl << "\nbuffer: ";
		//printArr(buffer, n);
		return task.procs.crit(buf, task.jobs, n);
	}*/

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
		delete buf;
	}
};