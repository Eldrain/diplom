#pragma once
//#include "stdafx.h"
#include "MarkMethod.cpp"
#include "Tree.cpp"

class Ant : public MarkMethod {
private:
	Tree tree;
	int count_;
public:
	Ant(Marks *marks) : MarkMethod(marks) {
		count_ = 1;
	}

	void GetRes(std::ostringstream &res) {
		res << "\nAnt (" << count_ << " ant; " << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
	}

	void Update() {
	}

	/*void PrintRes() {
		std::cout << "\nAnt (" << count_ << " ant; " << n << " jobs): f = " << minF << "; time = " << time_ << " s.; countVar = " << countVar;
		PrintBest();
	}*/

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