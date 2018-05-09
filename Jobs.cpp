#pragma once
#include "stdafx.h"
#include "Stack.cpp"
#include "vector.cpp"

using namespace eld;

class Jobs {//Class for work and store jobs	
private:
	int count;
	class Front {//Inner class for store unfulfilmed jobs from front
	private:
		/*
		Stack<int> mStack - for store current jobs from front
		Stack<int> mPool - pool for unused objects
		*/
		Stack<int> stack_;
		Stack<int> pool_;

	public:
		//Method returns index of job with max time in front
		int FindMax(Jobs &jobs) {
			if (stack_.size() == 0)
				return 0;
			Stack<int>::Iterator *i = stack_.GetIterator();
			int max = i->current_->info;

			do {
				if (jobs[max - 1] < jobs[i->current_->info - 1])
					max = i->current_->info;
			} while (i->get_next());

			return max;

		}

		//Method returns index of job with min time in front
		int FindMin(Jobs &jobs) {
			if (stack_.size() == 0)
				return 0;
			Stack<int>::Iterator *i = stack_.GetIterator();
			int min = i->current_->info;

			do {
				if (jobs[min - 1] > jobs[i->current_->info - 1])
					min = i->current_->info;
			} while (i->get_next());
			return min;
		}

		//Add job with index == n in front. If front contains this job, not add it again
		void Add(int n) {
			if (Find(n)) {
				return;
			}

			Stack<int>::elem *el = pool_.pop();
			if (!el) {
				el = new Stack<int>::elem(n);
			}
			else {
				el->info = n;
			}
			stack_.push(el);
		}

		//Remove from front job with index == n if it's having here
		bool Remove(int n) {
			Stack<int>::elem *el = stack_.pop(n);
			if (el) {
				pool_.push(el);
				return true;
			}
			else
				return false;
		}

		//Find in front job with index == n. If it's having here returns TRUE, else FALSE
		bool Find(int n) {
			Stack<int>::elem *now = stack_.first;
			while (now) {
				if (now->info == n)
					return true;
				now = now->next;
			}
			return false;
		}

		int size() {
			return stack_.size();
		}

		void Print() {
			stack_.print();
		}

		void Clear() {
			while (stack_.first)
				pool_.push(stack_.pop());
		}

		Stack<int>::Iterator* GetIterator() {
			return stack_.GetIterator();
		}

		~Front() {
		}
	};
	class job {//Inner class for store data about concrete job
	public:
		/*
		int nowPrev - previous uncomleted jobs at the moment
		int countPrev - previous jobs
		int time - lead time
		bool complete - variable for fix fulfilment of job
		Stack<int> follow - stack for store next jobs
		*/
		int nowPrev;
		int countPrev;
		int time;
		bool complete;
		Stack<int> follow;

		job() {
			countPrev = nowPrev = 0;
			complete = false;
		}

		job(int time, int countPrev) {
			this->time = time;
			this->countPrev = countPrev;
			nowPrev = 0;
			complete = false;
		}

		void AddFollow(int n) {
			follow.push(n);
		}

		void deleteFollows() {
			follow.clear();
		}

		Stack<int>::Iterator *GetFollowIterator() {
			return follow.GetIterator();
		}

		//Reset counter previous jobs and make job unfulfiled
		void refresh() {
			nowPrev = countPrev;
			complete = false;
		}

		~job() {
		}
	};

	Front front_;
	job *jobs_;

public:
	Jobs() {
		count = 0;
		jobs_ = NULL;
	}

	Jobs(int n) {
		count = n;
		//jobs_.resize(n);
		jobs_ = new job[n];
	}

	/*Jobs &operator =(const Jobs &jobs) {
		count = jobs.count;
		mJobs = new job[count];

		for (int i = 0; i < count; i++)
			mJobs[i] = jobs.mJobs[i];

		return *this;
	}*/

	//Resize array of jobs
	void resize(int n) {
		count = n;
		delete[] jobs_;
		jobs_ = new job[n];
		//jobs_.resize(n);
	}

	//Return TRUE if order corresponds to current task
	bool Check(int *arr, int set) {
		refresh();
		for (int i = 0; i < set; i++)
			if (!Complete(arr[i]))
				return false;	
		return true;
	}

	//Fulfilling job in front and returns TRUE. If job not finded in front returns FALSE.
	bool Complete(int n) {
		if (front_.Remove(n)) {
			Stack<int>::Iterator *i = jobs_[n - 1].GetFollowIterator();
			if (i == NULL)
				return true;

			do {
				jobs_[i->current_->info - 1].nowPrev--;
				if (jobs_[i->current_->info - 1].nowPrev == 0)
					front_.Add(i->current_->info);
			} while (i->get_next());

			jobs_[n - 1].complete = true;
			return true;
		} else
			return false;
	}

	//Make job with index n unfulfited
	void Uncomplete(int n) {
		jobs_[n - 1].complete = false;
		Stack<int>::Iterator *i = jobs_[n - 1].GetFollowIterator();

		if (i != NULL) {
			do {
				jobs_[i->current_->info - 1].nowPrev++;
				if (jobs_[i->current_->info - 1].nowPrev == 1) {
					front_.Remove(i->current_->info);
				}
			} while (i->get_next());
		}
		front_.Add(n);
	}
	
