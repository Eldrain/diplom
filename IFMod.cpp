#pragma once
#include "stdafx.h"
#include "Jobs.cpp"

class IFMod {

	virtual int next(Jobs::Front &front) = 0;

	virtual ~IFMod() {
	}
};