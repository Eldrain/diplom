#pragma once
#include <stdio.h>

class Stats {
private:
	double av_f; // Averange optimum
	double av_min; // Averange minimum mark
	double av_max; // Averange max mark
	double av_time; // Averange time of calculations
	double av_countVar; // Averange count of solutions

	//// Buffer variables
	//unsigned int minValue; // Sum of all min marks in this iteration
	//int countMin; // Count of calculated min marks
	//unsigned int maxValue;// Sum of all max marks in this iteration
	//int countMax; // Count of calculated max marks
public:
	
	Stats() :
		av_f(0),
		av_min(0),
		av_max(0),
		av_time(0),
		av_countVar(0)/*, countMax(0), countMin(0)*/{}

	void addMinMark(int value) {
		av_min = (av_min + (double)value) / 2;
		/*minValue += value;
		countMin++;*/
	}

	void addMaxMark(int value) {
		av_max = (av_max + (double)value) / 2;
		/*maxValue += value;
		countMax++;*/
	}

	void add(int f, double time, int countVar) {
		av_f = ((double)f + av_f) / 2;
		av_time = (time + av_time) / 2;
		av_countVar = ((double)countVar + av_time) / 2;

		/*if (countMin) {
			av_min = (minValue / countMin + av_min) / 2;
		}
		else {
			av_min = -1;
		}
		if (countMax) {
			av_max = ( maxValue / countMax + av_max) / 2;
		}
		else {
			av_max = -1;
		}*/
	}

	void clear() {
		av_f = 0;
		av_time = 0;
		av_countVar = 0;
		av_min = 0;
		av_max = 0;
	}

	void print() {
		printf("f: %f\nav_min: %f\nav_max: %f\nav_time: %f\nav_countvar: %f",
			av_f, av_min, av_max, av_time, av_countVar);
	}
};