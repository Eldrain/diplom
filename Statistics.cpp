#pragma once
#include "stdafx.h"
#include <iostream>

class Statistics {
private:
	double av_f;
	double av_min_;
	double av_max_;
	double av_time_;
	double av_err_;
	double av_countvar_;
public:
	static int etalonMinF;
	
	Statistics() :
		av_f(0),
		av_min_(0),
		av_max_(0),
		av_time_(0),
		av_err_(0),
		av_countvar_(0) {}

	void AddF(double f) {
		av_f = (av_f + f) / 2;
	}

	void AddMin(double min) {
		av_min_ = (av_min_ + min) / 2;
	}

	void AddMax(double max) {
		av_max_ = (av_max_ + max) / 2;
	}

	void AddTime(double time) {
		av_time_ = (av_time_ + time) / 2;
	}

	void AddErr(double minF) {
		av_err_ = (av_err_ + (minF - etalonMinF)/ etalonMinF * 100) / 2;
	}

	void AddCountVar(double count_var) {
		av_countvar_ = (av_countvar_ + count_var) / 2;
	}

	void print() {
		std::cout << std::endl << "Statistics: avF = " << av_f << "; avMin = " << av_min_ << "; avMax = " << av_max_ << "; avTime = " << av_time_ << "s.; avErr = " << av_err_ << " %; avCountVar = " << av_countvar_;
		std::cout << std::endl;
	}
};