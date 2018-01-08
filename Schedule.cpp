#pragma once
#include "stdafx.h"
#include "SortOut.cpp"
#include "BB.cpp"
#include "BBreal.cpp"
#include "FrontAlg.cpp"
#include "MultiSearch.cpp"
#include "FastMS.cpp"
#include "NextMT.cpp"
#include "MTBB.cpp"
#include "Ant.cpp"
#include "StatMethod.cpp"

class Schedule {
public:
	class Generator {
	public:
		static void GenerateTree(Task &task, int n, int maxTime, int retry) {
			task.n = n;
			generateTree(task.jobs, n, maxTime, retry);
			RemoveRedundancy(task);
			task.jobs.PrintTimes();
		}

		static void GenerateChain(Task &task, int n, int maxTime) {
			task.n = n;
			generateChain(task.jobs, n, maxTime);
		}

		//minimaze graph of dependicies of jobs
		static void RemoveRedundancy(Task &task) {
			Stack<int>::Iterator *it = nullptr;
			Stack<int>::Iterator iterator;
			int n = 0;
			bool del = false;

			for (int i = task.n; i > 1; i--) {
				iterator.current_ = task.jobs.GetFollowIterator(i)->current_;
				del = false;
				do {
					if (del) {
						task.jobs.RemoveFollow(i, n);
						n = 0;
						del = !del;
					}
					it = task.jobs.GetFollowIterator(i);

					do {
						if (iterator.current_->info == it->current_->info) {
							continue;
						}
						if (FindPath(task, it->current_->info, iterator.current_->info)) {
							del = true;
							n = iterator.current_->info;
							break;
							
						}
					} while (it->get_next());
				} while (iterator.get_next());		

				if (del) {
					task.jobs.RemoveFollow(i, n);
					n = 0;
					del = !del;
				}
			}

		}

		//recursive method for find vertex with number == num
		static bool FindPath(Task &task, int from, int num) {
			Stack<int>::Iterator *i = task.jobs.GetFollowIterator(from);
			if (i == nullptr) {
				return false;
			}

			do {
				if (i->current_->info == num || FindPath(task, i->current_->info, num)) {
					return true;
				}	
			} while (i->get_next());

			return false;
		}
	private:
		static void generateTree(Jobs &jobs, int n, int maxTime, int retry) {
			jobs.clear();
			jobs.resize(n);

			int to = 0;
			for (int i = n - 1; i >= 0; i--) {
				jobs.SetJobTime(i + 1, rand() % maxTime + 1);

				if (i != 0)
					for (int j = 0; j < retry; j++) {
						to = rand() % i + 1;
						if (!jobs.FindInFollows(i + 1, to))
							jobs.AddJobFollow(i + 1, to);
					}
			}
			jobs.defineCountPrev();
			jobs.refresh();
		}

		static void generateChain(Jobs &jobs, int n, int maxTime) {
			jobs.clear();
			jobs.resize(n);

			for (int i = n - 1; i >= 0; i--) {
				jobs.SetJobTime(i + 1, rand() % maxTime + 1);

				if (i != 0)
					jobs.AddJobFollow(i + 1, i + 1);
			}
			jobs.defineCountPrev();
			jobs.refresh();
		}
	};
private:
	Task task;
	sort::vector<IMethod*> met_;
	Statistics *stat;
public:

	Schedule() {
		stat = NULL;
	}
	
	void Solve() {
		for (int i = 0; i < met_.size(); i++) {
			met_[i]->Solve(task);
			met_[i]->PrintRes();
		}
	}

	int SolveByMethod(int n, int m,  int method, std::string &results) {
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
	*/
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
	}

	~Schedule() {
		for (int i = 0; i < met_.size(); i++) {
			delete met_[i];
		}
		met_.clear();
		delete[] stat;
		//delete[] met_;
	}
};