#pragma once
#include "stdafx.h"
#include "Marks.cpp"
#include "BBMarks.cpp"
#include "MozMarks.cpp"
#include "StatMarks.cpp"
#include "ErrorMarks.cpp"

class MarkFactory {
public:
	static Marks *CreateSimpleMarks() {
		return create<BBMarks>();
	}

	static Marks *CreateBestMarks() {
		return create<MozMarks>();
	}

	static Marks* CreateStatMarks(Statistics *stat) {
		StatMarks<MozMarks> *marks = new StatMarks<MozMarks>(stat);
		return marks;
	}

	static Marks* CreateErrorMarks() {
		return new ErrorMarks();
	}

private:
	template<class T>
	static Marks *create() {
		return new T();
	}
};

