// kursach.cpp: ���������� ����� ����� ��� ����������� ����������.
//

//#include "stdafx.h"
#include "test.cpp"
#include <stdio.h>
//#include "UnitTests.cpp"
#include <list>

using namespace std;

void clearArr(int *arr) {
	delete[] arr;
	arr = NULL;
}

void printArr(int *arr, int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << ", ";
}

int main()
{
	setlocale(0, "");
	
	Task task;
	int n = 0, m = 0;
	//UnitTests t;

	//t.TreeTest();

	test test1;
	test1.timeTest(5, 30, 3, 50, 8, task);
	//test1.start();
	//test1.generateTree(jobs, 10, 50, 5);
	//test1.timeTest(5, 20, 3, 50, 5, task);
	//test1.testFront(50, 100, 5, 200, 8, task);
	/*cout << endl << "SortOut: f = " << sOut.solve();
	sOut.printBest();
	cout << "\ncountVar = " << sOut.countVar << "; timeSO: " << sOut.timeSO << " s.";
	cout << endl << "timeCheck = " << sOut.timeCheck << "s.; timeCrit = " << sOut.timeCrit << "s.";
	cout << endl << endl << "Clip: f = " << clip.solve();
	clip.printBest();
	cout << "\ncountVar = " << clip.countVar << "; time: " << clip.timeClip << " s.";
	cout << endl << "timeCheck = " << clip.timeCheck << "s.; timeCrit = " << clip.timeCrit << "s.";
	cout << endl << "maxTime = " << clip.maxTime << "s.; minTime = " << clip.minTime << "s.";
	/*task exp(n, m, times, rel);
	cout << "\n����������� ������: n = " << n << "; m = " << m << "\ntimes: ";
	printArr(times, n);
	rel.print();
	cout << "\n�������: f = " << exp.sortOut();
	cout << "\n����� ���������: " << exp.countVar << "\n������������: ";
	exp.printBestSO();
	exp.test();
	cout << endl << "timeSO = " << exp.timeSO;
	//exp.drawGraph(false);
	cout << "\n����� ������ � ������: f = " << exp.mVG();
	cout << "\n����� ���������: " << exp.countVar << "\n������������: ";
	exp.printBestMVG();
	cout << endl << "timeMVG = " << exp.timeMVG;
	//exp.drawGraph(true);*/
	//clearArr(times);
	//nodelay();
	getchar();
	return 0;
}