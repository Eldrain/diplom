#pragma once
#include "stdafx.h"
#include "Mark.cpp"
#include "Stats.cpp"

class StatMark : public Mark {
private:
	Stats *stats;
	Mark *mark;
	bool type; // flag type of mark (max = 1 or min = 0)
public:
	StatMark(Stats *st, Mark *mark, bool type) : 
		stats(st),
		mark(mark),
		type(type) {}

	int bound(int *var, int set, Task &task, int *buf) {
		int value = mark->bound(var, set, task, buf);
		if (type) {
			stats->addMaxMark(value);
		}
		else {
			stats->addMinMark(value);
		}
		return value;
	}

	~StatMark() {
		delete mark;
	}
};