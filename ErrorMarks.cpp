#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "MaxMaxFront.cpp"
#include "MinMoz.cpp"

class ErrorMarks : public Marks {
public:
	ErrorMarks() {
		max = new MaxMaxFront();
		min = new MinMoz();
	}

	~ErrorMarks() {
	}
};