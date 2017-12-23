#pragma once
//#include "stdafx.h"
#include <iostream>

template <typename T>
class Stack {
private: 
	int count;
public:
	class elem {
	public:
		T info;
		elem *next;

		elem() {
			next = NULL;
		}

		elem(T info) {
			this->info = info;
			next = NULL;
		}


	};
    class Iterator {//Class for itarating objects of stack
	public:
		elem *current_;

		Iterator() {
			current_ = NULL;
		}

		void reset(elem *first) {
			current_ = first;
		}

		bool get_next() {
			if (current_->next != NULL) {
				current_ = current_->next;
				return true;
			}
			else {
				return false;
			}
		}
	};

	elem *first;
	Iterator iterator;

	Stack() {
		first = NULL;
		count = 0;
	}

	void push(T info) {
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

	elem* pop(T info) {
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

	bool find(T info) {
		elem *el = first;
		while (el) {
			if (el->info == info)
				return true;
			el = el->next;
		}
		return false;
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
		iterator.reset(nullptr);
	}

	void swap() {
		if (first == NULL)
			return;
		elem *now = first->next, *prev = first, *next;
		while (now) {
			next = now->next;
			now->next = prev;
			prev = now;
			now = next;
		}
		first->next = NULL;
		first = prev;
	}

	void getAll(Stack &stack) {
		while (stack.first) {
			push(stack.pop());
		}
	}

	int size() {
		return count;
	}

	//Returns functioning iterator of stack with pointer to first
	Iterator *GetIterator() {
		iterator.reset(first);
		if (iterator.current_ == NULL) {
			return NULL;
		}
		else {
			return &iterator;
		}
	}

	//Returns functioning iterator of stack with pointer to element specified info
	Iterator *GetIterator(T info) {
		elem *element = NULL;
		element = pop(info);
		if (element == NULL) {
			return NULL;
		}
		else {
			iterator->reset(element);
			return &iterator;
		}	
	}

	~Stack() {
		clear();
	}
};