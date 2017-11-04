#pragma once
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include "Windows.h"

class UnitTests {
private:
	HANDLE hConsole;
public:
	UnitTests() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void TreeTest() {
		res(true);
		res(false);
	}

	void res(bool result) {
		if (result) {
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			std::cout << "Matrix has you\n";
		}
		else {
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
			std::cout << "Matrix has you\n";
		}
	}
};