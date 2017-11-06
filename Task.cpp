#pragma once
#include "stdafx.h"
#include "IOFile.cpp"

class Task {
private:
	
	IOFile file;
public:
	int n, m;
	Jobs jobs;
	Procs procs;
	
	Task() {
		m = 0;
		n = 0;
	}

	Task(string filename) {
		loadTask(filename);
	}

	void loadTask(string filename) {
		file.loadData(jobs, procs, filename);
		n = jobs.getCount();
		m = procs.getCount();
	}

	void createProcs(int m) {
		this->m = m;
		procs.create(m);
	}

	int getTime(int jobNum) {
		return jobs.jobs[jobNum].time;
	}
};
	/*bool checkVar(int *var, int set) {
		helpRel = rel;
		//helpRel.print();
		relations::job *nowJob = NULL;
		for (int j = 0; j < set; j++) 
			if (!helpRel.complete(var[j]))
				return false;
		
		return true;
	}

	int mVG() {
		int *var = new int[n], maximum = 0;
		clearArr(var, n);
		
		maximum = sumArr(times, n);
		
		countVar = 0;
		minF = maximum;
		timeMVG = clock();
		mVG(var, 0, maximum);
		timeMVG = (clock() - timeMVG) / 1000;
		delete var;

		return minF;
	}

	int sumArr(int *arr, int n) {
		int sum = 0;
		for (int i = 0; i < n; i++)
			sum += arr[i];

		return sum;
	}

	void test() {
		proc.procsTime(bestSO, n);
		std::cout << "\nprocsTime: ";
		for (int i = 0; i < m; i++)
			std::cout << std::endl << i + 1 << " = " << proc.procs[i].allTime;
	}

	int mVG(int *var, int set, int &maximum) {
		
		//std::cout << std::endl;
		//printArr(var, n);	

		countVar++;
		if (set < n) {
			int j = 0;
			for (int i = 0; i < n; i++) {
				j = 0;
				while (var[j] != 0)
					if (var[j] == i + 1)
						break;
					else
						j++;
				if (j == set) {
					var[set] = i + 1;
					if (!checkVar(var, set + 1)) {
						var[set] = 0;
						continue;
					}
					int mx = max(var, set + 1), mn = min(var, set + 1);

					if (mx < maximum)
						maximum = mx;
					if (mn == mx) {
						if (mn < minF) {
							minF = mn;
							for (int i = 0; i < n; i++)
								bestMVG[i] = var[i];
						}
						//mVG(var, set + 1, maximum);
					} else if (mn <= maximum)
						mVG(var, set + 1, maximum);

					var[set] = 0;
				}
			}
		} else {
			int f = 0, j = 0;
			f = proc.crit(var);
			//std::cout << "\nf = " << f;
			if (f < minF) {
				minF = f;
				for (int i = 0; i < n; i++)
					bestMVG[i] = var[i];
			}
		}
		return minF;
	}

	int min(int *var, int set) {
		proc.procsTime(var, set);
		//std::cout << std::endl << "var: ";
		//printArr(var, n);
		//std::cout << std::endl << "buffer: ";
		//printArr(buffer, n);
		int maxDur = 0, minDur = times[0];

		for (int i = 0; i < m; i++) {
			if (proc.procs[i].allTime > maxDur)
				maxDur = proc.procs[i].allTime;
			if (proc.procs[i].allTime < minDur)
				minDur = proc.procs[i].allTime;
		}

		int maxJob = 0, i = 0;
		while (true) {
			for (i = 0; i < set; i++)
				if (var[i] == maxJob) {
				maxJob++;
				break;
				}
			if (i == set)
				break;
		}

		if (minDur + times[maxJob] > maxDur)
			return minDur + times[maxJob];
		else
			return maxDur;
	}

	int max(int *var, int set) {
		int i = 0, j = 0, k = 0;
		helpRel = rel;

		for (; i < set; i++) {
			buffer[i] = var[i];
			helpRel.complete(var[i]);
		}
		relations::pack::elem *nowPack = helpRel.packet.first;
		relations::job *nowJob = NULL;

		int maxTime = 0, num = 0;
		while (nowPack) {
			maxTime = 0;
			while (nowPack) {
				if (maxTime < times[nowPack->now->n - 1]) {
					maxTime = times[nowPack->now->n - 1];
					num = nowPack->now->n;
				}
				nowPack = nowPack->next;
			}
			buffer[i] = num;
			i++;
			helpRel.complete(num);
			nowPack = helpRel.packet.first;
		}

		//std::cout << std::endl << "\nbuffer: ";
		//printArr(buffer, n);
		return proc.crit(buffer);
	}

	//// рисует график Ганта на основе выходных данных procNum
	//void drawGraph(bool method) { 
	//	int *useArr = method ? bestMVG : bestSO;
	//	procNum(useArr);
	//	for (int i = 0; i < m; i++) {
	//		std::cout << std::endl << i + 1 << ": ";

	//		for (int k = 0; k < n; k++) {
	//			if (buffer[useArr[k] - 1] == i + 1)
	//				for (int j = 0; j < times[useArr[k] - 1]; j++)
	//					std::cout << useArr[k];
	//		}
	//	}
	//} 

	void printBestSO() {
		printArr(bestSO, n);
	}

	void printBestMVG() {
		printArr(bestMVG, n);
	}

	void printArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << ", ";
	}

	void clearArr(int *arr, int n) {
		n--;
		while (n != -1) {
			arr[n] = 0;
			n--;
		}
	}

	void sort(int *arr) {
		int glass = 0;
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++)
				if (arr[j] > arr[i]) {
					glass = arr[j];
					arr[j] = arr[i];
					arr[i] = glass;
				}		
	}

	~task() {
		delete buffer;
		delete bestSO;
	}
};*/