#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "BBMarks.cpp"
#include "MozMarks.cpp"

class MarkFactory {
public:
	static Marks *CreateSimpleMarks() {
		return create<BBMarks>();
	}

	static Marks *CreateBestMarks() {
		return create<MozMarks>();
	}

private:
	template<class T>
	static Marks *create() {
		return new T();
	}
};

