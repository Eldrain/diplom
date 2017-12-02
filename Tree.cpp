#pragma once
#include "stdafx.h"
#include "ObjectStack.cpp"
#include "Marks.cpp"

class Tree {
public:
	class leaf {
	public:
		int *arr, max, min, set;

		leaf() {
			arr = NULL;
			max = 0;
			min = 0;
			set = 0;
		}

		leaf(int n, int set) {	
			this->set = set;
			min = 0;
			max = 0;
			arr = new int[n];
		}

		leaf(int *arr, int n, int max, int min, int set) {
			this->arr = new int[n];
			copyArr(arr, n);
			this->min = min;
			this->max = max;
			this->set = set;
		}

		void setData(int *arr, int n, int max, int min, int set) {
			copyArr(arr, n);
			this->min = min;
			this->max = max;
			this->set = set;
		}

		void copyArr(int *arr, int n) {
			for (int i = 0; i < n; i++)
				this->arr[i] = arr[i];
		}

		bool operator==(const leaf &l) {
			for (int i = 0; i < set; i++)
				if (this->arr[i] != l.arr[i])
					return false;
			return true;
		}

		~leaf() {
			delete[] arr;
			arr = NULL;
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
		int set = prsp->set, *var = prsp->arr;

		for (int i = 0; i < n; i++) {
			seted = false;
			for (int j = 0; j < prsp->set; j++)
				if (var[j] == i + 1) {
				seted = true;
				break;
				}
			if (!seted) {
				var[set] = i + 1;
				if (!task.jobs.checkVar(var, set + 1)) {
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
			l->info->max = mark.maxB(l->info->arr, l->info->set, task);
			l->info->min = mark.minB(l->info->arr, l->info->set, task);
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

	void addInWave(int *arr, int max, int min, int set) {
		leaf *l = NULL;
		if (pool.count > 0) {
			ObjectStack<leaf>::elem *el = pool.pop();
			l = el->info;
			l->setData(arr, n, max, min, set);
			el->info = NULL;
			delete el;
		}
		else {
			l = new leaf(arr, n, max, min, set);
			count++;
		}
		wave.push(l);
	}

	void addInWave(leaf *l) {
		wave.push(l);
		count++;
	}

	void setBest(leaf *l) {
		setBest(l->arr, l->max);
	}

	void setBest(int *arr, int min) {
		best->copyArr(arr, n);
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
		printLeaf(prsp);
	}

	void printLeaf(leaf *l) {
		for (int i = 0; i < l->set; i++)
			std::cout << l->arr[i] << ", ";
		std::cout << "\nmin = " << l->min << ";max = " << l->max;
	}

	void printTree() {
		ObjectStack<leaf>::elem *l = tree.first;

		while (l) {
			printLeaf(l->info);
			l = l->next;
		}
	}

	/*void store(Stack<leaf>::elem *l) {
		pool.push(l);
	}

	/*leaf *addLeaf(leaf *lf) {
		if (root == NULL) {
			root = lf;
			last = lf;
			lastLevel = lf;
		}
		else if (lastLevel->level == lf->level) {
			last->brother = lf;
			last = lf;
		}
		else {
			leaf *nowLeaf = root;
			while (nowLeaf != NULL && nowLeaf->level != lf->level)
				nowLeaf = nowLeaf->nextLevel;

			if (!nowLeaf) {
				lastLevel->nextLevel = lf;
				lastLevel = lf;
				last = lf;
			}
			else {
				leaf* prev = nowLeaf;
				while (nowLeaf != NULL)
					nowLeaf = nowLeaf->brother;
				prev->brother = lf;
			}
		}
		count++;
		return lf;
	}

	leaf *addLeaf(int *arr, bool *busy, int level, int max) {
		leaf *lf = NULL;

		if (root == NULL) {
			lf = new leaf(arr, busy, level, id, max);
			root = lf;
			last = lf;
			lastLevel = lf;
		}
		else if (lastLevel->level == level) {
			lf = new leaf(arr, busy, level, id, max);
			last->brother = lf;
			last = lf;
		}
		else {
			lf = root;
			while (lf != NULL && lf->level != level)
				lf = lf->nextLevel;

			if (!lf) {
				lf = new leaf(arr, busy, level, id, max);
				lastLevel->nextLevel = lf;
				lastLevel = lf;
				last = lf;
			}
			else {
				leaf* prev = lf;
				while (lf != NULL)
					lf = lf->brother;
				lf = new leaf(arr, busy, level, id, max);
				prev->brother = lf;
			}
		}
		count++;
		id++;
		return lf;
	}

	bool levelInPool(int level) {
		if (level == 0)
			return false;
		leaf *lf = root;
		while (lf != NULL && lf->level != level)
			lf = lf->nextLevel;

		if (!lf)
			return false;
		else {
			count -= pool.addElem(lf->brother);
			lf->brother = NULL;
			return true;
		}
	}

	bool elemInPool(int id, int level) {
		leaf *nowLeaf = NULL, *prev = NULL;

		if (lastLevel->id == id) {
			nowLeaf = root;
			while (nowLeaf != lastLevel) {
				prev = nowLeaf;
				nowLeaf = nowLeaf->nextLevel;
			}
			if (nowLeaf->brother == NULL) {
				prev->nextLevel = NULL;
				lastLevel = prev;
				while (prev != NULL) {
					last = prev;
					prev = prev->brother;
				}
			}
			else {
				prev->nextLevel = nowLeaf->brother;
				lastLevel = nowLeaf->brother;
			}
		}
		else if (lastLevel->level == level) {
			nowLeaf = lastLevel;
			while (nowLeaf->id != id) {
				prev = nowLeaf;
				nowLeaf = nowLeaf->brother;
			}
			prev->brother = nowLeaf->brother;
			if (nowLeaf == last)
				last = prev;
		}
		else {
			nowLeaf = root;
			while (nowLeaf->level != level) {
				prev = nowLeaf;
				nowLeaf = nowLeaf->nextLevel;
			}
			while (nowLeaf->id != id) {
				prev = nowLeaf;
				nowLeaf = nowLeaf->nextLevel;
			}
			if (nowLeaf->nextLevel == NULL)
				prev->brother = nowLeaf->brother;
			else {
				if (nowLeaf->brother == NULL)
					prev->nextLevel = nowLeaf->nextLevel;
				else {
					prev->nextLevel = nowLeaf->brother;
					nowLeaf->brother->nextLevel = nowLeaf->nextLevel;
				}
			}
		}
		if (nowLeaf) {
			count -= pool.addElem(nowLeaf->brother);
			nowLeaf = NULL;
			return true;
		}
		else
			return false;
	}

	bool deleteFirst() {
		if (!root)
			return false;
		else {
			leaf *nowLeaf = root;
			if (last == root) {
				last = NULL;
				root = NULL;
				lastLevel = NULL;
			}
			else if (root->brother == NULL)
				root = root->nextLevel;
			else {
				root->brother->nextLevel = root->nextLevel;
				root = root->brother;
			}

			delete nowLeaf;
			nowLeaf = NULL;
			count--;
			return true;
		}
	}

	bool deleteId(int id, int level) {
		leaf *nowLeaf = NULL, *prev = NULL;

		if (lastLevel->id == id) {
			nowLeaf = root;
			while (nowLeaf != lastLevel) {
				prev = nowLeaf;
				nowLeaf = nowLeaf->nextLevel;
			}
			if (nowLeaf->brother == NULL) {
				prev->nextLevel = NULL;
				lastLevel = prev;
				while (prev != NULL) {
					last = prev;
					prev = prev->brother;
				}
			}
			else {
				prev->nextLevel = nowLeaf->brother;
				lastLevel = nowLeaf->brother;
			}
		}
		else if (lastLevel->level == level) {
			nowLeaf = lastLevel;
			while (nowLeaf->id != id) {
				prev = nowLeaf;
				nowLeaf = nowLeaf->brother;
			}
			prev->brother = nowLeaf->brother;
			if (nowLeaf == last)
				last = prev;
		}
		else {
			nowLeaf = root;
			while (nowLeaf->level != level) {
				prev = nowLeaf;
				nowLeaf = nowLeaf->nextLevel;
			}
			while (nowLeaf->id != id) {
				prev = nowLeaf;
				nowLeaf = nowLeaf->nextLevel;
			}
			if (nowLeaf->nextLevel == NULL)
				prev->brother = nowLeaf->brother;
			else {
				if (nowLeaf->brother == NULL)
					prev->nextLevel = nowLeaf->nextLevel;
				else {
					prev->nextLevel = nowLeaf->brother;
					nowLeaf->brother->nextLevel = nowLeaf->nextLevel;
				}
			}
		}
		if (nowLeaf) {
			delete nowLeaf;
			nowLeaf = NULL;
			count--;
			return true;
		}
		else
			return false;
	}

	bool deletePrev(leaf *prev) {
		if (prev) {
			leaf *nowLeaf = prev->brother;
			prev->brother = nowLeaf->brother;
			count--;
			delete nowLeaf;
			nowLeaf = NULL;
			return true;
		}
		else
			return false;
	}

	void clearTree() {
		std::cout << "\n������� ������...";
		while (deleteFirst());
		id = 0;
	}

	void printTree() {
		//if (id > 500) {
		std::cout << "id = " << id << "; count = " << count;
		/*}
			else {
			leaf *nowLeaf = root, *nextLevel = NULL;
			while (nowLeaf != NULL) {
			std::cout << std::endl << "Level:" << nowLeaf->level;
			nextLevel = nowLeaf->nextLevel;
			while (nowLeaf != NULL) {
			std::cout << std::endl << "ID: " << nowLeaf->id << "| Max =" << nowLeaf->max << ", Min = " << nowLeaf->min << " | ";
			printArr(nowLeaf->arr, countV);
			nowLeaf = nowLeaf->brother;
			}
			nowLeaf = nextLevel;
			}
		}*/
	

	~Tree() {
		delete best;
		best = NULL;
	}
};