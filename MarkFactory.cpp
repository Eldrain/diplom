#pragma once
#include "MaxMaxFront.cpp"
#include "MinMingozzi.cpp"

class MarkFactory {
public:
	static Mark* createBestMax() {
		return new MaxMaxFront();
	}

	static Mark* createBestMin() {
		return new MinMingozzi();
	}

	/*static Marks *CreateSimpleMarks() {
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

	template<class T>
	static Marks *create() {
		return new T();
	}*/
};

