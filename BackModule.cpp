#pragma once
#include "Module.cpp"
#include "Hook.cpp"

class BackModule : public Module {
private:
	int *pairs;
	Hook hook;
	int step;
public:
	BackModule() : pairs(NULL) {}
	
	void update(Jobs &jobs) {
		delete[] pairs;
		pairs = new int[jobs.get_count()];
		hook.update(jobs.get_count());

		jobs.refresh();
		int orderCount = 0;
		hook.calculateHooks(jobs, pairs, orderCount);
		if (orderCount != jobs.get_count()) {
			std::cout << "Back module error. Unexpected count of sorted jobs";
		}
		step = 0;
	}

	int next(Jobs &jobs) {
		int res = pairs[step];
		step++;
		return res;
	}

	virtual ~BackModule() {
		delete[] pairs;
	}
};