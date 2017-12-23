#pragma once
//#include "stdafx.h"
#include "AMethod.cpp"
#include "Statistics.cpp"

class StatMethod : public IMethod {
private:
	Statistics *stat;
	AMethod *m;

public:
	StatMethod(Statistics *st, AMethod *m) :stat(st), m(m) {}

	int Solve(Task &task) {
		int minF = m->Solve(task);
		stat->AddF(minF);
		stat->AddErr(minF);
		stat->AddCountVar(m->getCountVar());
		stat->AddTime(m->GetTime());
		return minF;
	}

	void GetRes(std::ostringstream &res) {
		m->GetRes(res);
	}

	void Update() {
		m->Update();
	}

	void Start(Task &task, int set) {
		m->Start(task, set);
	}

	void PrintRes() {
		m->PrintRes();
	}

	void GetAddInfo(std::ostringstream &info) {
		m->GetAddInfo(info);
	}

	~StatMethod() {
		delete m;
	}
};