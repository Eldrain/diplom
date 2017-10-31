#include "stdafx.h"
#include "Graph.cpp"
#include "ListOC.cpp"
#include "Tree.cpp"
#include "Variant.cpp"
#include <ctime>

class Task {
	Tree tree;
	List *first;
	ListOC **edges, **degreeV;
	elemPool pool;
	elem *recElem;
	int record, recordVG, *best, *bestVG;
	int countEd, countV, factorial, deleted;
	int *arr, *bufferArr;
	bool *buffer;

public:
	double time, timeMin, timeMax, timeValue, nowTime, nowTime2, timeMem, timeCheck, delPerc;

	Task() {
		arr = NULL;
		bufferArr = NULL;
		first = NULL;
		best = NULL;
		bestVG = NULL;
		buffer = NULL;
		degreeV = NULL;
		edges = NULL;
		recElem = NULL;

		countV = 0;
		delPerc = 0;
		countEd = 0;
		factorial = 0;
	}

	void newTask(int *arr, Graph &graph) {
		deleteLists();
		if (countV != graph.countV) {
			tree.pool.clearPool();
			pool.clearPool();
		}
		countV = graph.numarateAndCount();
		countEd = graph.countEd;
		first = graph.first;
		tree.countV = countV;
		delete[] buffer;
		delete[] bufferArr;
		buffer = new bool[countV];
		bufferArr = new int[countV];

		this->arr = arr;
		sortArray(this->arr);
		fillLists(graph);
	}

	void printArray(int *arr, int n) {
		std::cout << std::endl;
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << ", ";
	}

	/*void prepareArr() {
		int maxWeight = 0, glass = 0, *help = NULL, i = 0;
		help = new int[countV];

		for (i = 0; i < countV; i++) {
			bufferArr[i] = 0;
			for (int k = 0; k < countV; k++)
				bufferArr[i] += abs(arr[k] - arr[i]);
		}

		printArray(arr, countV);
		printArray(bufferArr, countV);
		for (int k = 0; k < countV; k++) {
			maxWeight = 0;
			for (i = 0; i < countV; i++) 
				if (bufferArr[i] > maxWeight) {
					maxWeight = bufferArr[i];
					glass = i;
				}
			bufferArr[glass] = 0;
			help[k] = glass;
		}
		printArray(help, countV);
		for (i = 0; i < countV; i++) 
			bufferArr[i] = arr[help[i]];
		
		delete[] help;
		help = arr;
		arr = bufferArr;
		bufferArr = help;
		printArray(arr, countV);
	}*/

	void edgeInTop(int from, int num, int vertex) {
		ListOC *help = edges[num];
		bool into = false;
		for (; from < countEd; from++) {
			if (edges[from] == NULL)
				return;
			else if (edges[from]->num1 == vertex || edges[from]->num2 == vertex) {
				into = true;
				if (!into && from == num)
					return;
				else if (into && !edges[from]->twice)
					break;		
			}
			else if (into)
				return;
		}
		edges[num] = edges[from];
		edges[from] = help;
	}

