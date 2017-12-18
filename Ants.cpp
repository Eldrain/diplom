#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include "Tree.cpp"
#include "MarkFactory.cpp"

class Ants /*: public AMethod*/ {
public:
	/*Tree *tree;
	Marks *marks;

	Ants() {
		marks = MarkFactory::CreateBestMarks();
	}

	Ants(Statistics *st) {
		marks = MarkFactory::CreateStatMarks(st);
	}

	void PrintRes() {
		std::cout << "\nB&B (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}

	void Update() {
		delete[] tree;
		tree = new Tree[n - 1];
		for (int i = 0; i < n - 1; i++) {
			tree[i].init(n);
		}
		marks->init(n);
	}

	void Start(Task &task) {
		int maximum = marks->maxB(var_, 0, task);
		tree[0].addInWave(var_, marks->minB(var_, 0, task), maximum, 0);
		tree[0].addWave();

		//timeCrit = timeCheck = bufTime = minTime = maxTime = 0;
		minF = StartAnts(0, maximum, task);

		int set = countSet(best_);

		if (set < n) {
			marks->maxB(best_, set, task);
			ArrFunctions::copyArr(best_, marks->GetBuf(), n);
		}
	}

	int StartAnts(Task &task) {
		while (!tree.isEmpty()) {
			tree.findPrsp();
			countVar += tree.produce(task);
			tree.marks(*marks, task);
			//tree.printTree();
			tree.cut(maximum);
			tree.addWave();

		}

		minF = tree.getMin();
		ArrFunctions::copyArr(best_, tree.best->arr_, n);

		return tree.getMin();
	}

	int ant() {
		int step = 0;
		if ()
	}

	~Ants() {
		delete marks;
	}*/
};