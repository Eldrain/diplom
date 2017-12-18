#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include "Tree.cpp"
#include "MarkFactory.cpp"

class Ant : public AMethod {
private:
	Tree tree;
	int count_;
public:
	Marks * marks;

	Ant() {
		count_ = 1;
		marks = MarkFactory::CreateBestMarks();
	}

	void Update() {
	}

	void PrintRes() {
		std::cout << "\nAnt (" << count_ << " ant; " << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}

	void Start(Task &task, int set) {		
		tree.init(n);
		tree.addInWave(var_, 0, 0, set);
		tree.addWave();
		tree.findPrsp();

		int step = n - set - 1;

		while (step != 0) {
			tree.produce(task);
			tree.addWave();
			tree.findPrsp();
			tree.SavePrsp();
			step--;
		}

		ArrFunctions::copyArr(best_, tree.prsp->arr_, n);
		best_[n - 1] = 1;
		minF = task.procs.crit(best_, task.jobs, n);
	}

	virtual ~Ant() {

	}
};