	void fillLists(Graph &graph) {
		newLists();
		List *nowList = graph.first;
		List::node *nowNode = NULL;
		int i = 0, k = 0, vertex = 0, edArr = 0;

		int *degrees = new int[countV];
		for (; i < countV; i++)
			degrees[i] = 0;
		i = 0;

		while (nowList != NULL) {
			nowNode = nowList->nodes;
			while (nowNode != NULL) {
				if (nowNode->edgeTo != nowList) {
					degrees[nowList->num - 1]++;
					degrees[nowNode->edgeTo->num - 1]++;
				}
				else
					countEd--;
				nowNode = nowNode->next;
			}
			nowList = nowList->next;
		}

		int max = -1, from = 0;
		for (i = 0; i < countV; i++)
			if (degrees[i] > max) {
			max = degrees[i];
			vertex = i + 1;
			}

		while (max != 0) {
			from = edArr;
			degreeV[k] = new ListOC(vertex, degrees[vertex - 1]);
			k++;
			nowList = graph.checkVertex(vertex);
			nowNode = nowList->nodes;
			while (nowNode != NULL) {
				if (!checkInArr(nowNode->edgeTo->num, k) && nowNode->edgeTo != nowList) {
					edges[edArr] = new ListOC(nowList->num, nowNode->edgeTo->num);
					
					if (graph.checkEdge(nowNode->edgeTo->num, nowList->num) != NULL) {
						edges[edArr]->twice = true;
						edgeInTop(from, edArr, vertex);
						degrees[nowList->num - 1]--;
						degrees[nowNode->edgeTo->num - 1]--;
						degreeV[k - 1]->num2--;
						countEd--;
					}
					edArr++;
					degrees[nowList->num - 1]--;
					degrees[nowNode->edgeTo->num - 1]--;
				}
				nowNode = nowNode->next;
			}

			nowList = graph.first;
			while (degrees[vertex - 1] != 0) {
				if (nowList->num == vertex || checkInArr(nowList->num, k)) {
					nowList = nowList->next;
					continue;
				}
				nowNode = nowList->nodes;

				while (nowNode != NULL) {
					if (nowNode->edgeTo->num == vertex && !checkEdgeInArr(vertex, nowList->num, edArr)) {
						edges[edArr] = new ListOC(nowList->num, vertex);
						edArr++;
						degrees[nowList->num - 1]--;
						degrees[vertex - 1]--;
					}
					nowNode = nowNode->next;
				}
				nowList = nowList->next;
			}

			max = -1;
			for (i = 0; i < countV; i++)
				if (degrees[i] > max) {
				max = degrees[i];
				vertex = i + 1;
				}
		}
		//printListEdge();
	}

	void printListEdge() {
		ListOC *elem = *edges;
		int i = 0;
		while (elem != NULL) {
			std::cout << std::endl << elem->num1 << "-->" << elem->num2 << " twice: " << (elem->twice ? "+" : "-");
			i++;
			elem = edges[i];
		}
	}
	
	bool checkEdgeInArr(int from, int to, int count) {
		for (int i = 0; i < count; i++)
			if (edges[i]->num1 == from && edges[i]->num2 == to)
				return true;
		return false;
	}

/*	void fillMaxLine() {	
		prepareArr();

		for (int i = 0; i < countV; i++) {
			for (int k = 0; k < countV; k++)
				bufferArr[k] = abs(arr[i] - arr[k]);
			sortMaxLine(i);	
		}
	}

	void sortMaxLine(int num) {
		int weight = 0, glass = 0;
		for (int i = 0; i < countV; i++) {
			weight = 0;
			for (int k = 0; k < countV; k++)
				if (bufferArr[k] > weight) {
					weight = bufferArr[k];
					glass = k;
				}
			maxLine[num][glass].num1 = glass + 1;
			maxLine[num][glass].num2 = weight;
			bufferArr[glass] = 0;
		}
	}*/

	void newLists() {
		edges = new ListOC*[countEd];
		degreeV = new ListOC*[countV / 2 + 1];
		//maxLine = new ListOC*[countV];

		//for (int i = 0; i < countV; i++)
		//	maxLine[i] = new ListOC[countV];
		for (int i = 0; i < countV / 2 + 1; i++)
			degreeV[i] = NULL;
		for (int i = 0; i < countEd; i++)
			edges[i] = NULL;
	}

	void deleteLists() {
		if (edges) {
			for (int i = 0; i < countEd; i++) {
				delete edges[i];
				edges[i] = NULL;
			}
			edges = NULL;
		}
		if (degreeV) {
			for (int i = 0; i < countV / 2 + 1; i++) {
				delete degreeV[i];
				degreeV[i] = NULL;
			}
			degreeV = NULL;
		}
		/*if (maxLine) {
			for (int i = 0; i < countV; i++) {
				delete[] maxLine[i];
				maxLine[i] = NULL;
			}
			maxLine = NULL;
		}*/
	}

	bool checkInArr(int num, int count) {
		for (int i = 0; i < count; i++)
			if (degreeV[i]->num1 == num)
				return true;
		return false;
	}

	void sortArray(int *arr) {
		int now = arr[0], i;
		for (int k = 0; k < countV; k++) {
			now = arr[k];
			for (i = k; i < countV; i++)
				if (now < arr[i]) {
				arr[k] = arr[i];
				arr[i] = now;
				now = arr[k];
				}
		}
	}

	int sortOut() {
		if (best)
			delete[] best;
		best = NULL;
		int f = 0;
		record = -1;
		time = clock();
		f = sortOut(NULL, 0);
		time = (clock() - time) / 1000;
		return f;
	}

