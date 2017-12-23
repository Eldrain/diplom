#pragma once
//#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include "Windows.h"
#include "Tree.cpp"
#include <string>

class UnitTests {
/*private:
	HANDLE hConsole;
public:
	UnitTests() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void TreeTest() {
		int arr[] = { 1, 2, 3 };
		int n = 3, set = 3;
		//Tree::leaf lf(arr, n, 0, 0, set), lf2(new int[]{2, 3, 0}, 3, 1, 1, 2), lf3(arr, n, 1, 2, set);
		/*Tree tree(n);

		log("Tree test");
		testLeaf(lf, lf2, lf3, arr);
		tree.addInWave(arr, 3, 3, set);
		res("Add in wave", compare(arr, tree.wave.first->info->arr, n));

	}

	void testLeaf(Tree::leaf &lf, Tree::leaf &lf2, Tree::leaf &lf3, int *arr) {		
		res("Create leaf and copyArr", compare(lf.arr, arr, 3));
		res("operator == 1", !(lf == lf2));
		res("operator == 2", lf == lf3);
	}

	bool compare(int *arr1, int *arr2, int n) {
		for (int i = 0; i < n; i++)
			if (arr1[i] != arr2[i])
				return false;
		return true;
	}

	void res(std::string testName, bool result) {

		if (result) {
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			std::cout << testName << ": + Success\n";
		}
		else {
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
			std::cout << testName << ": - Error\n";
		}
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
	}

	void log(std::string str) {
		std::cout << str << ":" << std::endl;
	}*/
};