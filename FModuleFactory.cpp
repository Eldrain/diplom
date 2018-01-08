#pragma once
#include "stdafx.h"
#include "IFModule.cpp"
#include "MaxModule.cpp"
#include "MinModule.cpp"
#include "BackModule.cpp"

static class FModuleFactory {
public:
	static void CreateSet(sort::vector<IFModule*> &set) {
		set.resize(3);
		set[0] = new MaxModule();
		set[1] = new MinModule();
		set[2] = new BackModule();
	}

	static void Release(sort::vector<IFModule*> &set) {
		for (int i = 0; i < set.size(); i++) {
			delete set[i];
		}
	}
};