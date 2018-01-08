#pragma once
#include "stdafx.h"
#include "IFModule.cpp"

class MaxModule : public IFModule {

	void update(Jobs &jobs) {
	}

	int next(Jobs &jobs) {
		return jobs.FindMaxInFront();
	}

	virtual ~MaxModule() {
	}
};