#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <conio.h>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjacencyMatrix;
public:
    Graph(int v) : vertices(v), adjacencyMatrix(v, vector<int>(v, 0)) {}

    void addEdge(int start, int end, int weight) {
        start -= 1;
        end -= 1;
        adjacencyMatrix[start][end] = weight;
        adjacencyMatrix[end][start] = weight;
    }

    void addVertex() {
        vertices++;
        adjacencyMatrix.push_back(vector<int>(vertices, 0));
        for (int i = 0; i < vertices - 1; i++)
            adjacencyMatrix[i].push_back(0);
    }

    void displayGraph() {
        cout << "Матрица смежности:\n";
        cout << setw(2) << " ";
        for (int i = 0; i < vertices; i++) 
            cout << setw(4) << i + 1;
        cout << endl;
        cout << setw(4) << " ";
        for (int i = 0; i < vertices; i++) 
            cout << "----";
        cout << endl;
        for (int i = 0; i < vertices; i++) {
            cout << setw(2) << i + 1 << "|";
            for (int j = 0; j < vertices; j++)
                cout << setw(4) << adjacencyMatrix[i][j];
            cout << endl;
        }
    }

    int findCenter() {
        int* eccentricity = new int[vertices];
        for (int i = 0; i < vertices; i++) 
            eccentricity[i] = 0;
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (adjacencyMatrix[i][j] != 0) 
                    eccentricity[i] = max(eccentricity[i], adjacencyMatrix[i][j]);
            }
        }
        int minEccentricity = INT_MAX;
        int center = -1;
        for (int i = 0; i < vertices; i++) {
            if (eccentricity[i] < minEccentricity) {
                minEccentricity = eccentricity[i];
                center = i;
            }
        }
        delete[] eccentricity;
        return center + 1; 
    }

    void kruskal() {
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (adjacencyMatrix[i][j] != 0)
                    edges.push_back({ adjacencyMatrix[i][j], {i, j} });
            }
        }
        sort(edges.begin(), edges.end());
        vector<int> parent(vertices, -1);
        int mstWeight = 0;
        for (auto edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            int setU = find(parent, u);
            int setV = find(parent, v);
            if (setU != setV) {
                cout << setU + 1 << " - " << setV + 1 << " : " << weight << endl;
                mstWeight += weight;
                unionSets(parent, setU, setV);
            }
        }
    }

    void clear() {
        vertices = 0;
        adjacencyMatrix.clear();
    }

private:
    int find(const vector<int>& parent, int i) {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    void unionSets(vector<int>& parent, int x, int y) {
    int setX = find(parent, x);
    int setY = find(parent, y);
    parent[setX] = setY;
    }

};

int main() {
    setlocale(0, "");
    int vertices = 0, center;
    Graph graph(vertices);
    char ch = 0;
    while (ch != 27) {
        system("cls");
        graph.displayGraph();
        cout << "\nВыберите действие:\n1. Добавить вершину\n2. Задать значение ребру\n3. Создание графа по варианту\n4. Центр графа\n5. Алгоритм Крускала\n6. Очистка графа\n\n";
        ch = _getch();
        switch (ch)
        {
        default:
            break;
        case '1':
            graph.addVertex();
            vertices++;
            break;
        case '2':
            int a, b, weight;
            cout << "Введите: вершина 1, вершина 2, вес >> ";
            cin >> a >> b >> weight;
            graph.addEdge(a, b, weight);
            break;
        case '3':
            if (vertices != 0) break;
            vertices = 5;
            for (int i = 0; i < vertices; i++) graph.addVertex();
            graph.addEdge(1, 2, 1);
            graph.addEdge(1, 3, 2);
            graph.addEdge(2, 4, 3);
            graph.addEdge(3, 4, 4);
            graph.addEdge(1, 5, 10);
            graph.addEdge(2, 5, 6);
            graph.addEdge(3, 5, 7);
            graph.addEdge(4, 5, 11);
            break;
        case '4':
            center = graph.findCenter();
            cout << "Центр графа: " << center << endl;
            _getch();
            break;
        case '5':
            graph.kruskal();
            _getch();
            break;
        case '6':
            graph.clear();
            vertices = 0;
            break;
        }
    }
    cout << "\nВыход";
    return 0;
}
