#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

class ADT {
public:
	struct Table {
		int id;
		string firstname;
		string name;
		string group_number;
		double evl[5];
		double sr;
	};
	struct Type {
		static const int N = 100;
		typedef unsigned int TypeItem;
		unsigned int n = 0;
		Table X[N] = {};
		Type(int n1) { n = n1; }
	};

	static bool input(Type& a) {
		for (int pos = 0; pos < a.n; pos++) {
			system("cls");
			cout << "Введите данные о студенте:\nНомер З.К" << setw(12) << "Фамилия" << setw(18) << "Номер группы" << setw(11.5) << "Оценки >> ";
			cin >> a.X[pos].id >> a.X[pos].firstname >> a.X[pos].name >> a.X[pos].group_number;
			if (a.X[pos].group_number.length() > 10) { return false; }
			for (int i = 0; i < 5; i++) {
				cin >> a.X[pos].evl[i]; if (a.X[pos].evl[i] < 1 || a.X[pos].evl[i] > 5) { return false; }
			}
		}
		return true;
	}

	static bool input_in(Type& a) {
		Table Temp[1];
		vector<int>T;
		system("cls");
		cout << "Введите данные о студенте:\nНомер З.К" << setw(12) << "Фамилия" << setw(18) << "Номер группы" << setw(11.5) << "Оценки >> ";
		cin >> Temp[0].id >> Temp[0].firstname >> Temp[0].name >> Temp[0].group_number;
		if (Temp[0].group_number.length() > 10) { return false; }
		for (int i = 0; i < 5; i++) {
			cin >> Temp[0].evl[i]; if (Temp[0].evl[i] < 1 || Temp[0].evl[i] > 5) { return false; }
		}
		for (int pos = 0; pos < a.n; pos++) {
			T.push_back(a.X[pos].id);
		}
		sort(T.begin(), T.end());
		for (int j = 0; j < T.size(); j++) {
			if (Temp[0].id < T[j]) {
				paste(a, Temp, j);
				break;
			}
		}
		cin.ignore();
		return true;
	}

	static void paste(Type& a, Table Temp[], int ipos) {
		a.n++;
		for (int pos1 = a.n-1; pos1 >= ipos; pos1--) {
			a.X[pos1] = a.X[pos1 - 1];
		}
		a.X[ipos] = Temp[0];
	}

	static void deltablestring(Type& a, int ipos) {
		for (int pos = ipos; pos < a.n; pos++)
			a.X[pos] = a.X[pos + 1];
		a.n -= 1;
	}

	static void maxbal(Type a) {
		double maxcount = 0;
		for (int pos = 0; pos < a.n; pos++) {
			if (a.X[pos].sr > maxcount)
				maxcount = a.X[pos].sr;
		}
		for (int i = 0; i < a.n; i++) {
			if (maxcount == a.X[i].sr)
				cout << a.X[i].id << " ";
		}
	}

	static void srevl(Type& a) {
		double average = 0, counter = 0, ss = 5.5;
		for (int pos = 0; pos < a.n; pos++) {
			for (int i = 0; i < 5; i++)
				average += a.X[pos].evl[i];
			a.X[pos].sr = average / 5;
			average = 0;
		}
	}

	static void output(Type& a) {
		cout << "Номер З.К" << setw(12) << "Фамилия" << setw(18) << "Номер группы" << setw(11.5) << "Оценки\n";
		cout << setfill('-') << setw(51) << "" << setfill(' ') << endl;
		for (int pos = 0; pos < a.n; pos++) {
			cout << setw(7) << a.X[pos].id << setw(12) << a.X[pos].firstname << " " << a.X[pos].name << setw(14) << a.X[pos].group_number << setw(5) << a.X[pos].evl[0] << " " << a.X[pos].evl[1] << " " << a.X[pos].evl[2] << " " << a.X[pos].evl[3] << " " << a.X[pos].evl[4] << "\n";
		}
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n = 0;
	char ch = 0;
	ADT::Type a(n), b(0);
	while (ch != 27) {
		system("cls");
		cout << "Текущие значения в АТД:\n\n";
		if (a.n != 0) ADT::output(a);
		cout << "\nВыберете действие:\n1. Ввести данные с клавиатуры\n";
		cout << (a.n != 0 ? "\n2. Добавить данные о студенте\n3. Вывести список студентов с максимальным средним балом\n5. Удалить данные о студентах по номеру группы" : "");
		ADT::srevl(a);
		ch = _getch();
		system("cls");
		if (ch == '1') {
			cout << "Введите размер таблицы >> ";
			if (cin >> n && n <= a.N && n > 0) {
				a.n = n;
				system("cls");
				ADT::input(a);
			}
			else {
				cout << "\nОшибка. Недопустимое значение\a\nНажмите любую клавишу, чтобы продолжить";
				_getch();
			}
		}
		else if (ch == '2')
			ADT::input_in(a);
		else if (ch == '3') {
			cout << "Номера З.К. студентов с максимальным балом: ";
			ADT::maxbal(a);
			_getch();
		}
		else if (ch == '4') {
			string group;
			cout << "Введите номер группы >> ";
			cin >> group;
			for (int i = 0; i < a.n+1; i++) {
				for (int pos = 0; pos < a.n; pos++) {
					if (group == a.X[pos].group_number)
						ADT::deltablestring(a, pos);
				}
			}
		}
	}
	cout << "Выход\n";
}