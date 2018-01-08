#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "MaxMaxFront.cpp"
#include "MinMingozzi.cpp"

class MozMarks : public Marks {
public:
	MozMarks() {
		max = new MaxMaxFront();
		min = new MinMingozzi();
	}

	~MozMarks() {
	}
};