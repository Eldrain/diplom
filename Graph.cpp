#pragma once
//#include "stdafx.h"
#include "List.cpp"
#include <iostream>

class Graph {
public:
	List *first;
	int countV, countEd;
	Graph()
	{
		first = NULL;
		countV = 0;
		countEd = 0;
	}

	bool addVertex(int num) {
		if (checkVertex(num))
			return false;

		List *newVertex = new List(num);

		if (first == NULL) 
			first = newVertex;
		else {
			newVertex->next = first;
			first = newVertex;
		}
		countV++;
		return true;
	}

	bool addEdge(int fromNum, int toNum) {
		List *from = checkVertex(fromNum), *to = checkVertex(toNum);

		if (!from || !to)
			return false;

		if (from->addNode(to)) {
			countEd++;
			return true;
		} else
			return false;
	}

	bool checkEdge(int fromNum, int toNum) {
		List *from = checkVertex(fromNum);
		List::node *nowNode = NULL;
		if (!from)
			return false;
		
		nowNode = from->nodes;
		while (nowNode != NULL)
			if (nowNode->edgeTo->num == toNum)
				return true;
			else
				nowNode = nowNode->next;

		return false;
	}

	bool deleteEdge(int from, int to) {
		List *nowList = checkVertex(from);

		if (!nowList)
			return false;
		else if (nowList->deleteNode(to)) {
			countEd--;
			return true;
		} else
			return false;
	}

	bool deleteVertex(int num) {
		List *deleted = first, *prev = NULL;
		while (deleted != NULL)
			if (deleted->num == num)
				break;
			else {
				prev = deleted;
				deleted = deleted->next;
			}

		if (!deleted)
			return false;
		List *nowList = first;
		List::node *nowNode = NULL;

		while (nowList != NULL) {
			if (nowList == deleted) {
				nowList = nowList->next;
				continue;
			}
			nowList->deleteNode(num);
			nowList = nowList->next;
		}

		if (prev)
			prev->next = deleted->next;
		else
			first = deleted->next;

		delete deleted;
		deleted = NULL;
		countV--;
		return true;
	}

	List *checkVertex(int num) {
		List *now = first;
		while (now != NULL) 
			if (now->num == num)
				return now;
			else
				now = now->next;

		return NULL;
	}

	void printGraph() {
		List *nowList = first;
		List::node *nowNode = NULL;

		while (nowList != NULL) {
			std::cout << std::endl << nowList->num << ": ";
			nowNode = nowList->nodes;

			while (nowNode != NULL) {
				std::cout << nowNode->edgeTo->num << ", ";
				nowNode = nowNode->next;
			}
			nowList = nowList->next;
		}
	}

	void deleteGraph() {
		while (first != NULL)
			deleteVertex(first->num);
		countEd = 0;
	}

	int numarateAndCount() {
		List *nowList = first;
		
		int num = 1, count = 0;

		while (nowList != NULL) {
			count++;
			if (num == nowList->num)
				num++;
			nowList = nowList->next;
		}

		nowList = first;
		List *buf = first;
		while (num <= count) {
			buf = checkVertex(num);
			if (!buf) {
				while (nowList->num <= count) 
					nowList = nowList->next;
				nowList->num = num;
			}
			num++;
		}
		return count;
	}

	~Graph() {
		deleteGraph();
	}
};