	//Fulfilling n jobs with min time from front. Returns pointer on current unfulfited job in var
	int CompleteJobs(int n, int *var, int &pointer) {
		int minJob = 0;
		int minTime = jobs_[front_.FindMax(*this) - 1].time;

		while (n != 0 && front_.size() != 0)
		{
			if (var[pointer] == 0) {
				minJob = front_.FindMax(*this);
			}
			else {
				minJob = var[pointer];
				if (front_.Find(minJob) == false) {
					break;
				}
			}

			if (minTime > jobs_[minJob - 1].time) {
				minTime = jobs_[minJob - 1].time;
			}

			pointer++;
			front_.Remove(minJob);

			Stack<int>::Iterator *i = jobs_[minJob - 1].GetFollowIterator();
			if (i != NULL) {
				do {
					jobs_[i->current_->info - 1].nowPrev--;
				} while (i->get_next());
			}

			jobs_[minJob - 1].complete = true;
			n--;
		}

		for(int i = 0; i < count; i++)
			if (jobs_[i].nowPrev == 0 && !jobs_[i].complete)
				front_.Add(i + 1);
		
		return minTime;
	}

	//Returns index - 1 of job with min time fulfiting
	int MinTime() {
		int min = 0;
		bool set = false;

		for (int i = 0; i < count; i++)
			if (!jobs_[i].complete)
				if (set) {
					if (jobs_[min].time > jobs_[i].time)
						min = i;
				}
				else {
					set = true;
					min = i;
				}	
		return min;
	}

	//Update jobs connections set for new work
	void refresh() {
		front_.Clear();
		for (int i = 0; i < count; i++) {
			jobs_[i].refresh();
			if (jobs_[i].countPrev == 0)
				front_.Add(i + 1);
		}	
	}

	int FindMaxInFront() {
		return front_.FindMax(*this);
	}

	int FindMinInFront() {
		return front_.FindMin(*this);
	}

	bool FindInFront(int n) {
		return front_.Find(n);
	}

	int front_size() {
		return front_.size();
	}

	bool SetJobTime(int n, int time) {
		if (n > count) {
			return false;
		}

		jobs_[n - 1].time = time;
		return true;
	}

	bool AddJobFollow(int n, int follow) {
		if (n > count) {
			return false;
		}
		jobs_[n - 1].AddFollow(follow);
		return true;

	}

	bool FindInFollows(int n, int follow) {
		return jobs_[n - 1].follow.find(follow);
	}

	//Returns time of jobs
	int operator[](int i) {
		return jobs_[i].time;
	}

	void Print() {
		std::cout << std::endl << "count = " << count;
		std::cout << std::endl << "Front: ";
		front_.Print();

		for (int i = 0; i < count; i++) {
			std::cout << std::endl << i + 1 << ": ";
			jobs_[i].follow.print();
		}
	}

	void PrintTimes() {
		std::cout << std::endl << "Times: ";
		for (int i = 0; i < count; i++) {
			std::cout << jobs_[i].time << ", ";
		}
	}

	void defineCountPrev() {
		for (int i = 0; i < this->count; i++)
			jobs_[i].countPrev = CountPrev(i + 1);
	}

	//returns count of previous jobs
	int CountPrev(int num) {
		int count = 0;
		for (int i = 0; i < this->count; i++)
			if (jobs_[i].follow.find(num))
				count++;
		return count;
	}

	//Returns next previous job for job with num == n. cur - current number of previous job
	int GetNextPrev(int n, int cur) {
		cur--;
		while (cur != n) {
			if (jobs_[cur - 1].follow.find(n)) {
				return cur;
			}
			cur--;
		}
		return 0;
	}

	void clear() {
		front_.Clear();
		count = 0;
		//jobs_.clear();
		delete[] jobs_;
		jobs_ = NULL;
	}

	int get_count() {
		return count;
	}

	//Create clone of parent
	void CloneFrom(Jobs &parent) {
		parent.refresh();
		resize(parent.get_count());

		for (int i = 0; i < count; i++) {
			jobs_[i].time = parent.jobs_[i].time;
			jobs_[i].countPrev = parent.jobs_[i].countPrev;
			
			Stack<int>::Iterator *it = parent.jobs_[i].GetFollowIterator();
			if (it == NULL) {
				continue;
			}

			do {
				jobs_[i].AddFollow(it->current_->info);
			} while (it->get_next());
		}
		refresh();
	}

	Stack<int>::Iterator* GetFrontIterator() {
		return front_.GetIterator();
	}

	Stack<int>::Iterator* GetFollowIterator(int n) {
		return jobs_[n - 1].GetFollowIterator();
	}

	void RemoveFollow(int from, int num) {
		jobs_[num - 1].countPrev--;
		jobs_[from - 1].follow.remove(num);

	}

	~Jobs() {
		delete[] jobs_;
	}
};