#pragma once
#include "stdafx.h"
#include "AMethod.cpp"
#include "Statistics.cpp"

template <class T>
class StatMethod : public AMethod {
private:
	Statistics *stat;
	AMethod *m;

public:
	StatMethod(Statistics *st) :stat(st), m(new T()) {
		/*var_ = NULL;
		best_ = NULL;*/
	}

	//TODO: DELETE KOSTYL'!!!!
	StatMethod(Statistics *st, AMethod *m) :stat(st), m(m) {}

	int Solve(Task &task) {
		minF = m->Solve(task);
		stat->AddF(minF);
		stat->AddErr(minF);
		stat->AddCountVar(m->getCountVar());
		stat->AddTime(m->GetTime());
		return minF;
	}

	void Update() {
		m->Update();
	}

	void Start(Task &task) {
		m->Start(task);
	}

	void PrintRes() {
		m->PrintRes();
	}

	~StatMethod() {
		delete m;
	}
};