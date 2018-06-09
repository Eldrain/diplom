#pragma once
#include "AMethod.cpp"
#include "Marks.cpp"

class MarkMethod : public AMethod {
protected:
	int *buf;
	Mark *min;
	Mark *max;
public:
	MarkMethod(int metId, std::string metName) : AMethod(metId, metName), buf(NULL), min(NULL), max(NULL) {}

	int setMark(Mark *min, Mark *max) {
		int rc = -1;
		if ( (min != NULL) && (max != NULL) ) {
			delete this->min;
			delete this->max;
			this->min = min;
			this->max = max;
			rc = 0;
		}
		return rc;
	}

	virtual ~MarkMethod() {
		delete[] buf;
		delete min;
		delete max;
	}
};