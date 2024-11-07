#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<string>
#include<vector>

#define NOMINMAX
#include<Windows.h>

using namespace std;

vector<vector<unsigned int>> distances;
vector<vector<pair<int, int>>> adjList;
vector<vector<int>> nexVt;

const unsigned int INF = numeric_limits<unsigned int>::max();

bool read(const string& path) {
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "Файл не відкривається для зчитування." << endl;
		return false;
	}
	unsigned int N, M;
	file >> N >> M;
	if (N <= 0 || M <= 0) {
		cerr << "Неправильна структура файла. Перевірте кількість вершин та ребер." << endl;
		return false;
	}

	distances.assign(N, vector<unsigned int>(N, INF));
	nexVt.assign(N, vector<int>(N, -1));

	adjList.assign(N, vector<pair<int, int>>());

	for (size_t i = 0; i < N; i++) {
		distances[i][i] = 0;
	}

	for (size_t i = 0; i < M; i++) {
		unsigned int v, u, w;
		if (!(file >> v >> u >> w)) {
			cerr << "Ребро графа неправильно записано." << endl;
			return false;
		}
		if (u < 1 || u > N) {
			cerr << "Неправильні індекси ребра " << (i + 1) << "." << endl;
			return false;
		}
		distances[v - 1][u - 1] = w;
		nexVt[v - 1][u - 1] = u - 1;
		adjList[v - 1].push_back({ u - 1, w });
	}

	return true;
}

void floydWarshall() {
	int n = distances.size();
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (distances[i][k] < INF && distances[k][j] < INF) {
					if (distances[i][j] > distances[i][k] + distances[k][j]) {
						distances[i][j] = distances[i][k] + distances[k][j];
						nexVt[i][j] = nexVt[i][k];
					}
				}
			}
		}
	}
}

void print() {
	for (int i = 0; i < adjList.size(); i++) {
		cout << "Вершина " << (i + 1);
		if (!adjList[i].empty()) {
			cout << ": [";
			for (size_t j = 0; j < adjList[i].size(); ++j) {
				cout << (adjList[i][j].first + 1);
				if (j < adjList[i].size() - 1) {
					cout << ", ";
				}
			}
			cout << "]\n";
		}
	}
}

void printPath(int u, int v) {
	if (nexVt[u][v] == -1) {
		cout << "Шлях від " << u + 1 << " до " << v + 1 << " не існує." << endl;
		return;
	}

	cout << "Шлях від " << u + 1 << " до " << v + 1 << ": " << u + 1;
	unsigned int totalWeight = 0;

	while (u != v) {
		int next = nexVt[u][v];
		cout << " -> " << next + 1;
		totalWeight += distances[u][next];
		u = next;
	}

	cout << endl;
	cout << "Загальна вага маршруту: " << totalWeight << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string path;
	cout << "Введіть шлях до графа з вагами ребер: ";
	getline(cin, path);
	if (!read(path)) {
		return 1;
	}

	floydWarshall();

	print();
	unsigned int u, v;

	cout << "Введіть початкову вершину: ";
	cin >> u;
	if (cin.fail()) {
		cout << "Початкова вершина неправильно введена." << endl;
		return 2;
	}

	cout << "Введіть кінцеву вершину: ";
	cin >> v;
	if (cin.fail()) {
		cout << "Кінцеву вершину неправильно введено." << endl;
		return 3;
	}

	if (u < 1 || u > adjList.size() || v < 1 || v > adjList.size()) {
		cout << "Початкова або кінцева вершина для пошуку виходить за межі дозволених границь графу." << endl;
		return 4;
	}

	printPath(u - 1, v - 1);

	return 0;
}