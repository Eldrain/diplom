#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include "Marks.cpp"

class MarkMethod : public AMethod {
protected:
	Marks * marks;
public:
	MarkMethod(Marks *marks) : marks(marks) {}

	virtual ~MarkMethod() {
		delete marks;
	}
};