	int sortOut(int *arr, int num) {
		if (!arr) {
			arr = new int[countV];
			for (int i = 0; i < countV; i++)
				arr[i] = 0;
		}

		if (num < countV - 1) {
			for (int i = 0; i < countV; i++)
				if (arr[i] == 0) {
				int *buffer = new int[countV];
				for (int k = 0; k < countV; k++)
					buffer[k] = arr[k];
				buffer[i] = this->arr[num];
				sortOut(buffer, num + 1);
				}
			delete[] arr;
		}
		else {
			int i = 0;
			while (num < countV) {
				if (arr[i] == 0) {
					arr[i] = this->arr[num];
					num++;
				}
				i++;
			}
			i = value(arr);
			if (i > record) {
				record = i;
				delete[] best;
				best = arr;
			}
			else {
				delete[] arr;
				arr = NULL;
			}
		}

		return record;
	}

	int value(int *arr) {
		nowTime = clock();
		List *nowList = first;
		List::node *nowNode = NULL;
		int value = 0;

		while (nowList != NULL) {
			nowNode = nowList->nodes;

			while (nowNode != NULL) {
				value += abs(arr[nowList->num - 1] - arr[nowNode->edgeTo->num - 1]);
				nowNode = nowNode->next;
			}
			nowList = nowList->next;
		}
		timeValue += clock() - nowTime;
		return value;
	}

	int abs(int s) {
		if (s < 0)
			return -s;
		else
			return s;
	}

	void printBest() {
		for (int i = 0; i < countV; i++)
			std::cout << best[i] << ", ";
	}

	void printBestVG() {
		for (int i = 0; i < countV; i++)
			std::cout << bestVG[i] << ", ";
	}

	void prepareTree() {
		tree.clearTree();
		tree.addLeaf(0);
		tree.root->busy = new bool[countV];
		tree.root->arr = new int[countV];

		for (int i = 0; i < countV; i++) {
			tree.root->busy[i] = false;
			tree.root->arr[i] = 0;
		}
	}

	void prepareRoot(elem *root){
		root->busy = new bool[countV];
		root->arr = new int[countV];

		for (int i = 0; i < countV; i++) {
			root->busy[i] = false;
			root->arr[i] = 0;
		}
	}
	
	int startVG() {
		int minimum = 0;
		elem *root = new elem(0);
		clearBuffer();
		clearBufferArr();
		prepareRoot(root); //prepareTree();
		std::cout << "\nРешение...";
		timeCheck = 0;
		timeMem = 0;
		timeMin = 0;
		timeMax = 0;
		timeValue = 0;
		nowTime = 0;
		deleted = 0;

		recordVG = 0;
		recElem = NULL;

		time = clock();
		root->max = max(root->arr, root->busy);
		upMethodVG(root, minimum);
		checkAnswer(recElem);
		time = (clock() - time) / 1000;

		//tree.printTree();
		return recordVG;
	}

	void upMethodVG(elem *nowVar, int &minimum) {
		min(nowVar);
		if (nowVar->min > minimum)
			minimum = nowVar->min;

		if (nowVar->min == nowVar->max) {
			if (nowVar->min > recordVG) {
				if (!recElem)
					pool.addElem(recElem);
				recordVG = nowVar->min;
				recElem = nowVar;
			}
			else
				pool.addElem(nowVar);
			return;
		}

		elem *el = pool.getElem();
		int mx = 0;
		int *buffer = NULL;
		bool *boolBuf = NULL;
		factorial = fact(countV - nowVar->level);
		if (el) {
			buffer = el->arr;
			boolBuf = el->busy;
		}
		else {
			buffer = new int[countV];
			boolBuf = new bool[countV];
		}
		
		
		for (int i = 0; i < countV; i++)
			if (nowVar->max >= minimum) {
				if (nowVar->arr[i] == 0) {
					for (int k = 0; k < countV; k++) {
						buffer[k] = nowVar->arr[k];
						boolBuf[k] = nowVar->busy[k];
					}
					buffer[i] = this->arr[nowVar->level];
					boolBuf[nowVar->level] = true;
					mx = max(buffer, boolBuf);

					if (mx >= minimum) {
						if (el) {
							el->max = mx;
							el->level = nowVar->level + 1;
							upMethodVG(el, minimum);
							el = pool.getElem();
							if (el) {
								buffer = el->arr;
								boolBuf = el->busy;
							}
							else {
								buffer = new int[countV];
								boolBuf = new bool[countV];
							}
						}
						else {
							upMethodVG(new elem(buffer, boolBuf, nowVar->level + 1, mx), minimum);
							buffer = new int[countV];
							boolBuf = new bool[countV];
						}
					}
					else
						deleted += factorial;
				}
			}
			else
				break;
		pool.addElem(nowVar);
		if (el) {
			pool.addElem(el);
			el = NULL;
		}
		else {
			delete[] buffer;
			delete[] boolBuf;
			boolBuf = NULL;
			buffer = NULL;
		}
	}

