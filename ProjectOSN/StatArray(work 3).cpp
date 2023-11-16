#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class ADT
{
public:
	struct Type {
		static const int N = 10;
		typedef unsigned int TypeItem;
		unsigned int n = 0;
		TypeItem X[N][N] = {};
		Type(int n1) { n = n1; }
		Type() { n = 0; }
	};
	static bool input(Type& a) {
		if (a.n < 1 || a.n > a.N) { return false; }
		for (int pos1 = 0; pos1 < a.n; pos1++) {
			for (int pos2 = 0; pos2 < a.n; pos2++) {
				cout << "Введите значение для позиции [" << pos1 << "][" << pos2 << "] >> ";
				cin >> a.X[pos1][pos2];
			}
		}
		return true;
	}
	static void output(Type& a) {
		for (int pos1 = 0; pos1 < a.n; pos1++) {
			for (int pos2 = 0; pos2 < a.n; pos2++)
				(pos2 % 10 != 0 ? (cout << a.X[pos1][pos2] << " ") : (cout << "\n" << a.X[pos1][pos2] << " "));
		}
	}
	static bool randominput(Type& a, int from = 0, int to = 50) {
		srand(time(0));
		if (a.n < 1 || a.n > a.N) { return false; }
		for (int pos1 = 0; pos1 < a.n; pos1++) {
			for (int pos2 = 0; pos2 < a.n; pos2++)
				a.X[pos1][pos2] = (rand() % to * 2 + 1) + from;
		}
		return true;
	}
	static void transposed(Type& a, Type& b) {
		for (int pos1 = 0; pos1 < a.n; pos1++) {
			for (int pos2 = 0; pos2 < a.n; pos2++) 
				b.X[pos2][pos1] = a.X[pos1][pos2];
		}
	}
};

void main()
{
	setlocale(0, "");
	int n = 0;
	char ch = 0;
	ADT::Type a(n), b(n);
	while (ch != 27) {
		cout << "Текущие значения в АТД:\n";
		ADT::output(a);
		cout << "\n\nВыберете действие:\n1. Задать случайные значения в АТД\n2. Задать значения с клавиатуры";
		cout << (a.n != 0 ? "\n3. Транспонировать матрицу" : "");
		ch = _getch();
		system("cls");
		if (ch == '1') {
			if (n == 0) {
				cout << "Введите кол-во значений: ";
				if (cin >> n && n <= a.N && n > 1) {
					a.n = n;
					b.n = n;
					ADT::randominput(a);
				}
				else {
					cout << "\nОшибка. Недопустимое значение\a\nНажмите любую клавишу, чтобы продолжить";
					_getch();
				}
			}
			else
				ADT::randominput(a);
		}
		else if (ch == '2') {
			cout << "Введите кол-во значений: ";
			if (cin >> n && n <= a.N && n > 1) {
				a.n = n;
				b.n = n;
				system("cls");
				ADT::input(a);
			}
			else {
				cout << "\nОшибка. Недопустимое значение\a\nНажмите любую клавишу, чтобы продолжить";
				_getch();
			}
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
	cout << "Выход из программы";
}