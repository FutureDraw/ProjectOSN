#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <fstream>

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

	static bool input(Type& a, bool ss = true) {
		if (ss == true) {
			for (int pos = 0; pos < a.n; pos++) {
				system("cls");
				cout << "Введите данные о студенте:\nНомер З.К" << setw(12) << "Фамилия" << setw(18) << "Номер группы" << setw(11.5) << "Оценки >> ";
				cin >> a.X[pos].id >> a.X[pos].firstname >> a.X[pos].name >> a.X[pos].group_number;
				if (a.X[pos].group_number.length() > 10) { return false; }
				for (int i = 0; i < 5; i++) {
					cin >> a.X[pos].evl[i]; if (a.X[pos].evl[i] < 1 || a.X[pos].evl[i] > 5) { return false; }
				}
			}
		}
		if (ss == false) {
			ifstream file("Table.txt");
			ifstream file1("Table.txt");
			if (!file.is_open()) { return false; }
			string line;
			while (getline(file1, line)) {
				a.n++;
			}
			file1.close();
			for (int pos = 0; pos < a.n; pos++) {
				file >> a.X[pos].id >> a.X[pos].firstname >> a.X[pos].name >> a.X[pos].group_number;
				if (a.X[pos].group_number.length() > 10) { return false; }
				for (int i = 0; i < 5; i++) {
					file >> a.X[pos].evl[i]; if (a.X[pos].evl[i] < 1 || a.X[pos].evl[i] > 5) { return false; }
				}
			}
			file.close();
		}
		return true;
	}

	static bool input_in(Type& a) {
		a.n++;
		if (a.n < 1 || a.n > a.N) return false;
		cout << "Введите данные о студенте:\nНомер З.К" << setw(12) << "Фамилия" << setw(18) << "Номер группы" << setw(11.5) << "Оценки >> ";
		cin >> a.X[a.n - 1].id >> a.X[a.n - 1].firstname >> a.X[a.n - 1].name >> a.X[a.n - 1].group_number;
		if (a.X[a.n - 1].group_number.length() > 10) { return false; }
		for (int i = 0; i < 5; i++) {
			cin >> a.X[a.n - 1].evl[i]; if (a.X[a.n - 1].evl[i] < 1 || a.X[a.n - 1].evl[i] > 5) { return false; }
		}
		return true;
	}

	static void deltablestring(Type& a, int ipos) {
		for (int pos = ipos; pos < a.n; pos++)
			a.X[pos] = a.X[pos + 1];
		a.n -= 1;
	}

	static void prosto(Type a) {
		vector<double> T;
		double ss = 5.5;
		int max_index;
		for (int i = 0; i < a.n; i++) {
			max_index = i;
			for (int j = i + 1; j < a.n; j++) {
				if (a.X[j].sr > a.X[max_index].sr && a.X[j].sr > 4) {
					max_index = j;
				}
			}
			if (a.X[max_index].sr <= 4) {
				break;
			}
			T.push_back(a.X[max_index].id);
			ss = a.X[max_index].sr;
			swap(a.X[i], a.X[max_index]);
		}
		for (int pos = 0; pos < T.size(); pos++)
			cout << T[pos] << " ";
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
		cout << "\nВыберете действие:\n1. Ввести данные с клавиатуры\n2. Заполнить данные из файла";
		cout << (a.n != 0 ? "\n3. Добавить данные о студенте в конец таблицы\n4. Вывести список студентов средний бал которых выше 4\n5. Удалить данные о студенте с средним балом выше определенного" : "");
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
		else if (ch == '2') {
			bool ss = false;
			ADT::input(a, ss);
		}
		else if (ch == '3')
			ADT::input_in(a);
		else if (ch == '4') {
			cout << "Студенты, средний бал которых выше 4: ";
			ADT::prosto(a);
			_getch();
		}
		else if (ch == '5') {
			double r;
			cout << "Введите среднее арфиметическое >> ";
			cin >> r;
			ADT::srevl(a);
			for (int pos = 0; pos < a.n; pos++) {
				if (r > a.X[pos].sr) {
					ADT::deltablestring(a, pos);
				}
			}
		}
	}
	cout << "Выход\n";
}