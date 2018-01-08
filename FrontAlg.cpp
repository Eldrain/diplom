#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include "FModuleFactory.cpp"

class FrontAlg : public AMethod {
private:
	std::string add_info_;
	sort::vector<IFModule*> modules_;
public:
	//vector<int> sol1, sol2, sol3;
	//int *sol1, *sol2, *sol3;
	//int f1, f2, f3;
	
	FrontAlg() {
		FModuleFactory::CreateSet(modules_);
		/*f1 = 0;
		f2 = 0;
		f3 = 0;
		sol1 = NULL;
		sol2 = NULL;
		sol3 = NULL;*/
	}

	void GetRes(std::ostringstream &res) {
		res << "\nFrontAlg (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.";
	}

	/*void PrintRes() {
		std::cout << "\nFrontAlg (" << n << " jobs): f = " << minF << "; time = " << time_ << " s.";
		PrintBest();
	}
	*/
	void Update() {
		/*sol1.resize(n);
		sol2.resize(n);
		sol3.resize(n);*/
		/*delete[] sol1;
		delete[] sol2;
		delete[] sol3;

		sol1 = new int[n];
		sol2 = new int[n];
		sol3 = new int[n];*/
	}

	void Start(Task &task, int set) {
		int f = 0;
		for (int i = 0; i < modules_.size(); i++) {
			modules_[i]->update(task.jobs);
			f = Alg(modules_[i], task, set);
			if (f < minF) {
				minF = f;
				ArrFunctions::copyArr(best_, var_, n);
				add_info_ = "FModule " + (i + 1);
			}
		}
		/*alg1(task, set);
		alg2(task, set);

		if (f1 > f2) {
			minF = f2;
			ArrFunctions::copyArr(best_, sol2, n);
			add_info_ = "met2";
		}
		else {
			minF = f1;
			ArrFunctions::copyArr(best_, sol1, n);
			add_info_ = "met1";
		}

		if (f1 = f2) {
			add_info_ = "met12";
		}*/
	}

	int Alg(IFModule *mod, Task &task, int set) {
		int index = 0;
		task.jobs.refresh();
		for (int i = 0; i < set; i++) {
			task.jobs.Complete(var_[i]);
		}
		for (int i = set; i < n; i++) {
			index = mod->next(task.jobs);
			task.jobs.Complete(index);
			var_[i] = index;
		}
		//std::cout << std::endl;
		//ArrFunctions::printArr(var_, n);
		return task.procs.crit(var_, task.jobs, n);
	}

	/*int alg2(Task &task, int set) {
		int index = 0;
		task.jobs.refresh();
		for (int i = set; i < n; i++) {
			index = task.jobs.FindMinInFront();
			task.jobs.Complete(index);
			sol2[i] = index;
		}
		f2 = task.procs.crit(sol2, task.jobs, n);

		return f2;
	}

	//��������� ������������ �������� �� ������ �� ������ ������� � ������������������ ������ �����������
	/*int alg3(Task &task) {
		int index = 0, diff = 0, minProc = 0;
		task.jobs.refresh();
		task.procs.prepare();

		index = task.jobs.front.findMin(task.jobs);
		sol3[0] = index;
		task.jobs.complete(index);
		for (int i = 1; i < jobCount - 1; i++) {
			minProc = task.procs.minTime();
			diff = task.procs.maxTime() - minProc;

			index = getMin(diff, task) - 1;
			sol3[i] = index + 1;
			task.jobs.complete(index + 1);

			task.procs.procs[minProc].allTime += task.jobs[index];
		}
		sol3[jobCount - 1] = 1;
		f3 = task.procs.crit(sol3, task.jobs, jobCount);
		return f3;
	}*/

	/*int getMin(int diff, Task &task) {
		int min = 0;// jobs->front.stack.first->info;

		for (int i = 0; i < n; i++) {
			var_[i] = abs(task.jobs[i] - diff);
			if (var_[i] < var_[min - 1] && task.jobs.FindInFront(i + 1))
				min = i + 1;
		}
		return min;
	}*/

	int abs(int a) {
		if(a > 0)
			return a;
		else
			return -a;
	}

	~FrontAlg() {
		FModuleFactory::Release(modules_);
		/*delete[] sol1;
		delete[] sol2;
		delete[] sol3;*/
	}
};