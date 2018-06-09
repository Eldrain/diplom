#pragma once
#include "SortOut.cpp"
#include "AbBound.cpp"
#include "BBreal.cpp"
#include "FrontAlg.cpp"
#include "MTBB.cpp"

class MethodSet {
private:
	eld::vector<IMethod*> mets;
	eld::vector<Stats*> stats;
	MarkFactory markFactory;
public:
	
	void addSortOut(bool statistics) {
		mets.increase(1);
		int index = mets.size() - 1;
		mets[index] = new SortOut();

		stats.increase(1);
		if (statistics) {
			stats[index] = new Stats();
			mets[index]->setStats(stats[index]);
		}
		else {
			stats[index] = NULL;
		}
	}

	// Alpha-Beta algorythm
	void addAbBound(Mark *min, Mark *max, bool statistics) {
		mets.increase(1);
		mets[mets.size() - 1] = new AbBound();

		int index = mets.size() - 1;
		stats.increase(1);
		if (statistics) {
			stats[index] = new Stats();
			Mark *statMin = markFactory.createStatMark(stats[index], min, false);
			Mark *statMax = markFactory.createStatMark(stats[index], max, true);
			
			mets[index]->setStats(stats[index]);
			((MarkMethod*)mets[index])->setMark(statMin, statMax);
		}
		else {
			stats[index] = NULL;
			((MarkMethod*)mets[index])->setMark(min, max);
		}
		
	}

	// Bound & Branches
	void addBaB(Mark *min, Mark *max, bool statistics) {
		mets.increase(1);
		mets[mets.size() - 1] = new BBreal();

		int index = mets.size() - 1;
		stats.increase(1);
		if (statistics) {
			stats[index] = new Stats();
			Mark *statMin = markFactory.createStatMark(stats[index], min, false);
			Mark *statMax = markFactory.createStatMark(stats[index], max, true);

			mets[index]->setStats(stats[index]);
			((MarkMethod*)mets[index])->setMark(statMin, statMax);
		}
		else {
			stats[index] = NULL;
			((MarkMethod*)mets[index])->setMark(min, max);
		}
	}

	// Front algorythm
	void addFrontAlg(bool statistics) {
		mets.increase(1);
		mets[mets.size() - 1] = new FrontAlg();

		int index = mets.size() - 1;
		stats.increase(1);
		if (statistics) {
			stats[index] = new Stats();
			mets[index]->setStats(stats[index]);
		}
		else {
			stats[index] = NULL;
		}
	}

	// Multi-Thread Alpha-Beta algorythm
	void addMtBab(bool statistics) {
		mets.increase(1);
		mets[mets.size() - 1] = new MTBB();

		int index = mets.size() - 1;
		stats.increase(1);
		if (statistics) {
			stats[index] = new Stats();
			mets[index]->setStats(stats[index]);
		}
		else {
			stats[index] = NULL;
		}
	}
	
	Solution* Solve(int n, Task &task) {
		Solution *res = NULL;
		if ((n < mets.size()) && (n >= 0)) {
			res = mets[n]->Solve(task);
		}
		return res;
	}

	/* Solve task by each method in set.
	 * callback[in] - is inner iterator */
	void solve(void callback(Solution*), Task &task) {
		Solution *res = NULL;
		if (mets.size() != 0) {
			for (int i = 0; i < mets.size(); i++) {
				delete res;
				res = mets[i]->Solve(task);
				callback(res);
			}
		}
		else {
			std::cout << "Methods in MethodSet is not created";
		}
	}

	void printStats() {
		std::cout << std::endl << "**************** Statistics ****************";
		for (int i = 0; i < stats.size(); i++) {
			std::cout << std::endl << (i + 1) << ": ";

			if (stats[i] != NULL) {
				std::cout << std::endl;
				stats[i]->print();
			}
			else {
				std::cout << "NULL";
			}
		}
	}

	~MethodSet() {
		for (int i = 0; i < mets.size(); i++) {
			delete mets[i];
			delete stats[i];
		}
		mets.clear();
		stats.clear();
	}
};