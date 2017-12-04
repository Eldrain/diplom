#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "BBMarks.cpp"
#include "MazMarks.cpp"

class MarkFactory {
public:
	static Marks *CreateSimpleMarks() {
		return create<BBMarks>();
	}

	static Marks *CreateBestMarks() {
		return create<MazMarks>();
	}

private:
	template<class T>
	static Marks *create() {
		return new T();
	}
};

