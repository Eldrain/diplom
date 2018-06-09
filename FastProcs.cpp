#include "IProcs.cpp"

class FastProcs : public IProcs {
private:
    int mCount;
    int *mWorkTimes;
    int mCurMin;

    void findMin() {
        for (int i = 0; i < mCount; i++) {
            if (mWorkTimes[i] < mWorkTimes[mCurMin]) {
                mCurMin = i;
            }
        }
    }
public:
    FastProcs(int count = 0) : mCount(count), mCurMin(0) {
        if (count > 0) {
            mWorkTimes = new int[count];
		}
		else {
			mWorkTimes = NULL;
		}
    };

    // Fill in work time of processor
    // with min work time
    void execute(int time) {
        mWorkTimes[mCurMin] += time;
        findMin();
    }

    // Returns value of optimization function
    int crit(Jobs &jobs, int *var, int set) {
        refresh();
        for (int i = 0; i < set; i++) {
            execute(jobs[var[i] - 1]);
        }
        return mWorkTimes[getMaxIndex()];
    }

    void resize(int newSize) {
        delete[] mWorkTimes;
        mWorkTimes = new int[newSize];
        mCount = newSize;
    }

    void refresh() {
        mCurMin = 0;
        for (int i = 0; i < mCount; i++) {
            mWorkTimes[i] = 0;
        }
    }

    // Returns current time of work.
    // In case bad index returns -1
    int getTime(int index) {
        if (index >= 0 && index < mCount) {
            return mWorkTimes[index];
        }
        else {
            return -1;
        }
    }

    int getMinTime() {
        return mWorkTimes[mCurMin];
    }

    int getMaxTime() {
        int index = getMaxIndex();
        return mWorkTimes[index];
    }

    int getMinIndex() {
        return mCurMin;
    }

    int getMaxIndex() {
        int max = 0;
        for (int i = 0; i < mCount; i++) {
            if (mWorkTimes[i] < mWorkTimes[max]) {
                max = i;
            }
        }
        return max;
    }

    int size() {
        return mCount;
    }

    ~FastProcs() {
        delete[] mWorkTimes;
    }
};