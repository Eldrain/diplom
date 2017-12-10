#pragma once
#include "stdafx.h"
#include <iostream>
//#include "vector.cpp"

//using namespace sort;

class ArrFunctions {
public:
	static void copyArr(int *arr1, int *arr2, int n) {
		for (int i = 0; i < n; i++)
			arr1[i] = arr2[i];
	}

	static void printArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << ", ";
	}

	static void clearArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			arr[i] = 0;
	}

	/*tatic void copyArr(vector<int> &arr1, vector<int> &arr2) {
		for (int i = 0; i < arr1.size(); i++)
			arr1[i] = arr2[i];
	}

	static void printArr(vector<int> &arr) {
		for (int i = 0; i < arr.size(); i++)
			std::cout << arr[i] << ", ";
	}

	static void clearArr(vector<int> &arr) {
		for (int i = 0; i < arr.size(); i++)
			arr[i] = 0;
	}*/
};