	/*int methodVG() {
		Tree::leaf *nowLeaf = NULL;
		int minimum = 0, level = 0, maximum = 0;

		while (1) {
			calculationVG(nowLeaf, minimum, maximum);
			nowTime = clock();
			nowLeaf = checkEnd(nowLeaf, minimum, maximum, level);
			timeCheck += clock() - nowTime;
			if (nowLeaf)
				break;
			level++;
			nowTime2 = clock();
			newVars(nowLeaf, level, minimum);
			if (level != 1)
				tree.levelInPool(level - 1);
			//tree.printTree();
			timeMem += clock() - nowTime2;
		}
		checkAnswer(nowLeaf);
		bestVG = nowLeaf->arr;
		return nowLeaf->max;
	}*/

	void newVars(Tree::leaf *nowLeaf, int level, int minimum) {
		Tree::leaf *leafBuf = tree.pool.getElem();
		nowLeaf = tree.lastLevel;
		int mx = 0;
		int *buffer = NULL;
		bool *boolBuf = NULL;
		factorial = fact(countV - level);
		if (leafBuf) {
			buffer = leafBuf->arr;
			boolBuf = leafBuf->busy;
		}
		else {
			buffer = new int[countV];
			boolBuf = new bool[countV];
		}
		while (nowLeaf != NULL) {
			if (nowLeaf->max >= minimum) {
				for (int i = 0; i < countV; i++)
					if (nowLeaf->arr[i] == 0) {
						for (int k = 0; k < countV; k++) {
							buffer[k] = nowLeaf->arr[k];
							boolBuf[k] = nowLeaf->busy[k];
						}
						buffer[i] = this->arr[level - 1];
						boolBuf[level - 1] = true;
						mx = max(buffer, boolBuf);
						if (mx >= minimum) {
							if (leafBuf) {
								leafBuf->max = mx;
								leafBuf->level = level;
								tree.addLeaf(leafBuf);
								leafBuf = tree.pool.getElem();
								if (leafBuf) {
									buffer = leafBuf->arr;
									boolBuf = leafBuf->busy;
								}
								else {
									buffer = new int[countV];
									boolBuf = new bool[countV];
								}
							}
							else {
								tree.addLeaf(buffer, boolBuf, level, mx);
								buffer = new int[countV];
								boolBuf = new bool[countV];
							}
						} else
							deleted += factorial;
					}
			} 
			nowLeaf = nowLeaf->brother;
		}
		if (leafBuf) {
			delete leafBuf;
			leafBuf = NULL;
		} else {
			delete[] buffer;
			delete[] boolBuf;
			boolBuf = NULL;
			buffer = NULL;
		}
	}

	void calculationVG(Tree::leaf *nowLeaf, int &minimum, int &maximum) {
		nowLeaf = tree.lastLevel;
		maximum = 0;
		while (nowLeaf != NULL) {
			min(nowLeaf);
			if (nowLeaf->min > minimum)
				minimum = nowLeaf->min;
			if (nowLeaf->max > maximum)
				maximum = nowLeaf->max;
			nowLeaf = nowLeaf->brother;
		}
	}

	Tree::leaf *checkEnd(Tree::leaf *nowLeaf, int &minimum, int &maximum, int level) {
		Tree::leaf *prev = NULL;
		int deleteId = 0;
		nowLeaf = tree.lastLevel;
		while (nowLeaf != NULL) {
			if (nowLeaf->min == nowLeaf->max && nowLeaf->max == maximum)
				return nowLeaf;
			/*			if (nowLeaf->max <= minimum) {
							if (tree.deletePrev(prev))
							nowLeaf = prev->brother;
							else {
							deleteId = nowLeaf->id;
							nowLeaf = nowLeaf->brother;
							tree.deleteId(deleteId, level);
							}
							} 	*/
			else {
				prev = nowLeaf;
				nowLeaf = nowLeaf->brother;
			}
		}
		return nowLeaf;
	}

