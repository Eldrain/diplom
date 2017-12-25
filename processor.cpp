#pragma once
#include "stdafx.h"

class processor  {
public:
	int mJob;
	int mWork;
	int mAll;
	//TODO: delete buf!!!
	int buf;
	bool busy;

	processor() : mJob(0), mWork(0), mAll(0), busy(false) {}

	void reset() {
		mJob = mWork = mAll  = buf = 0;
		busy = false;
	}

	bool work(int time) {
		if (mWork <= time) {
			mWork = 0;
			busy = false;
		}
		else {
			mWork -= time;
		}

		return !busy;
	}
};