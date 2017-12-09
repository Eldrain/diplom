#pragma once
#include "stdafx.h"
#include "ObjectStack.cpp"
#include "Marks.cpp"

class Tree {
public:
	class leaf {
	public:
		sort::vector<int> arr_;
		int max, min, set;

		leaf() {
			max = 0;
			min = 0;
			set = 0;
		}

		leaf(int n, int set) {	
			this->set = set;
			min = 0;
			max = 0;
			arr_.resize(n);
		}

		leaf(sort::vector<int> &arr, int max, int min, int set) {
			arr_.resize(arr.size());
			arr_ = arr;
			this->min = min;
			this->max = max;
			this->set = set;
		}

		void setData(sort::vector<int> &arr, int max, int min, int set) {
			arr_ = arr;
			this->min = min;
			this->max = max;
			this->set = set;
		}

		bool operator==(leaf &l) {
			for (int i = 0; i < set; i++)
				if (arr_ != l.arr_)
					return false;
			return true;
		}

		~leaf() {
		}
	};

	int count, n;
	ObjectStack<leaf> pool, tree, wave;
	leaf *best, *prsp;

	Tree() {
		count = 0;
		this->n = 0;
		best = NULL;
		prsp = NULL;
	}

	Tree(int n) {
		count = 0;
		this->n = n;
		best = new leaf(n, 0);
		best->min = 0;
		prsp = NULL;
	}

	void init(int n) {
		this->n = n;
		delete best;
		best = new leaf(n, 0);
		
		count = 0;
		best->min = 0;
		pool.clear();
		tree.clear();
		wave.clear();
		prsp = NULL;
	}

	void findPrsp() {
		ObjectStack<leaf>::elem *l = tree.first;
		if (!l)
			return;
		int min = l->info->min;
		prsp = l->info;

		while (l) {
			if (l->info->min < min) {
				min = l->info->min;
				prsp = l->info;
			}
			l = l->next;
		}
	}

	int produce(Task &task) {
		bool seted = false;
		int mx = 0, mn = 0;
		int count = 0;
		int set = prsp->set;
		sort::vector<int> &var = prsp->arr_;

		for (int i = 0; i < n; i++) {
			seted = false;
			for (int j = 0; j < prsp->set; j++)
				if (var[j] == i + 1) {
				seted = true;
				break;
				}
			if (!seted) {
				var[set] = i + 1;
				if (!task.jobs.Check(var, set + 1)) {
					var[set] = 0;
					continue;
				}
				count++;
				addInWave(var, mx, mn, set + 1);
				var[set] = 0;
			}
		}

		pool.push(tree.pop(prsp));
		prsp = NULL;
		return count;
	}

	void marks(Marks &mark, Task &task) {
		ObjectStack<leaf>::elem *l = wave.first;
		if (!l)
			return;

		while (l) {
			l->info->max = mark.maxB(l->info->arr_, l->info->set, task);
			l->info->min = mark.minB(l->info->arr_, l->info->set, task);
			l = l->next;
		}
	}

	void cut(int &maximum) {
		ObjectStack<leaf>::elem *l = wave.first, *help = NULL;
		if (!l)
			return;

		while (l) {
			if (l->info->max < maximum){
				maximum = l->info->max;
				setBest(l->info);
			}
			if (l->info->set == n || l->info->min > maximum) {
				help = l->next;
				pool.push(wave.pop(l->info));
				l = help;
			} else
				l = l->next;
		}
	}

	void addInWave(sort::vector<int> &arr, int max, int min, int set) {
		leaf *l = NULL;
		if (pool.count > 0) {
			ObjectStack<leaf>::elem *el = pool.pop();
			l = el->info;
			l->setData(arr, max, min, set);
			el->info = NULL;
			delete el;
		}
		else {
			l = new leaf(arr, max, min, set);
			count++;
		}
		wave.push(l);
	}

	void addInWave(leaf *l) {
		wave.push(l);
		count++;
	}

	void setBest(leaf *l) {
		setBest(l->arr_, l->max);
	}

	void setBest(sort::vector<int> &arr, int min) {
		best->arr_ = arr;
		best->min = min;
	}

	void addWave() {
		tree.getAll(wave);
	}

	ObjectStack<leaf>::elem *getFirstInWave() {
		return wave.first;
	}
	
	int getMin() {
		return best->min;
	}

	bool isEmpty() {
		return tree.count == 0 ? true : false;
	}

	void printPrsp() {
		std::cout << "\nPerspective:";
		PrintLeaf(prsp);
	}

	void PrintLeaf(leaf *l) {
		for (int i = 0; i < l->set; i++)
			std::cout << l->arr_[i] << ", ";
		std::cout << "\nmin = " << l->min << ";max = " << l->max;
	}

	void printTree() {
		ObjectStack<leaf>::elem *l = tree.first;

		while (l) {
			PrintLeaf(l->info);
			l = l->next;
		}
	}

	~Tree() {
		delete best;
		best = NULL;
	}
};