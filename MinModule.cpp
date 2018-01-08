#pragma once
#include "stdafx.h"
#include "IFModule.cpp"

class MinModule : public IFModule {

	void update(Jobs &jobs) {
	}

	int next(Jobs &jobs) {
		return jobs.FindMinInFront();
	}

	virtual ~MinModule() {
	}
};