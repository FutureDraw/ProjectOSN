#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <vector>

using namespace std;

char X[301];
vector<char*> X1;
vector<int> numbers;
clock_t start, end_time;
double cpu_ms;

static void input() {
	X1.clear();
	cout << "Введите предложение >> ";
	gets_s(X, 301);
}

static void output() {
	for (int pos = 0; pos < X1.size(); pos++) {
		cout << X1[pos] << " ";
	}
}

static void split() {
	start = clock();
	char* c;
	c = strtok(X, " .,-");
	while (c != NULL) {
		X1.push_back(c);
		c = strtok(NULL, " .,-");
	}
	end_time = clock();
}

static void dellcouple() {
	start = clock();
	char* a = 0;
	for (int pos1 = 0; pos1 < X1.size(); pos1++) {
		for (int pos2 = pos1 + 1; pos2 < X1.size(); pos2++) {
			if (!strcmp(X1[pos1], X1[pos2])) {
				a = X1[pos1];
				for (int pos3 = 0; pos3 < X1.size(); pos3++) {
					if (!strcmp(X1[pos3], a)) {
						X1.erase(X1.begin() + pos3);
						pos3--;
					}
				}
			}
		}
	}
	end_time = clock();
}

static void intmass() {
	start = clock();
	for (int pos1 = 0; pos1 < X1.size(); pos1++) {
		char* str = X1[pos1];
		int len = strlen(str);
		bool is_number = true;
		for (int pos2 = 0; pos2 < len; pos2++) {
			if (str[pos2] < '0' || str[pos2] > '9') {
				is_number = false;
				break;
			}
		}
		if (is_number) {
			int num = atoi(str);
			numbers.push_back(num);
		}
	}
	for (int pos = 0; pos < numbers.size(); pos++)
		cout << numbers[pos] << " ";
	numbers.clear();
	end_time = clock();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char ch = 0;
	int x;
	system("cls");
	while (ch != 27) {
		cout << "Текущая строка: \n\n";
		output();
		cpu_ms = ((double)(end_time - start)) / CLOCKS_PER_SEC;
		cout << "\n\nВремя работы: " << cpu_ms << "ms";
		cout << "\n\nВыберете действие:\n1. Заполнить строку";
		cout << (X1.size() != 0 ? "\n2. Удалить все одинаковые слова\n3. Создать массив из чисел" : "");
		ch = _getch();
		system("cls");
		if (ch == '1') {
			input();
			split();
			system("cls");
		}
		else if (ch == '2') {
			for (int i = 0; i < X1.size(); i++)
				dellcouple();
		}
		else if (ch == '3') {
			intmass();
			_getch();
			system("cls");
		}
	}
	cout << "Выход\n";
}

/*static char* copy(int x) {
	for (int pos = 0; pos < X1.size(); pos++) {
		if (pos == x - 1)
			return X1[pos];
	}
}*/