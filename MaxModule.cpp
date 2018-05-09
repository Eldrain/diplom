#pragma once
#include "Module.cpp"

class MaxModule : public Module {

	void update(Jobs &jobs) {
	}

	int next(Jobs &jobs) {
		return jobs.FindMaxInFront();
	}

	virtual ~MaxModule() {
	}
};