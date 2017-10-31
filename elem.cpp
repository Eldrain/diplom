#include "stdafx.h"

class elem {
public:
	elem *brother;
	int set, min, max, *arr;

	elem(int set) {
		this->set = set;
		min = 0;
		max = 0;
		brother = NULL;
		arr = NULL;
	}

	elem(int *arr, int set, int max) {
		this->set = set;
		this->arr = arr;
		min = 0;
		this->max = max;
		brother = NULL;
	}

	~elem() {
		delete[] arr;
		arr = NULL;
	}
};

class elemPool {
	elem *first, *last;
public:
	elemPool() {
		first = NULL;
		last = NULL;
	}

	void addElem(elem *newElem) {
		if (last)
			last->brother = newElem;
		else
			first = newElem;
		last = newElem;
	}

	elem *getElem() {
		if (first == NULL) {
			last = NULL;
			return NULL;
		}
		else {
			elem *nowEl = first;
			first = first->brother;
			nowEl->brother = NULL;
			return nowEl;
		}
	}

	void clearPool() {
		while (first)
			delete getElem();
	}

	~elemPool() {
		clearPool();
	}
};
