#pragma once
//#include "stdafx.h"
#include <iostream>

class relations {
public:
	class job {
	public:
		int n, countPrev;
		job *to;

		job(int n, job *to, int countPrev) {
			this->n = n;
			this->to = to;
			this->countPrev = countPrev;
		}
	};

	class pack {
	public:
		class elem {
		public:
			job *now;
			elem *next;

			elem(job *now) {
				this->now = now;
			}
		};
		elem *first;

		pack() {
			first = NULL;
		}

		void add(job *newElem) {
			elem *packElem = new elem(newElem);
			packElem->next = first;
			first = packElem;
		}

		job *find(int n) {
			elem *nowPack = first;
			while (nowPack != NULL && nowPack->now->n != n) {
				nowPack = nowPack->next;
			}
			if (nowPack)
				return nowPack->now;
			else
				return NULL;
		}

		job *get(int n) {
			elem *nowPack = first, *prev = NULL;
			while (nowPack != NULL && nowPack->now->n != n) {
				prev = nowPack;
				nowPack = nowPack->next;
			}

			if (nowPack) {
				if (prev)
					prev->next = nowPack->next;
				else {
					if (first->next)
						first = first->next;
					else
						first = NULL;
				} {
					job *j = nowPack->now;
					delete nowPack;
					return j;
				}
			} else
				return NULL;
		}
	};

	pack packet;
	int countJob;

	relations() {
		countJob = 0;
	}

	relations(int countJob) {
		this->countJob = countJob;
	}

	bool complete(int n) {
		job *compJob = packet.get(n);

		if (compJob) {
			if (compJob->to) {
				compJob->to->countPrev--;
				if (compJob->to->countPrev == 0)
					packet.add(compJob->to);
			}
			delete compJob;
			return true;
		}
		else
			return false;
	}

	void packElem(job *el) {
		packet.add(el);
	}

	void prepare(int count) {
		countJob = count;
		job *getElem = NULL, *to = NULL;

		for (int i = 0; i < countJob; i++) {
			getElem = packet.find(i + 1);
			if (getElem) {
				to = packet.find((int)getElem->to);
				getElem->to = to;
			}
			else
				std::cout << "\nRelations load error! Bad file!";
		}

		for (int i = 0; i < countJob; i++) {
			getElem = packet.get(i + 1);
			if (getElem->countPrev == 0)
				packet.add(getElem);
		}
	}
	
	void clear() {
		job *help = NULL;

		while (packet.first != NULL) {
			help = packet.get(packet.first->now->n);
			if (help->to != NULL) {
				help->to->countPrev--;
				if (help->to->countPrev == 0)
					packet.add(help->to);
			}
			delete help;
		}
	}

	void print() {
		std::cout << "\nPack: ";

		pack::elem *now = packet.first;
		job *help = NULL;
		while (now != NULL) {
			std::cout << now->now->n << ", ";
			now = now->next;
		}
		std::cout << "\nRelations:";
		now = packet.first;

		while (now != NULL) {
			if (now->now->to != NULL)
				help = now->now->to;
			std::cout << std::endl << now->now->n;

			while (help != NULL) {
				std::cout << "->" << help->n;
				help = help->to;
			}
			now = now->next;
		}	
	}

	relations &operator=(const relations &from) {
		clear();
		countJob = from.countJob;

		pack::elem *now = from.packet.first;
		job *help = NULL;
		
		while (now != NULL) {
			if (now->now->to != NULL)
				help = now->now->to;
			if (packet.find(now->now->n) == NULL) {
				job *newJob = new job(now->now->n, (job*)now->now->to->n, now->now->countPrev);
				packet.add(newJob);
			}

			while (help != NULL) {
				if (packet.find(help->n) == NULL) {
					job *newJob = NULL;
					if (help->to)
						newJob = new job(help->n, (job*)help->to->n, help->countPrev);
					else
						newJob = new job(help->n, NULL, help->countPrev);
					packet.add(newJob);
				}
				else
					break;
				help = help->to;
			}
			now = now->next;
		}
		prepare(countJob);
		return *this;
	}
};