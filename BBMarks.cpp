#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "MaxSimple.cpp"
#include "MinSimple.cpp"

class BBMarks : public Marks {
public:
	BBMarks() {
		max = new MaxSimple();
		min = new MinSimple();
	}

	~BBMarks() {
	}
};