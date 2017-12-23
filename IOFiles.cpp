//#include "stdafx.h"
#include "Graph.cpp"
#include <fstream>

using std::string;

class IOFiles {
	std::fstream file;

public:

	IOFiles() {
		file.close();
	}

	bool saveGraph(Graph &graph, string fileName) {
		file.open(fileName, std::ios::out);
		if (file) {
			List *vertex = graph.first;
			List::node *nowNode = NULL;

			while (vertex != NULL) {
				nowNode = vertex->nodes;
				file << vertex->num << " ";
				while (nowNode != NULL) {
					file << nowNode->edgeTo->num << " ";
					nowNode = nowNode->next;
				}
				file << std::endl;
				vertex = vertex->next;
			}
			file.close();
			return true;
		}
		else
			return false;
	}

	bool loadGraph(Graph &graph, string fileName) {
		file.open(fileName, std::ios::in);

		if (file) {
			char buffer = file.get();
			int num = 0, from = 0;
			bool newVertex = true;
			graph.deleteGraph();

			while (!file.eof()) {
				if (buffer == ' ') {
					if (newVertex) {
						graph.addVertex(num);
						from = num;
						newVertex = false;
					}
					else if (!graph.addEdge(from, num)) {
						graph.addVertex(num);
						graph.addEdge(from, num);
					}
					num = 0;
				}
				else if (buffer == '\n') {
					newVertex = true;
					num = 0;
				}
				else
					num = num * 10 + buffer - 48;
				buffer = file.get();
			}
			file.close();
			return true;
		}
		else
			return false;
	}

	bool loadTask(int *w, string fileName, int count) {
		file.open(fileName, std::ios::in);

		if (file) {
			char buffer = file.get();
			int num = 0, countNum = 0;

			while (buffer != ' ') {
				num = num * 10 + buffer - 48;		
				buffer = file.get();
			}

			if (num != count)
				return false;

			buffer = file.get();
			num = 0;
			while (!file.eof()) {
				if (buffer == ' ') {
					w[countNum] = num;
					num = 0;
					countNum++;
				}
				else
					num = num * 10 + buffer - 48;
				buffer = file.get();
			}
			w[countNum] = num;
			file.close();
			return true;
		}
		else
			return false;
	}

	
	~IOFiles() {
		if (file)
			file.close();
	}
};