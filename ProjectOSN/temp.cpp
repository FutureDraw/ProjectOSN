#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

class Graph {
	//Воруя этот класс, я соглашаюсь получить 0 баллов за работу
private:
	//Список смежных вершин
	struct edge {
		char edgeTo; //Было бы здорово хранить тут указатель на узел, но при увеличении вектора все адреса отлетают, если мы заранее не выделили размер через reserve()
		int distance;

		edge(char edgeTo, int distance)
			: edgeTo(edgeTo), distance(distance)
		{
		}
	};
	struct vertex {
		char name;
		vector<edge> edges;
	};
	vector<vertex> adjacencyList;


	//Матрица смежности
	vector<char> names;
	vector<vector<int>> adjacencyMatrix;

public:
	int addVertex(char name) {
		int id = (int)distance(names.begin(), find(names.begin(), names.end(), name));

		if (id < adjacencyList.size()) return -1;
		adjacencyList.push_back({ name });

		names.push_back(name);
		for (vector<int>& row : adjacencyMatrix) row.push_back(-1);
		adjacencyMatrix.push_back(vector<int>(adjacencyMatrix.size() + 1));
		for (int& edge : adjacencyMatrix[adjacencyMatrix.size() - 1]) edge = -1;
		return 0;
	}

	int addEdge(char name1, char name2, int edgeDistance, bool symmetry = false) {
		int id1 = (int)distance(names.begin(), find(names.begin(), names.end(), name1));
		int id2 = (int)distance(names.begin(), find(names.begin(), names.end(), name2));
		if (id1 >= adjacencyList.size() || id2 >= adjacencyList.size()) return -1;
		adjacencyList[id1].edges.push_back(edge(adjacencyList[id2].name, edgeDistance));
		if (symmetry == true) adjacencyList[id2].edges.push_back(edge(adjacencyList[id1].name, edgeDistance));

		adjacencyMatrix[id1][id2] = edgeDistance;
		if (symmetry == true) adjacencyMatrix[id2][id1] = edgeDistance;

		return 0;
	}

	void printList() {
		cout << "Список смежных вершин:" << endl;
		for (vertex vertex : adjacencyList) {
			cout << "[" << vertex.name << "]:\t";
			for (edge edge : vertex.edges)
				cout << edge.edgeTo << "(" << edge.distance << ") ";
			cout << endl;
		}
		cout << endl;
	}

	void printMatrix() {
		cout << "Матрица смежности:" << endl;
		for (int i = 0; i < adjacencyList.size(); i++) cout << "\t" << names[i];
		cout << endl;
		for (int i = 0; i < adjacencyMatrix.size(); i++) {
			cout << names[i] << "\t";
			for (int j = 0; j < adjacencyMatrix.size(); j++) {
				if (adjacencyMatrix[i][j] == -1) cout << "\t";
				else cout << adjacencyMatrix[i][j] << "\t";
			}
			if (i < adjacencyMatrix.size() - 1) cout << endl;

		}
		cout << endl << endl;
	}

	void clear() {
		for (vertex vertex : adjacencyList) vertex.edges.clear();
		adjacencyList.clear();
		for (vector<int> row : adjacencyMatrix) row.clear();
		adjacencyMatrix.clear();
	}
};

int main()
{
	setlocale(0, "");
	Graph myGraph;
	myGraph.addVertex('a');
	myGraph.addVertex('x');
	myGraph.addVertex('c');
	myGraph.addVertex('p');
	myGraph.addEdge('a', 'c', 5, true);
	myGraph.addEdge('a', 'e', 5, true);
	myGraph.addEdge('x', 'c', 3, true);
	myGraph.printMatrix();
	myGraph.printList();

	char menu = 0;
	int result = 0;
	while (menu != '0') {
		cout << "Меню\n"
			<< "1. Пересоздать граф\n"
			<< "2. Добавить узел\n"
			<< "3. Добавить грань\n"
			<< "4. Вывести список смежных вершин\n"
			<< "5. Вывести матрицу смежности\n"
			<< "0. Выход\n\n";

		menu = _getch(); //conio.h
		//system("cls"); //Не всегда хорошее решение

		switch (menu) {
		case'1':
			myGraph.clear();
			cout << "Граф очищен" << endl;
			break;
		case '2':
			char newvertex;
			cout << "Введите имя новой вершины: ";
			cin >> newvertex;
			result = myGraph.addVertex(newvertex);
			if (result == 0)
				cout << "Вершина добавлена" << endl;
			else if (result == -1)
				cout << "Вершина уже существует" << endl;
			break;
		case '3':
			char vertex1, vertex2;
			int edgeDistance;
			bool edgeSymmetry;
			cout << "Введите имя вершины 1: ";
			cin >> vertex1;
			cout << "Введите имя вершины 2: ";
			cin >> vertex2;
			cout << "Введите длину грани: ";
			cin >> edgeDistance;
			cout << "Грань двунаправленная? (1 – да, 0 – нет): ";
			cin >> edgeSymmetry;
			result = myGraph.addEdge(vertex1, vertex2, edgeDistance, edgeSymmetry);
			if (result == 0)
				cout << "Грань добавлена" << endl;
			else if (result == -1)
				cout << "Узел не найден" << endl;
			break;
		case'4':
			myGraph.printList();
			break;
		case'5':
			myGraph.printMatrix();
			break;
		default:
			cout << "Неверный ввод" << endl;
		}
	}

}