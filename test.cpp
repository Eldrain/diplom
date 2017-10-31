#pragma once
#include "stdafx.h"
#include "Task.cpp"
#include "SortOut.cpp"
#include "BB.cpp"
#include "FrontAlg.cpp"
#include "BBreal.cpp"
#include <ctime>

using namespace std;
class test {
public:
	test() {
		srand(time(0));
		
	}

	void timeTest(int startN, int finishN, int m, int maxTime, int retry, Task &task) {
		task.createProcs(m);
		AMethod *a = new BBreal;
		SortOut sOut;
		BB clip;
		FrontAlg front;
		int opt = 0;

		for (int i = startN; i < finishN + 1; i++) {		
			generateTree(task.jobs, i, maxTime, retry);
			task.n = task.jobs.getCount();
			task.jobs.print();
			cout << endl << endl << i << " JOBS:\nTimes: ";
			for (int j = 0; j < i; j++)
				cout << task.jobs[j] << ", ";
			

			opt = sOut.solve(task);
			cout << endl << "SortOut: f = " << opt;
			sOut.printRes();
			cout << "\ncountVar = " << sOut.countVar << "; timeSO: " << sOut.timeSO << " s.";

			cout << endl << "Clip: f = " << clip.solve(task);
			clip.printRes();
			cout << "\ncountVar = " << clip.countVar << "; time: " << clip.timeClip << " s.";
			//cout << "\nРазличий в перестановках: " << compare(sOut., clip.best, i + 1);

			cout << endl << "BB: f = " << a->solve(task);
			a->printRes();
			//cout << "\ncountVar = " << a->countVar << "; time: " << clip.timeClip << " s.";

			front.solve(task);
			cout << endl << "FrontAlg: ";
			cout << endl << "f1 = " << front.f1 << "\nОценка1 = " << ((double)front.f1 - opt)/opt * 100 << " %.";
			front.printBest1();
			cout << endl << "f2 = " << front.f2 << "\nОценка2 = " << ((double)front.f2 - opt) / opt * 100 << " %.";
			front.printBest2();
			/*cout << endl << "f3 = " << front.f3 << "\nОценка3 = " << ((double)front.f3 - opt) / opt * 100 << " %.";
			front.printBest3();*/
		}
	}

	void testFront(int startN, int finishN, int m, int maxTime, int retry, Task &task) {
		task.createProcs(m);
		FrontAlg front;

		for (int i = startN - 1; i < finishN; i++) {
			cout << endl << endl << i + 1 << " JOBS:";

			generateTree(task.jobs, i + 1, maxTime, retry);
			task.n = task.jobs.getCount();
			front.solve(task);
			cout << endl << "FrontAlg: ";
			cout << endl << "f1 = " << front.f1;
			//front.printBest1();
			cout << endl << "f2 = " << front.f2 << "\nРазличий с 1-ой = " << compare(front.sol1, front.sol2, i + 1);
			//front.printBest2();
			cout << endl << "f3 = " << front.f3 << "\nРазличий с 1-ой = " << compare(front.sol1, front.sol3, i + 1);
			cout << endl << "Различий со 2-ой = " << compare(front.sol2, front.sol3, i + 1);
			//front.printBest3();
		}
	}
	//Возвращает число разных элементов в массивах
	int compare(int *arr1, int *arr2, int len) {
		int count = 0;

		for (int i = 0; i < len; i++)
			if (arr1[i] != arr2[i])
				count++;
		return count;
	}

	void generateTree(Jobs &jobs, int n, int maxTime, int retry) {
		jobs.clear();
		jobs.create(n);

		int to = 0;
		for (int i = n - 1; i >= 0; i--) {
			jobs.jobs[i].time = rand() % maxTime + 1;

			if(i != 0)
				for (int j = 0; j < retry; j++) {
					to = rand() % i + 1;
					if(!jobs.jobs[i].follow.find(to))
						jobs.jobs[i].follow.push(to);
				}
			//if(i != n - 1)
			//	jobs.jobs[i].countPrev = 1;
		}
		jobs.defineCountPrev();
		jobs.refresh();
		//jobs.print();
	}

	void generateChain(Jobs &jobs, int n, int maxTime) {
		jobs.clear();
		jobs.create(n);

		for (int i = n - 1; i >= 0; i--) {
			jobs.jobs[i].time = rand() % maxTime + 1;

			if (i != 0)
				jobs.jobs[i].follow.push(i);
			//if(i != n - 1)
			//	jobs.jobs[i].countPrev = 1;
		}
		jobs.defineCountPrev();
		jobs.refresh();
		jobs.print();
	}

	/*void test_procsTime(int *var, processor proc) {
		std::cout << "\ntest_procsTime: ";
		printArr(var, proc.n);
		std::cout << "\nf = " << proc.crit(var);

	}*/

	void printArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << ", ";
	}
};