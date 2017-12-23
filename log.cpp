#pragma once
//#include "stdafx.h"
#include <iostream>

namespace sort {
	class log {
	private:
		int cur;
		int all;
		double averange;
		double result;
	public:

		log() {
			all = 0;
			cur = 0;
			averange = 0;
		}

		void doLog(int mark) {
			averange += mark;
			cur++;
			all++;

			if (cur == 10) {
				cur = 0;
				averange /= 10;
				result = (result + averange) / 2;
				averange = 0;
			}
		}

		void clear() {
			cur = 0;
			result = 0;
			all = 0;
		}

		void print() {
			std::cout << "\nLOG: averange mark = " << result;
		}

		~log() {
		}
	};
}