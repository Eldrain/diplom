#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include "Tree.cpp"
#include "MarkFactory.cpp"

class BBreal : public AMethod {
public:
	std::vector<int> buf;
	double timeClip, timeCrit, timeCheck, bufTime, minTime, maxTime;
	Tree tree;
	Marks *marks;

	BBreal() {
		marks = MarkFactory::CreateBestMarks();
	}

	void PrintRes() {
		std::cout << "\nB&B (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}

	void Update() {
		tree.init(n);
		marks->init(n);
		buf.resize(n);
	}

	void Start(Task &task) {
		int maximum = minF;
		tree.addInWave(var_, maximum, maximum, 0);
		tree.addWave();

		//timeCrit = timeCheck = bufTime = minTime = maxTime = 0;
		minF = clip(0, maximum, task);

		int set = countSet(best_, n);
		
		if (set < n) {
			marks->maxB(best_, set, task);
			std::vector<int> &buffer = marks->GetBuf();
			best_ = buffer;
		}
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
		best_ = tree.best->arr_;

		return tree.getMin();
	}

	int countSet(std::vector<int> &var, int n) {
		int set = 0;
		for (int i = 0; i < n; i++)
			if (var[i] == 0)
				return set;
			else
				set++;
		return set;
	}

	~BBreal() {
		delete marks;
		marks = NULL;
	}
};