	void checkAnswer(elem *el) {
		for (int i = 0; i < countV; i++)
			if (el->arr[i] == 0) {
				min(el);
			for (int k = 0; k < countV; k++)
				el->arr[k] = bufferArr[k];
			break;
			}
		bestVG = el->arr;
	}

	int max(int *leafArr, bool *busy) {
		nowTime = clock();
		int i = 0, nowVertex = 0, countInc = 0, completeEdges = 0, minProfit = 0, maxProfit = 0, max = 0;

		clearBuffer();
		while (completeEdges != countEd) {
			nowVertex = degreeV[i]->num1;
			countInc = degreeV[i]->num2;
			if (leafArr[nowVertex - 1] == 0)
				max += calculateMax1(leafArr, busy, nowVertex, completeEdges, completeEdges + countInc);
			else
				max += calculateMax2(leafArr, busy, nowVertex, completeEdges, completeEdges + countInc);

			i++;
			completeEdges += countInc;
		}
		timeMax += clock() - nowTime;
		return max;
	}

	void min(Tree::leaf *leaf) {
		nowTime = clock();
		int completeEdges = 0, nowV = 0, toVertex = 0, useMax = 0, useMin = countV - 1, countInc = 0, need = 0, set = 0;
		clearBuffer();
		clearBufferArr();

		while (set != countV) {
			countInc = degreeV[nowV]->num2;

			if (leaf->arr[degreeV[nowV]->num1 - 1] == 0) {
				if (bufferArr[degreeV[nowV]->num1 - 1] == 0) {
					useMax = setUsing(leaf, 0, true);
					bufferArr[degreeV[nowV]->num1 - 1] = arr[useMax];
					buffer[useMax] = true;
					useMax++;
					set++;
				}
				for (int i = completeEdges; i < completeEdges + countInc; i++) {
					if (edges[i]->num1 == degreeV[nowV]->num1) {
						need = leaf->arr[edges[i]->num2 - 1];
						toVertex = edges[i]->num2;
					}
					else {
						need = leaf->arr[edges[i]->num1 - 1];
						toVertex = edges[i]->num1;
					}
					if (bufferArr[toVertex - 1] == 0) {
						if (need == 0) {
							useMin = setUsing(leaf, useMin, false);
							bufferArr[toVertex - 1] = arr[useMin];
							buffer[useMin] = true;
							useMin--;
						}
						else
							bufferArr[toVertex - 1] = need;
						set++;
						if (set == countV)
							break;
					}
				}
			}
			else {
				if (bufferArr[degreeV[nowV]->num1 - 1] == 0) {
					bufferArr[degreeV[nowV]->num1 - 1] = leaf->arr[degreeV[nowV]->num1 - 1];
					set++;
					if (set == countV)
						break;
				}
				bool max = needMax(leaf->arr[degreeV[nowV]->num1 - 1]);
				for (int i = completeEdges; i < completeEdges + countInc; i++) {
					if (edges[i]->num1 == degreeV[nowV]->num1) {
						need = leaf->arr[edges[i]->num2 - 1];
						toVertex = edges[i]->num2;
					}
					else {
						need = leaf->arr[edges[i]->num1 - 1];
						toVertex = edges[i]->num1;
					}
					if (bufferArr[toVertex - 1] == 0) {
						if (need == 0) {
							if (max) {
								useMax = setUsing(leaf, useMax, true);
								bufferArr[toVertex - 1] = arr[useMax];
								buffer[useMax] = true;
								useMax++;
							}
							else {
								useMin = setUsing(leaf, useMin, false);
								bufferArr[toVertex - 1] = arr[useMin];
								buffer[useMin] = true;
								useMin--;
							}
						}
						else
							bufferArr[toVertex - 1] = need;
						set++;
						if (set == countV)
							break;
					}
				}
			}
			completeEdges += countInc;
			nowV++;
			//Test::printArray(bufferArr, countV);
		}
		leaf->min = value(bufferArr);
		timeMin += clock() - nowTime;
	}

