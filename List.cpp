#pragma once

#include "stdafx.h"

class List {
public:
	class node
	{
	public:
		node *next;
		List *edgeTo;

		node(node *next, List *edgeTo)
		{
			this->edgeTo = edgeTo;
			this->next = next;
		}

		node(List *edgeTo)
		{
			this->edgeTo = edgeTo;
			this->next = NULL;
		}

		~node()
		{
			next = NULL;
			edgeTo = NULL;
		}
	};

	int num;
	node *nodes;
	List *next;

	List(int num)
	{
		this->num = num;
		nodes = NULL;
		next = NULL;
	}

	bool addNode(List *to)
	{
		node *now = this->nodes;

		while (now != NULL)
			if (now->edgeTo == to)
				return false;
			else
				now = now->next;

		this->nodes = new node(this->nodes, to);
		return true;
	}

	bool deleteNode(int num) {
		node *now = this->nodes, *prev = NULL;

		while (now != NULL)
			if (now->edgeTo->num == num) {
				if (prev)
					prev->next = now->next;
				else
					this->nodes = now->next;
				delete now;
				now = NULL;
				return true;
			} else {
				prev = now;
				now = now->next;
			}
		return false;
	}

	~List() {
		while (nodes)
			deleteNode(nodes->edgeTo->num);
		next = NULL;
	}
};