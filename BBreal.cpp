#pragma once
#include "stdafx.h"
#include "MarkMethod.cpp"
#include "Tree.cpp"

class BBreal : public MarkMethod {
public:
	double timeClip, timeCrit, timeCheck, bufTime, minTime, maxTime;
	Tree tree;

	BBreal(): MarkMethod(2, "Bounds&Branches") {}


	void Update() {
		tree.init(n);
		delete[] buf;
		buf = new int[n];
	}

	void Start(Task &task, int set) {
		int maximum = minF;
		tree.addInWave(var, maximum, maximum, 0);
		tree.addWave();

		//timeCrit = timeCheck = bufTime = minTime = maxTime = 0;
		minF = clip(set, maximum, task);

		set = countSet(best);
		
		if (set < n) {
			max->bound(best, set, task, buf);
			ArrFunctions::copyArr(best, buf, n);
		}
	}

	int clip(int set, int &maximum, Task &task) {
		while (!tree.isEmpty()) {
			tree.findPrsp();
			countVar+=tree.produce(task);
			tree.marks(max, min, buf, task);
			tree.cut(maximum);
			tree.addWave();
			
		}

		minF = tree.getMin();
		ArrFunctions::copyArr(best, tree.best->arr_, n);

		return tree.getMin();
	}

	int countSet(int *var) {
		int set = 0;
		for (int i = 0; i < n; i++)
			if (var[i] == 0)
				return set;
			else
				set++;
		return set;
	}

	int countSet(vector<int> &var) {
		int set = 0;
		for (int i = 0; i < n; i++)
			if (var[i] == 0)
				return set;
			else
				set++;
		return set;
	}

	~BBreal() {
	}
};