#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "MaxSimple.cpp"
#include "MinMoz.cpp"

class MozMarks : public Marks {
public:
	MozMarks() {
		max = new MaxSimple();
		min = new MinMoz();
	}

	~MozMarks() {
	}
};