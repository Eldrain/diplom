#pragma once
//#include "stdafx.h"
#include <iostream>

template <typename T>
class ObjectStack { 
public:
	class elem {
	public:
		T *info;
		elem *next;

		elem() {
			info = NULL;
			next = NULL;
		}

		elem(T *info) {
			this->info = info;
			next = NULL;
		}

		~elem() {
			delete info;
			info = NULL;
		}
	};

	elem *first;
	int count;

	ObjectStack() {
		first = NULL;
		count = 0;
	}

	void push(T *info) {
		elem *newElem = new elem(info);
		newElem->next = first;
		first = newElem;
		count++;
	}

	void push(elem *el) {
		if (!el)
			return;
		el->next = first;
		first = el;
		count++;
	}

	elem* pop() {
		if (first) {
			elem *el = first;
			first = first->next;
			count--;
			return el;
		}
		else
			return NULL;
	}

	elem* pop(T *info) {
		elem *el = first, *prev = NULL;

		while (el) {
			if (el->info == info)
				break;
			prev = el;
			el = el->next;
		}
		if (el == NULL)
			return NULL;
		if (prev)
			prev->next = el->next;
		else {
			if (first->next)
				first = first->next;
			else
				first = NULL;
		}
		count--;
		return el;
	}

	void print() {
		elem *now = first;
		while (now != NULL) {
			std::cout << now->info << ", ";
			now = now->next;
		}
	}

	void clear() {
		elem *el = NULL;
		while (first) {
			el = pop();
			delete el;
		}
	}

	void getAll(ObjectStack &stack) {
		while (stack.first) {
			push(stack.pop());
		}
	}

	~ObjectStack() {
		clear();
	}
};