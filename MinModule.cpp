#pragma once
#include "Module.cpp"

class MinModule : public Module {

	void update(Jobs &jobs) {
	}

	int next(Jobs &jobs) {
		return jobs.FindMinInFront();
	}

	virtual ~MinModule() {
	}
};