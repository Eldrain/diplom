#pragma once
#include "stdafx.h"
#include "Stack.cpp"

class Jobs {
private:
	int count;
public:
	class job {
	public:
		int nowPrev, countPrev, time;
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

		/*job& operator =(const job& jb) {
			this->time = jb.time;
			this->countPrev = jb.countPrev;
			nowPrev = 0;
			complete = false;
			fol = NULL;

			follow *now = jb.fol;
			while (now) {
				addFollow(now->n);
				now = now->next;
			}

			return *this;
		}*/

		void addFollow(int n) {
			follow.push(n);
		}

		void deleteFollows() {
			follow.clear();
		}

		void refresh() {
			nowPrev = countPrev;
			complete = false;
		}

		~job() {
		}
	};
	class Front {
	public:
		Stack<int> stack, pool;

		//¬озвращает индекс работы с максимальным временем во фронте. јргумент нужен дл€ получени€ длительностей выполнени€ работ
		int findMax(Jobs &jobs) {
			Stack<int>::elem *elem = stack.first;
			if (!elem)
				return 0;

			int max = elem->info;
			while (elem) {
				if (jobs[max - 1] < jobs[elem->info - 1])
					max = elem->info;
				elem = elem->next;
			}
			return max;
		}

		//¬озвращает индекс работы с минимальным временем во фронте. јргумент нужен дл€ получени€ длительностей выполнени€ работ
		int findMin(Jobs &jobs) {
			Stack<int>::elem *elem = stack.first;
			if (!elem)
				return 0;

			int min = elem->info;
			while (elem) {
				if (jobs[min - 1] > jobs[elem->info - 1])
					min = elem->info;
				elem = elem->next;
			}
			return min;
		}

		void add(int n) {
			Stack<int>::elem *el = pool.pop();
			if (!el)
				el = new Stack<int>::elem(n);
			else
				el->info = n;
			stack.push(el);
		}

		bool del(int n) {
			Stack<int>::elem *el = stack.pop(n);
			if (el) {
				pool.push(el);
				return true;
			}
			else
				return false;
		}

		bool find(int n) {
			Stack<int>::elem *now = stack.first;
			while (now) {
				if (now->info == n)
					return true;
				now = now->next;
			}
			return false;
		}	

		void print() {
			stack.print();
		}

		void clear() {
			while (stack.first) 
				pool.push(stack.pop());		
		}

		~Front() {
		}
	};

	Front front;
	job *jobs;

	Jobs() {
		count = 0;
		jobs = NULL;
	}

	Jobs(int n) {
		count = n;
		jobs = new job[n];
	}

	/*Jobs &operator =(const Jobs &jobs) {
		count = jobs.count;
		this->jobs = new job[count];

		for (int i = 0; i < count; i++)
			this->jobs[i] = jobs.jobs[i];

		return *this;
	}*/

	void create(int n) {
		count = n;
		delete jobs;
		jobs = new job[n];
	}

	bool checkVar(int *arr, int set) {
		refresh();
		for (int i = 0; i < set; i++)
			if (!complete(arr[i]))
				return false;
		
		return true;
	}

	bool complete(int n) {
		if (front.del(n)) {
			Stack<int>::elem *now = jobs[n - 1].follow.first;
			while (now) {
				jobs[now->info - 1].nowPrev--;
				if (jobs[now->info - 1].nowPrev == 0)
					front.add(now->info);
				now = now->next;
			}
			jobs[n - 1].complete = true;		
			return true;
		} else
			return false;
	}

	int minTime() {
		int min = 0;
		bool set = false;

		for (int i = 0; i < count; i++)
			if (!jobs[i].complete)
				if (set) {
					if (jobs[min].time > jobs[i].time)
						min = i;
				}
				else {
					set = true;
					min = i;
				}	
		return min;
	}

	void refresh() {
		front.clear();
		for (int i = 0; i < count; i++) {
			jobs[i].refresh();
			if (jobs[i].countPrev == 0)
				front.add(i + 1);
		}	
	}

	//возвращает врем€ выполнени€ работы
	int operator[](int i) {
		return jobs[i].time;
	}

	void print() {
		std::cout << std::endl << "count = " << count;
		std::cout << std::endl << "Front: ";
		front.print();

		for (int i = 0; i < count; i++) {
			std::cout << std::endl << i + 1 << ": ";
			jobs[i].follow.print();
		}
	}

	void defineCountPrev() {
		for (int i = 0; i < this->count; i++)
			jobs[i].countPrev = countPrevs(i + 1);	
	}

	int countPrevs(int num) {
		int count = 0;
		for (int i = 0; i < this->count; i++)
			if (jobs[i].follow.find(num))
				count++;
		return count;
	}

	void clear() {
		front.clear();
		delete[] jobs;
		jobs = NULL;
		count = 0;
	}

	int getCount() {
		return count;
	}

	~Jobs() {
		delete[] jobs;
	}
};