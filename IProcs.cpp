#pragma once
#include "Jobs.cpp"

class IProcs {
public:
	virtual int size() = 0;

	virtual void resize(int m) = 0;

	virtual int crit(int *var, Jobs &jobs, int set) = 0;

	// Execute job with concrete time
	//virtual void execute(int time) = 0;
	virtual int getJobNum(int index) = 0;

	// Returns work time of proccessor 
	virtual int getTime(int index) = 0;

	// Returns time proc with min
	// busy time
	virtual int getMinTime() = 0;

	virtual int getMaxTime() = 0;

	// Returns index proc with max
	// busy time
	//virtual int getMaxIndex() = 0;

	//virtual int getMinIndex() = 0;

	virtual ~IProcs() {
	}
};