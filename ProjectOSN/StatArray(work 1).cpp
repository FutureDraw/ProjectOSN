#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class ADT
{
public:
	struct Type {
		static const int N = 100;
		typedef unsigned int TypeItem;
		unsigned int n = 0;
		TypeItem X[N] = {};
		Type(int n1) { n = n1; }
		Type() { n = 0; }
	};
	static bool input(Type& a) {

		if (a.n < 1 || a.n > a.N) { return false; }
		for (int pos = 0; pos < a.n; pos++) {
			cout << "������� �������� ��� ������� " << pos << " >> ";
			cin >> a.X[pos];
		}
		return true;
	}
	static void output(Type& a) {
		for (int pos = 0; pos < a.n; pos++) {
			cout << a.X[pos] << (pos < a.n - 1 ? ", " : "");
		}
	}

	static bool deleteinpos(Type& a, int pos) {
		if (pos < 0 || pos > a.n) { return false; }
		a.X[pos] = 0;
		for (int ipos = pos; ipos < a.n; ipos++) {
			a.X[ipos] = a.X[ipos + 1];
		}
		a.n = a.n - 1;
		return true;
	}
	static bool addinpos(Type& a, int pos, int number) {
		if (pos < 0 || pos > a.n) { return false; }
		a.X[pos] = number;
		return true;
	}
	static bool randominput(Type& a, int from = 0, int to = 50) {
		srand(time(0));
		if (a.n < 1 || a.n > a.N) { return false; }
		for (int pos = 0; pos < a.n; pos++) {
			a.X[pos] = (rand() % to * 2 + 1) + from;
		}
		return true;
	}
	static int searchindexprost(Type& a, int& r) {
		int k = 0;
		for (int pos = 0; pos < a.n; pos++) {
			for (int i = 2; i <= sqrt(a.X[pos]); i++) {
				if (a.X[pos] % i == 0) {
					k = a.X[pos];
					a.X[pos] = 0;
				}
			}
			if (a.X[pos] != 0) {
				r = pos + 1;
				return pos;
			}
			if (a.X[pos] == 0)
				a.X[pos] = k;
		}
		return -1;
	}
	static void deletemultipleelements(Type& a, int multiple = 7) {
		for (int pos = 0; pos < a.n; pos++) {
			if (a.X[pos] % multiple == 0)
				ADT::deleteinpos(a, pos);
		}
	}
	static bool addinposwithold(Type& a, int pos, int number) {
		if (pos < 0 || pos > a.n || a.n == 100) { return false; }
		int c = 0, b = a.X[pos];
		a.n++;
		int buff[2] = { number, 0 };
		for (int p = pos; p < a.n; p++) {
			buff[1] = a.X[p];
			a.X[p] = buff[0];
			int x = buff[0];
			buff[0] = buff[1];
			buff[1] = x;
		}
		return true;
	}
};

int main()
{
	setlocale(0, "");
	int n = 0;
	char ch = 0;
	ADT::Type a(n);
	while (ch != 27) {
		cout << "������� �������� � ���:\n";
		for (int i = 0; i < a.n; i++) {
			(i % 10 != 0 ? (cout << a.X[i] << " ") : (cout << "\n" << a.X[i] << " "));
		}
		cout << "\n\n�������� ��������:\n1. ������ ��������� �������� � ���\n2. ������ �������� � ����������";
		cout << (a.n != 0 ? "\n3. ������� ��������.\n4. �������� ������� � �������" : "");
		cout << (a.n != 0 ? "\n5. ������� ��� �������� ������� 7\n6. �������� �������� � ������� ����� �������� �����" : "");
		cout << (a.n != 0 ? "\n7. �������� ������ �������� �����" : "");
		ch = _getch();
		system("cls");
		if (ch == '1') {
			cout << "������� ���-�� ��������: ";
			if (cin >> n && n <= a.N) {
				a.n = n;
				ADT::randominput(a);
			}
			else {
				cout << "\n������. ������������ ��������\a\n������� ����� �������, ����� ����������";
				_getch();
			}
		}
		else if (ch == '2') {
			cout << "������� ���-�� ��������: ";
			if (cin >> n && n <= a.N) {
				a.n = n;
				ADT::input(a);
			}
			else {
				cout << "\n������. ������������ ��������\a\n������� ����� �������, ����� ����������";
				_getch();
			}
		}
		else if (ch == '3' && a.n != 0) {
			cout << "������� �������: ";
			int r;
			cin >> r;
			if (!ADT::deleteinpos(a, r)) {
				cout << "\n������. ������� ��� ���\a\n������� ����� �������, ����� ����������";
				_getch();
			}

		}
		else if (ch == '4' && a.n != 0) {
			cout << "������� �������: ";
			int r, g;
			cin >> r;
			cout << "������� �����: ";
			cin >> g;
			if (!ADT::addinpos(a, r, g)) {
				cout << "\n������. ������� ��� ���\a\n������� ����� �������, ����� ����������";
				_getch();
			}
		}
		else if (ch == '5' && a.n != 0) {
			ADT::deletemultipleelements(a, 7);
		}
		else if (ch == '6' && a.n != 0) {
			int r, g;
			ADT::searchindexprost(a, r);
			cout << "������� �����: ";
			cin >> g;
			if (!ADT::addinposwithold(a, r, g)) {
				cout << "\n������. ������� ��� ���\a\n������� ����� �������, ����� ����������";
				_getch();
			}
		}
		else if (ch == '7' && a.n != 0) {
			int r;
			cout << "������ �������� �����: " << ADT::searchindexprost(a, r);
			cout << "\n������� ����� �������, ����� ����������";
			_getch();
		}
		system("cls");
	}
	cout << "����� �������\n";
}