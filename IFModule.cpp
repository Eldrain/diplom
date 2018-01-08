#pragma once
#include "stdafx.h"
#include "Jobs.cpp"

class IFModule {
public:

	virtual void update(Jobs &jobs) = 0;

	virtual int next(Jobs &jobs) = 0;

	virtual ~IFModule() {}
};