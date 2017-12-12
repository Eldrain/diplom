#include "stdafx.h"
#include "SortOut.cpp"
#include "BB.cpp"
#include "BBreal.cpp"
#include "FrontAlg.cpp"
#include "MultiSearch.cpp"
#include "FastMS.cpp"
#define M 5

class Schedule {
private:
	Task task;
	sort::vector<AMethod*> met_;
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
		met_.resize(M);
		met_[0] = create<SortOut>();
		met_[1] = create<BB>();
		met_[2] = create<BBreal>();
		met_[3] = create<FrontAlg>();
		met_[4] = create<FastMS>();
	}

	void CreateFastSet() {
		clear();
		met_.resize(3);
		met_[0] = create<BB>();
		met_[1] = create<BBreal>();
		met_[2] = create<FastMS>();
	}

	void CreateSortOutSet() {
		clear();
		met_.resize(3);
		met_[0] = create<SortOut>();
		met_[1] = create<MultiSearch>();
		met_[2] = create<FastMS>();
	}

	void CreateBBSet() {
		clear();
		met_.resize(2);
		met_[0] = create<BB>();
		met_[1] = create<BBreal>();
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

	template<class T>
	AMethod* create() {
		return new T();
	}

	//Delete set of methods
	void clear() {
		for (int i = 0; i < met_.size(); i++) {
			delete met_[i];
		}
		met_.clear();
	}

	~Schedule() {
		for (int i = 0; i < M; i++) {
			delete met_[i];
		}
		met_.clear();
		//delete[] met_;
	}

	class Generator {
	public:
		static void GenerateTree(Task &task, int n, int maxTime, int retry) {
			task.n = n;
			generateTree(task.jobs, n, maxTime, retry);
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
};