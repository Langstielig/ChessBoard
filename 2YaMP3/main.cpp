#include "Graph.h"
#include <iostream>
#include <string>

using namespace std;

int** createAdjacencyMatrix(bool** cutCells, int rows, int cols) {
	int size = rows + cols + 2;
	int** adjacencyMatrix = new int*[size];
	for (int i = 0; i < size; i++)
		adjacencyMatrix[i] = new int[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			adjacencyMatrix[i][j] = 0;
	for (int i = 1; i <= size/2 - 1; i++) {
		adjacencyMatrix[0][i] = 1;
		adjacencyMatrix[i][0] = 1;
	}
	for (int i = size/2; i <= size - 2; i++) {
		adjacencyMatrix[size - 1][i] = 1;
		adjacencyMatrix[i][size - 1] = 1;
	}
	for (int i = 1; i <= size/2 - 1; i++)
		for (int j = size/2; j <= size - 2; j++) {
			if (cutCells[i - 1][j-size/2] == true) {
				adjacencyMatrix[i][j] = 1;
				adjacencyMatrix[j][i] = 1;
			}
		}
	return adjacencyMatrix;
}

//int Terms(int** &adjacencyMatrix, int rows, int i, int previousJ, int count, int size) {
//	if (i == size / 2)
//		return count;
//	else {
//		int j = size/2;
//		while ((adjacencyMatrix[i][j] == 0 && j < size - 2) || (adjacencyMatrix[i][j]==1 && j==previousJ))
//			j++;
//		if (j < size - 2) {
//			cout << "Ћадь€ на клетке (" << i << ";" << j << ")" << endl;
//			Terms(adjacencyMatrix, rows, i + 1, j, count + 1, size);
//		}
//		else
//			Terms(adjacencyMatrix, rows, i - 1, 0, count - 1, size);
//	}
//}
//int  recursiveTerms(int**& adjacencyMatrix, bool*& occupiedCells, int i, int size, int count, int startJ) {
//	if (i == size / 2)
//		return count;
//	while (i < size / 2) {
//		int flag = true;
//		int j = size / 2;
//		while (j < size - 1 && flag)
//			if (adjacencyMatrix[i][j] == 1 && occupiedCells[j - size / 2] == 0) {
//				occupiedCells[j - size / 2] = 1;
//				flag = false;
//			}
//			else
//				j++;
//		if (j == size - 1)
//			recursiveTerms(adjacencyMatrix, occupiedCells, 1, size, 0, startJ + 1);
//		count++;
//		i++;
//	}
//}
//
//int maxCountOfTerms(int**& adjacencyMatrix, int rows, int size) {
//	int count = 0;
//	bool* occupiedCells = new bool[rows];
//	for (int i = 0; i < rows; i++)
//		occupiedCells[i] = 0;
//	int i = 1;
//	count = recursiveTerms(adjacencyMatrix, occupiedCells, 1, size, 0, size / 2);
//	/*while (i<size/2) {
//		int flag = true;
//		int j = size / 2;
//		while (j < size - 1 && flag)
//			if (adjacencyMatrix[i][j] == 1 && occupiedCells[j - size / 2] == 0) {
//				occupiedCells[j - size / 2] = 1;
//				flag = false;
//			}
//			else
//				j++;
//		if(j==size-1)
//
//		count++;
//	}*/
//	return count;
//}

string createString(int i, int j, int size) {
	string termsPlace;
	termsPlace += "Ћадь€ на клетке (";
	termsPlace += to_string(i - 1);
	termsPlace += ";";
	termsPlace += to_string(j - size / 2);
	termsPlace += ")";
	termsPlace += '\n';
	return termsPlace;
}

int recursiveMaxCountOfTerms(Graph graph, int j, int countOfFunction, int maxCount, string termsPlace) {
	int i = 1;
	int count = 0;
	int size = graph.getVertexCount();
	bool flag = true;
	bool* occupiedCells = new bool[size/2 - 1];
	string currentTermsPlace;
	for (int i = 0; i < size/2 - 1; i++)
		occupiedCells[i] = 0;
	while (i < size / 2 && countOfFunction <= (size - 2 - size / 2)) {
		flag = true;
		while (j < size - 1 && flag) {
			if (graph.isEdgeExist(i, j) == 1 && occupiedCells[j - size / 2] == 0) {
				occupiedCells[j - size / 2] = 1;
				currentTermsPlace += createString(i, j, size);
				i++;
				flag = false;
			}
			j++;
		}
		if (j == size - 1 && flag && countOfFunction <= (size - 2 - size / 2)) {
			countOfFunction++;
			if (count > maxCount) {
				maxCount = count;
				termsPlace = currentTermsPlace;
				currentTermsPlace.clear();
			}
			return recursiveMaxCountOfTerms(graph, size / 2 + countOfFunction, countOfFunction, maxCount, termsPlace);
		}
		count++;
		j = size / 2;
	}
	if (count > maxCount) {
		maxCount = count;
		termsPlace = currentTermsPlace;
		currentTermsPlace.clear();
	}
	cout << termsPlace;
	return maxCount;
}

int main() {
	setlocale(LC_ALL, "rus");
	int rows, cols, cuts;
	cout << "¬ведите ширину шахматной доски" << endl;
	cin >> rows;
	cout << "¬ведите длину шахматной доски" << endl;
	cin >> cols;
	cout << "¬ведите количество вырезанных клеток" << endl;
	cin >> cuts;
	bool** cutCells = new bool* [rows]; //можно сделать bool
	for (int i = 0; i < rows; i++) 
		cutCells[i] = new bool[cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cutCells[i][j] = true;
	for (int i = 0; i < cuts; i++) {
		int x, y;
		cout << "¬ведите координаты вырезанных клеток в формате x y" << endl;
		cin >> x >> y;
		cutCells[x][y] = false;
	}
	/*for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			cout << cutCells[i][j] << " ";
		cout << endl;
	}*/
	cout << endl;
	int** adjacencyMatrix;
	adjacencyMatrix = createAdjacencyMatrix(cutCells, rows, cols);
	int size = rows + cols + 2;
	/*for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			cout << adjacencyMatrix[i][j] << " ";
		cout << endl;
	}*/
	Graph graph(adjacencyMatrix, rows+cols+2);
	string termsPlace;
	cout << recursiveMaxCountOfTerms(graph, size / 2, 0, 0, termsPlace);
	return 0;
}
//берем первую вершину слева и первое ее ребро ведущее в вершину справа, потом берем ребро из следующей вершины такое, 
//чтобы оно не вело в ту жу вершину справа и следующую вершину такую, чтобы она не вели ни в одну уже зан€тую вершину справа