	void min(elem *el) {
		nowTime = clock();
		int completeEdges = 0, nowV = 0, toVertex = 0, useMax = 0, useMin = countV - 1, countInc = 0, need = 0, set = 0;
		clearBuffer();
		clearBufferArr();

		while (set != countV) {
			countInc = degreeV[nowV]->num2;

			if (el->arr[degreeV[nowV]->num1 - 1] == 0) {
				if (bufferArr[degreeV[nowV]->num1 - 1] == 0) {
					useMax = setUsing(el, 0, true);
					bufferArr[degreeV[nowV]->num1 - 1] = arr[useMax];
					buffer[useMax] = true;
					useMax++;
					set++;
				}
				for (int i = completeEdges; i < completeEdges + countInc; i++) {
					if (edges[i]->num1 == degreeV[nowV]->num1) {
						need = el->arr[edges[i]->num2 - 1];
						toVertex = edges[i]->num2;
					}
					else {
						need = el->arr[edges[i]->num1 - 1];
						toVertex = edges[i]->num1;
					}
					if (bufferArr[toVertex - 1] == 0) {
						if (need == 0) {
							useMin = setUsing(el, useMin, false);
							bufferArr[toVertex - 1] = arr[useMin];
							buffer[useMin] = true;
							useMin--;
						}
						else
							bufferArr[toVertex - 1] = need;
						set++;
						if (set == countV)
							break;
					}
				}
			}
			else {
				if (bufferArr[degreeV[nowV]->num1 - 1] == 0) {
					bufferArr[degreeV[nowV]->num1 - 1] = el->arr[degreeV[nowV]->num1 - 1];
					set++;
					if (set == countV)
						break;
				}
				bool max = needMax(el->arr[degreeV[nowV]->num1 - 1]);
				for (int i = completeEdges; i < completeEdges + countInc; i++) {
					if (edges[i]->num1 == degreeV[nowV]->num1) {
						need = el->arr[edges[i]->num2 - 1];
						toVertex = edges[i]->num2;
					}
					else {
						need = el->arr[edges[i]->num1 - 1];
						toVertex = edges[i]->num1;
					}
					if (bufferArr[toVertex - 1] == 0) {
						if (need == 0) {
							if (max) {
								useMax = setUsing(el, useMax, true);
								bufferArr[toVertex - 1] = arr[useMax];
								buffer[useMax] = true;
								useMax++;
							}
							else {
								useMin = setUsing(el, useMin, false);
								bufferArr[toVertex - 1] = arr[useMin];
								buffer[useMin] = true;
								useMin--;
							}
						}
						else
							bufferArr[toVertex - 1] = need;
						set++;
						if (set == countV)
							break;
					}
				}
			}
			completeEdges += countInc;
			nowV++;
			//Test::printArray(bufferArr, countV);
		}
		el->min = value(bufferArr);
		timeMin += clock() - nowTime;
	}

	void clearBufferArr() {
		for (int i = 0; i < countV; i++)
			bufferArr[i] = 0;
	}

	void clearBuffer() {
		for (int i = 0; i < countV; i++)
			buffer[i] = false;
	}

	int calculateMax1(int *leafArr, bool *busy, int nowVertex, int from, int to) {
		int minProfit = 0, maxProfit = 0, need = 0, max = 0, useMax = 0, useMin = 0, useMinNow = 0, useMaxNow = 0;
		bool useMaxBool = true;
		
		useMax = setUsing(busy, true);
		useMin = setUsing(busy, false);
		useMaxNow = useMax;
		useMinNow = useMin;

		for (; from < to; from++) {
			if (edges[from]->num1 == nowVertex)
				need = leafArr[edges[from]->num2 - 1];
			else
				need = leafArr[edges[from]->num1 - 1];
			if (need > 0) {
				minProfit += abs(need - arr[useMin]) * ((edges[from]->twice) ? 2 : 1);
				maxProfit += abs(arr[useMax] - need) * ((edges[from]->twice) ? 2 : 1);
			}
			else {
				minProfit += abs(arr[useMin] - arr[useMaxNow]) * ((edges[from]->twice) ? 2 : 1);
				useMaxNow++;
				useMaxNow = setUsing(busy, useMaxNow, true);
				maxProfit += abs(arr[useMax] - arr[useMinNow]) * ((edges[from]->twice) ? 2 : 1);
				useMinNow--;
				useMinNow = setUsing(busy, useMinNow, false);
			}
		}

		if (maxProfit >= minProfit) {
			//buffer[useMax] = true;
			return maxProfit;
		}
		else {
			//buffer[useMin] = true;
			return minProfit;
		}
		/*weightFromV = setUsing(leaf, useMaxBool);
		weightToV = setUsing(leaf, !useMaxBool);

		for (; from < to; from++) {
		if (edges[from]->num1 == nowVertex)
		need = leaf->arr[edges[from]->num2 - 1];
		else
		need = leaf->arr[edges[from]->num1 - 1];

		if (need == 0) {
		max += abs(arr[weightFromV] - arr[weightToV]);
		if (useMaxBool)
		weightToV--;
		else
		weightToV++;
		weightToV = setUsing(leaf, weightToV, !useMaxBool);
		}
		else
		max += abs(arr[weightFromV] - need);
		}

		return max;*/
	}

