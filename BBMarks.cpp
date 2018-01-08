#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "MaxMaxFront.cpp"
#include "MinSimple.cpp"

class BBMarks : public Marks {
public:
	BBMarks() {
		max = new MaxMaxFront();
		min = new MinSimple();
	}

	~BBMarks() {
	}
};