#pragma once
#include "Task.cpp"

class Generator {
public:
	static void GenerateTree(Task &task, int n, int maxTime, int retry) {
		task.n = n;
		generateTree(task.jobs, n, maxTime, retry);
		RemoveRedundancy(task);
		task.jobs.PrintTimes();
	}

	static void GenerateChain(Task &task, int n, int maxTime) {
		task.n = n;
		generateChain(task.jobs, n, maxTime);
	}

	//minimaze graph of dependicies of jobs
	static void RemoveRedundancy(Task &task) {
		Stack<int>::Iterator *it = nullptr;
		Stack<int>::Iterator iterator;
		int n = 0;
		bool del = false;

		for (int i = task.n; i > 1; i--) {
			iterator.current_ = task.jobs.GetFollowIterator(i)->current_;
			del = false;
			do {
				if (del) {
					task.jobs.RemoveFollow(i, n);
					n = 0;
					del = !del;
				}
				it = task.jobs.GetFollowIterator(i);

				do {
					if (iterator.current_->info == it->current_->info) {
						continue;
					}
					if (FindPath(task, it->current_->info, iterator.current_->info)) {
						del = true;
						n = iterator.current_->info;
						break;

					}
				} while (it->get_next());
			} while (iterator.get_next());

			if (del) {
				task.jobs.RemoveFollow(i, n);
				n = 0;
				del = !del;
			}
		}
		task.jobs.defineCountPrev();
		task.jobs.refresh();
	}

	//recursive method for find vertex with number == num
	static bool FindPath(Task &task, int from, int num) {
		Stack<int>::Iterator *i = task.jobs.GetFollowIterator(from);
		if (i == nullptr) {
			return false;
		}

		do {
			if (i->current_->info == num || FindPath(task, i->current_->info, num)) {
				return true;
			}
		} while (i->get_next());

		return false;
	}
private:
	static void generateTree(Jobs &jobs, int n, int maxTime, int retry) {
		jobs.clear();
		jobs.resize(n);

		int to = 0;
		for (int i = n - 1; i >= 0; i--) {
			jobs.SetJobTime(i + 1, rand() % maxTime + 1);

			if (i != 0)
				for (int j = 0; j < retry; j++) {
					to = rand() % i + 1;
					if (!jobs.FindInFollows(i + 1, to))
						jobs.AddJobFollow(i + 1, to);
				}
		}
		jobs.defineCountPrev();
		jobs.refresh();
	}

	static void generateChain(Jobs &jobs, int n, int maxTime) {
		jobs.clear();
		jobs.resize(n);

		for (int i = n - 1; i >= 0; i--) {
			jobs.SetJobTime(i + 1, rand() % maxTime + 1);

			if (i != 0)
				jobs.AddJobFollow(i + 1, i + 1);
		}
		jobs.defineCountPrev();
		jobs.refresh();
	}
};