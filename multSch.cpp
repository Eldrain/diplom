// kursach.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "test.cpp"
//#include <conio.h>
#include "threadpool.cpp"
//#include "stdlib.cpp"


using namespace std;

void clearArr(int *arr) {
	delete[] arr;
	arr = NULL;
}

void printArr(int *arr, int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << ", ";
}

void print(int i) {
	for (int k = 0; k < i; k++)
		cout << endl << k + 1;
}

void printr(int t) {
	for (int i = 0; i < 50; i++) {
		cout << endl << t;
	}
}

int Statistics::etalonMinF = 1;

int main()
{
	setlocale(0, "");	

	test test1;
	test1.timeTest(15, 25, 3, 50, 10);
	
	getchar();
	return 0;
}