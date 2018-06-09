#pragma once
#include <iostream>
#include <string>

class Solution {
private:
	int methodId;
	std::string methodName;
	int *arr;
	int f;
	int n;
	int m;
	// Statistics
	double time;
	int countVar;
public:
	Solution(int metId, std::string metName, int *arr, int n, int m, int f, double time, int countVar) 
		:methodId(metId), methodName(metName), arr(arr), f(f), n(n), m(m), time(time), countVar(countVar) {}

	void print() {
		std::cout << "Solution by " << methodName << "(" << methodId << "): ";
		for (int i = 0; i < n; i++) {
			std::cout << arr[i];
			if (i != n - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl << "f: " << f << ", time: " << time << " s, countVar: " << countVar;
	}

	int getMin() {
		return f;
	}

	int* getArr() {
		return arr;
	}

	~Solution() {
		delete[] arr;
	}
};