#include "Graph.h"

Graph::Graph(int _size) : size(_size) {
	adjMatr = new int* [size];
	for (int i = 0; i < size; i++)
		adjMatr[i] = new int[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			adjMatr[i][j] = 0;
}

Graph::Graph(int**& newMatr, int _size) {
	adjMatr = newMatr;
	size = _size;
	newMatr = nullptr;
}

Graph::Graph(const Graph& obj) {
	size = obj.size;
	adjMatr = new int* [size];
	for (int i = 0; i < size; i++)
		adjMatr[i] = new int[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			adjMatr[i][j] = obj.adjMatr[i][j];
}

Graph::~Graph() {
	clearGraph();
}

void Graph::addEdge(int i, int j) {
	if (i < size && j < size && i >= 0 && j >= 0) {
		adjMatr[i][j] = 1;
		adjMatr[j][i] = 1;
	}
}

void Graph::addVertex() {
	int** newMatr = new int* [size + 1];
	for (int i = 0; i < size + 1; i++)
		newMatr[i] = new int[size + 1];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			newMatr[i][j] = adjMatr[i][j];
	for (int i = 0; i < size; i++)
		delete adjMatr[i];
	delete[] adjMatr;
	size++;
	adjMatr = newMatr;
}

void Graph::removeEdge(int i, int j) {
	if (i < size && j < size && i >= 0 && j >= 0) { 
		adjMatr[i][j] = 0;
		adjMatr[j][i] = 0;
	}
}

void Graph::removeVertex(int i) {
	int** newMatr = new int* [size - 1];
	for (int j = 0; j < size - 1; j++)
		newMatr[j] = new int[size - 1];
	for (int j = 0, x = 0; j < size - 1; j++) {
		if (j == i) x = 1;
		for (int n = 0; n < size - 1; n++) {
			if (n == i) x = 1;
			newMatr[j][n] = adjMatr[j + x][n + x];
		}
	}
	for (int i = 0; i < size; i++)
		delete adjMatr[i];
	delete[] adjMatr;
	size--;
	adjMatr = newMatr;
}

void Graph::clearGraph() {
	for (int i = 0; i < size; i++)
		delete adjMatr[i];
	delete[] adjMatr;

	adjMatr = nullptr;
	size = 0;
}

bool Graph::isEdgeExist(int i, int j) {
	return adjMatr[i][j] == 1;
}

bool Graph::isVertexExist(int i) {
	return i < size;
}

int Graph::getVertexCount() {
	return size;
}

int Graph::getEdgeCount() {
	int count = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (adjMatr[i][j] == 1)
				count++;
	return count;
}
