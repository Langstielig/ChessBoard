#pragma once

class Graph {
	int size;
	int** adjMatr;

public:
	Graph(int _size);
	Graph(int**& newMatr, int _size);
	Graph(const Graph& obj);
	~Graph();

	void addEdge(int i, int j);
	void addVertex();

	void removeEdge(int i, int j);
	void removeVertex(int i);

	void clearGraph();

	bool isEdgeExist(int i, int j);
	bool isVertexExist(int i);

	int getVertexCount();
	int getEdgeCount();

};
