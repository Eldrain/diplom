#pragma once
#include "stdafx.h"
#include <AMethods.cpp>
#include "Marks.cpp"

class AMarkMethod : public AMethod {
protected:
	Marks *marks;
public:

	void setMarks(Marks *newMarks) {
		delete marks;
		marks = newMarks;
	}

	virtual ~AMarkMethod() {
		delete marks;
	}
};