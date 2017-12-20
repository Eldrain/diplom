// kursach.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "test.cpp"
#include <conio.h>
#include "threadpool.cpp"
#include <stack>

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

int Statistics::etalonMinF = 1;

void printr() {
	for (int i = 0; i < 50; i++) {
		cout << endl << i;
	}
}

int main()
{
	setlocale(0, "");

	eld::threadpool pool(5);
	for (int i = 0; i < 5; i++)
		pool.async_task(&printr);

	test test1;
	test1.timeTest(5, 22, 3, 50, 10);

	getchar();
	return 0;
}