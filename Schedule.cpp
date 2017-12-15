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
			task.jobs.PrintTimes();
		}

		static void GenerateChain(Task &task, int n, int maxTime) {
			task.n = n;
			generateChain(task.jobs, n, maxTime);
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
	sort::vector<AMethod*> met_;
	Statistics *stat;
public:

	void Solve() {
		for (int i = 0; i < met_.size(); i++) {
			met_[i]->Solve(task);
			met_[i]->PrintRes();
		}
	}

	void CreateBaseSet() {
		/*delete[] met_;
		met_ = new AMethod*[M];*/
		clear();
		met_.resize(5);
		initStat();

		met_[0] = CreateStat<SortOut>(&stat[0]);
		met_[1] = CreateWithMarks<BB>(&stat[1]);
		met_[2] = CreateWithMarks<BBreal>(&stat[2]);

		//TODO: DELETE KOSTYLIIIIIIIIII!!!!!!!!!!!!!!!!!!
		/*delete ((BB*)met_[1])->marks;
		((BB*)met_[1])->marks = MarkFactory::CreateStatMarks(&stat[1]);
		delete ((BBreal*)met_[2])->marks;
		((BBreal*)met_[2])->marks = MarkFactory::CreateStatMarks(&stat[1]);*/
		//============================================================================
		met_[3] = CreateStat<FrontAlg>(&stat[3]);
		met_[4] = CreateStat<FastMS>(&stat[4]);
		
	}

	void CreateFastSet() {
		clear();
		met_.resize(3);
		met_[0] = create<BB>();
		met_[1] = create<BBreal>();
		met_[2] = create<MTBB>();
		initStat();
	}

	void CreateSortOutSet() {
		clear();
		met_.resize(3);
		met_[0] = create<SortOut>();
		met_[1] = create<MultiSearch>();
		met_[2] = create<FastMS>();
		initStat();
	}

	void CreateBBSet() {
		clear();
		met_.resize(2);
		initStat();
		met_[0] = create<BB>();
		met_[1] = create<BBreal>();
	}

	void CreateMTSet() {
		clear();
		met_.resize(4);
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
		met_[1] = CreateStat<Ant>(&stat[1]);
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
		for (int i = 0; i < met_.size(); i++) {
			stat[i].print();
		}
	}

	template<class T>
	AMethod* create() {
		return new T();
	}

	template<class T>
	AMethod* CreateNextMT() {
		return new NextMT<T>();
	}

	template<class T>
	AMethod* CreateStat(Statistics *st) {
		return new StatMethod<T>(st);
	}

	//TODO: DELETE!!!!!!!!!!!!!
	template<class T>
	AMethod* CreateWithMarks(Statistics *st) {
		return new StatMethod<T>(st, new T(st));
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