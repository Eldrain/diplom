#pragma once
#include "MaxMaxFront.cpp"
#include "MaxMinFront.cpp"
#include "MinMingozzi.cpp"
#include "MinPathMark.cpp"
#include "MinSimple.cpp"
#include "StatMark.cpp"

class MarkFactory {
public:
	Mark* createBestMax() {
		return new MaxMaxFront();
	}

	Mark* createFirstMax() {
		return new MaxMaxFront();
	}

	Mark* createSecondMax() {
		return new MaxMinFront();
	}

	Mark* createBestMin() {
		return new MinPathMark();
	}

	Mark* createSimpleMin() {
		return new MinSimple();
	}

	Mark* createMingozzi() {
		return new MinMingozzi();
	}

	Mark* createMinPath() {
		return new MinPathMark();
	}

	Mark* createStatMark(Stats *stats, Mark *mark, bool type) {
		return new StatMark(stats, mark, type);
	}
};

