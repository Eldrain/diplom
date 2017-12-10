#include "stdafx.h"
#include "SortOut.cpp"
#include "BB.cpp"
#include "BBreal.cpp"
#include "FrontAlg.cpp"
#include "MultiSearch.cpp"
#define M 5

class Schedule {
private:
	Task task;
	AMethod **met_;
public:

	void Solve() {
		for (int i = 0; i < M; i++) {
			met_[i]->Solve(task);
			met_[i]->PrintRes();
		}
	}

	void CreateBaseSet() {
		delete[] met_;
		met_ = new AMethod*[M];
		met_[0] = create<SortOut>();
		met_[1] = create<BB>();
		met_[2] = create<BBreal>();
		met_[3] = create<FrontAlg>();
		met_[4] = create<MultiSearch>();
	}

	void SetProcsCount(int m) {
		task.createProcs(m);
	}

	void Generate(int n, int maxTime, int retry) {
		task.n = n;
		Generator::generateTree(task.jobs, n, maxTime, retry);
	}

	void PrintJobs() {
		task.PrintJobs();
	}

	template<class T>
	AMethod* create() {
		return new T();
	}

	~Schedule() {
		for (int i = 0; i < M; i++) {
			delete met_[i];
		}
		delete[] met_;
	}

	class Generator {
	public:
		static void generateTree(Jobs &jobs, int n, int maxTime, int retry) {
			jobs.clear();
			jobs.SetCount(n);

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

		void generateChain(Jobs &jobs, int n, int maxTime) {
			jobs.clear();
			jobs.SetCount(n);

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