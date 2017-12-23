//#include "stdafx.h"

class ListOC {
public:
	int num1, num2;
	bool twice;
	ListOC() {
		num1 = 0;
		num2 = 0;
		twice = false;
	}
	ListOC(int num1, int num2) {
		this->num1 = num1;
		this->num2 = num2;
		twice = false;
	}
};