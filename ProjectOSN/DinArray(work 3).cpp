#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>
using namespace std;
class ADT {
public:
	struct Type {
		typedef unsigned int TypeItem;
		TypeItem** X;
		unsigned int n;
		Type() { n = 0; }
		Type(int nn) {
			n = nn;
			X = (TypeItem**)malloc(n * sizeof(TypeItem*));
			for (int pos1 = 0; pos1 < n; pos1++) 
				X[pos1] = (TypeItem*)malloc(n * sizeof(TypeItem));
			for (int pos1 = 0; pos1 < n; pos1++) {
				for (int pos2 = 0; pos2 < n; pos2++)
					X[pos1][pos2] = 0;
			}
		}
	};
	static void input(Type& a) {
		for (int pos1 = 0; pos1 < a.n; pos1++) {
			for (int pos2 = 0; pos2 < a.n; pos2++) {
				cout << "Введите значение для позиции [" << pos1 << "][" << pos2 << "] >> ";
				cin >> a.X[pos1][pos2];
			}
		}
	}
	static bool randominput(Type& a, int from = 0, int to = 50) {
		srand(time(0));
		for (int pos1 = 0; pos1 < a.n; pos1++) {
			for (int pos2 = 0; pos2 < a.n; pos2++)
				a.X[pos1][pos2] = (rand() % to * 2 + 1) + from;
		}
		return true;
	}
	static void output(Type& a) {
		for (int pos1 = 0; pos1 < a.n; pos1++) {
			for (int pos2 = 0; pos2 < a.n; pos2++)
				(pos2 % 10 != 0 ? (cout << a.X[pos1][pos2] << " ") : (cout << "\n" << a.X[pos1][pos2] << " "));
		}
	}
	static void transposed(Type& a, Type& b) {
		for (int pos1 = 0; pos1 < a.n; pos1++) {
			for (int pos2 = 0; pos2 < a.n; pos2++)
				b.X[pos2][pos1] = a.X[pos1][pos2];
		}
	}
};

int main()
{
	setlocale(0, "");
	cout << "Введите размер матрицы: ";
	int n = 0;
	cin >> n;
	if (n < 1 || n > 10) { system("cls"); cout << "Недопустимое значение матрицы\n";  return 0; }
	ADT::Type a(n), b(n);
	char ch = 0;
	system("cls");
	while (ch != 27) {
		cout << "Текущие значения в АТД:\n";
		ADT::output(a);
		cout << "\n\nВыберете действие:\n1. Задать случайные значения в АТД\n2. Задать значения с клавиатуры";
		cout << (a.n != 0 ? "\n3. Транспонировать матрицу" : "");
		ch = _getch();
		system("cls");
		if (ch == '1') {
			ADT::randominput(a);
		}
		else if (ch == '2') {
			ADT::input(a);
		}
		else if (ch == '3' && a.n != 0) {
			cout << "Основная матрица: ";
			ADT::output(a);
			cout << "\n\n";
			ADT::transposed(a, b);
			cout << "Транспонированная матрица: ";
			ADT::output(b);
			_getch();
		}
		system("cls");
	}
	cout << "Выход\n";
}