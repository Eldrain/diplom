#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "MaxSimple.cpp"
#include "MinMoz.cpp"

class ErrorMarks : public Marks {
public:
	ErrorMarks() {
		max = new MaxSimple();
		min = new MinMoz();
	}

	~ErrorMarks() {
	}
};