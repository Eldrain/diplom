#pragma once
#include "SortOut.cpp"
#include "AbBound.cpp"
#include "BBreal.cpp"
#include "FrontAlg.cpp"
#include "MTBB.cpp"

class MethodSet {
private:
	eld::vector<IMethod*> mets;
public:
	
	void addSortOut() {
		mets.increase(1);
		mets[mets.size() - 1] = new SortOut();
	}

	void addAbBound() {
		mets.increase(1);
		mets[mets.size() - 1] = new AbBound();
		((MarkMethod*)mets[mets.size() - 1])->setMark(new MinMingozzi(), new MaxMaxFront());
	}

	void addBaB() {
		mets.increase(1);
		mets[mets.size() - 1] = new BBreal();
		((MarkMethod*)mets[mets.size() - 1])->setMark(new MinMingozzi(), new MaxMaxFront());
	}

	void addFrontAlg() {
		mets.increase(1);
		mets[mets.size() - 1] = new FrontAlg();
	}

	void addMtBab() {
		mets.increase(1);
		mets[mets.size() - 1] = new MTBB();
	}
	
	Solution* Solve(int n, Task &task) {
		Solution *res = NULL;
		if ((n < mets.size()) && (n >= 0)) {
			res = mets[n]->Solve(task);
		}
		return res;
	}

	/* Solve task by each method in set */
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
	/*int SolveByMethod(int n, int m,  int method, std::string &results) {
		Generate(n, m, 50, 8);
		met_[method]->Solve(task);
		met_[method]->PrintRes();
		results = n + " jobs. Solved.";

		return 0;// met_[method]->GetMin();
	}

	void CreateBestMethod() {
		clear();
		met_.resize(1);
		initStat();
		met_[0] = new StatMethod(&stat[0], new MTBB(10));//new MTBB(10);
	}

	void CreateBaseSet() {
		clear();
		met_.resize(6);
		initStat();

		met_[0] = new StatMethod(&stat[0], new SortOut());//CreateStat<SortOut>(&stat[0]);
		met_[1] = new StatMethod(&stat[1], new BB(MarkFactory::CreateStatMarks(&stat[1]))); //CreateStatWithMarks<BB>(&stat[1]);
		met_[2] = new StatMethod(&stat[2], new BBreal(MarkFactory::CreateStatMarks(&stat[1]))); //CreateStatWithMarks<BBreal>(&stat[2]);
		met_[3] = new StatMethod(&stat[3], new FrontAlg()); //CreateStat<FrontAlg>(&stat[3]);
		met_[4] = new StatMethod(&stat[4], new NextMT<BB, MozMarks>()); //CreateStatNextMT<BB, MozMarks>(&stat[4]);//CreateStat<FastMS>(&stat[4]);
		met_[5] = new MTBB(5);
	}

	void CreateMTSet() {
		clear();
		met_.resize(3);
		initStat();

		met_[0] = new StatMethod(&stat[0], new FastMS());
		met_[1] = new StatMethod(&stat[1], new NextMT<BB, MozMarks>());
		met_[3] = new StatMethod(&stat[2], new MTBB(10));	
	}
	
	void CreateSortOutSet() {
		clear();
		met_.resize(3);
		initStat();

		met_[0] = new StatMethod(&stat[0], new SortOut());
		met_[1] = new StatMethod(&stat[1], new NextMT<BB, MozMarks>());
		met_[2] = new StatMethod(&stat[2], new MTBB(10));
	}
	/*
	void CreateBBSet() {
		clear();
		met_.resize(2);
		initStat();
		met_[0] = CreateMarks<BB, MozMarks>();
		met_[1] = CreateMarks<BBreal, MozMarks>();
	}

	void CreateMTSet() {
		clear();
		/*met_.resize(4);
		met_[0] = create<FastMS>();
		met_[1] = CreateNextMT<SortOut>();
		met_[2] = CreateNextMT<BB>();
		met_[3] = create<MTBB>();
	}

	void CreateEvrSet() {
		clear();
		met_.resize(2);
		initStat();
		met_[0] = CreateStat<FrontAlg>(&stat[0]);
		met_[1] = CreateStatWithMarks<Ant>(&stat[1]);
	}
	
	void ResizeTaskProcs(int m) {
		task.ResizeProcs(m);
	}

	void Generate(int n, int m, int maxTime, int retry) {
		task.ResizeProcs(m);
		Generator::GenerateTree(task, n, maxTime, retry);
	}

	void PrintJobs() {
		task.PrintJobs();
	}

	int GetCountMethod() {
		return met_.size();
	}

	void initStat() {
		delete[] stat;
		stat = new Statistics[met_.size()];
	}

	void PrintStat() {
		std::cout << "PrintStat() in Schedule";
		
		for (int i = 0; i < met_.size(); i++) {
			stat[i].print();
		}
	}

	//Delete set of methods
	void clear() {
		for (int i = 0; i < met_.size(); i++) {
			delete met_[i];
		}
		met_.clear();
	}*/

	~MethodSet() {
		for (int i = 0; i < mets.size(); i++) {
			delete mets[i];
		}
		mets.clear();
	}
};