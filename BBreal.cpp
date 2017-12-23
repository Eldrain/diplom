#pragma once
//#include "stdafx.h"
#include "MarkMethod.cpp"
#include "Tree.cpp"

class BBreal : public MarkMethod {
public:
	double timeClip, timeCrit, timeCheck, bufTime, minTime, maxTime;
	Tree tree;

	BBreal(Marks *m): MarkMethod(m) {}

	void GetRes(std::ostringstream &res) {
		res << "\nB&B (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
	}

	/*void PrintRes() {
		std::cout << "\nB&B (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}*/

	void Update() {
		tree.init(n);
		marks->init(n);
	}

	void Start(Task &task, int set) {
		int maximum = minF;
		tree.addInWave(var_, maximum, maximum, 0);
		tree.addWave();

		//timeCrit = timeCheck = bufTime = minTime = maxTime = 0;
		minF = clip(set, maximum, task);

		set = countSet(best_);
		
		if (set < n) {
			marks->maxB(best_, set, task);
			ArrFunctions::copyArr(best_, marks->GetBuf(), n);
		}
	}

	int clip(int set, int &maximum, Task &task) {
		while (!tree.isEmpty()) {
			tree.findPrsp();
			countVar+=tree.produce(task);
			tree.marks(*marks, task);
			//tree.printTree();
			tree.cut(maximum);
			tree.addWave();
			
		}

		minF = tree.getMin();
		ArrFunctions::copyArr(best_, tree.best->arr_, n);

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