	int calculateMax2(int *leafArr, bool *busy, int nowVertex, int from, int to) {
		int weight = leafArr[nowVertex - 1], need = 0, i = 0, max = 0;

		for (i = 0; i < countV; i++)
			if (busy[i] == false && buffer[i] == false)
				bufferArr[i] = abs(this->arr[i] - weight);
			else
				bufferArr[i] = 0;
		sortArray(bufferArr);
		i = 0;

		for (; from < to; from++) {
			if (edges[from]->num1 == nowVertex)
				need = leafArr[edges[from]->num2 - 1];
			else
				need = leafArr[edges[from]->num1 - 1];

			if (need == 0) {
				max = max + bufferArr[i] * ((edges[from]->twice) ? 2 : 1);
				i++;
			}
			else
				max += abs(weight - need) * ((edges[from]->twice) ? 2 : 1);
		}
		return max;
	}

	/*int setUsingNow(int numInArr, int from, bool *busy) {
		for (int i = from; i < countV; i++)
			if (!buffer[maxLine[numInArr][i].num1 - 1] && !busy[maxLine[numInArr][i].num1 - 1])
				return i;
	}*/

	int setUsing(elem *el, int from, bool useMax) {
		int result = from;
		if (useMax)
			while (el->busy[result] != false || buffer[result] != false)
				result++;
		else
			while (el->busy[result] != false || buffer[result] != false)
				result--;

		return result;
	}

	int setUsing(Tree::leaf *leaf, int from, bool useMax) {
		int result = from;
		if (useMax)
			while (leaf->busy[result] != false || buffer[result] != false)
				result++;
		else
			while (leaf->busy[result] != false || buffer[result] != false)
				result--;

		return result;
	}

	int setUsing(Tree::leaf *leaf, bool useMax) {
		int result = 0;
		if (useMax)
			while (leaf->busy[result] != false || buffer[result] != false)
				result++;
		else {
			result = countV - 1;
			while (leaf->busy[result] != false || buffer[result] != false)
				result--;
		}

		return result;
	}

	/*int setUsing(Tree::leaf *leaf) {
		int result = 0;
		while (1)
			if (leaf->busy[result] == false)
				return result;
			else if (leaf->busy[countV - result - 1] == false)
				return countV - result - 1;
			else
				result++;
	}*/

	int setUsing(bool *busy, int from, bool useMax) {
		int result = from;
		if (useMax)
			while (busy[result] != false || buffer[result] != false)
				result++;
		else
			while (busy[result] != false || buffer[result] != false)
				result--;

		return result;
	}

	int setUsing(bool *busy, bool useMax) {
		int result = 0;
		if (useMax)
			while (busy[result] != false || buffer[result] != false)
				result++;
		else {
			result = countV - 1;
			while (busy[result] != false || buffer[result] != false)
				result--;
		}

		return result;
	}

	bool needMax(int num) {
		if (arr[0] - num >= num - arr[countV])
			return true;
		else
			return false;
	}

	int fact(int num) {
		int res = 1;
		for (int i = 1; i < num; i++)
			res *= i + 1;
		return res;
	}

	~Task() {
		delete[] best;
		delete[] buffer;
		delete[] bufferArr;
		tree.clearTree();
		deleteLists();
		delete recElem;

		recElem = NULL;
		bufferArr = NULL;
		buffer = NULL;
		bestVG = NULL;
		best = NULL;
		std::cout << "\nОчистка пула...";
		pool.clearPool();
	}
};