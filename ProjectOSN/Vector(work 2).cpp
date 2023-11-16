#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <vector>
using namespace std;
class ADT {
public:
	struct Type {
		typedef unsigned int TypeItem;
		vector<TypeItem> X;
		Type(int nn) {
			X.resize(nn);
			for (int pos = 0; pos < X.size(); pos++) { X[pos] = 0; }
		}
	};
	static void input(Type& a) {
		for (int pos = 0; pos < a.X.size(); pos++) {
			cout << "������� �������� ��� ������� [" << pos << "] >> ";
			cin >> a.X[pos];
		}
	}
	static void randominput(Type& a) {
		srand(time(0));
		for (int pos = 0; pos < a.X.size(); pos++) {
			a.X[pos] = rand() % 101;
		}
	}
	static void output(Type& a) {
		for (int i = 0; i < a.X.size(); i++) {
			(i % (int)sqrt(a.X.size()) != 0 ? (cout << a.X[i] << " ") : (cout << "\n" << a.X[i] << " "));
		}
	}
	static bool deleteinpos(Type& a, int pos) {
		if (pos < 0 || pos >= a.X.size()) { return false; }
		for (int ipos = pos; ipos < a.X.size(); ipos++) {
			a.X[ipos] = a.X[ipos + 1];
		}
		a.X.resize(a.X.size() - 1);
		return true;
	}

	static bool addelement(Type& a, int num, int pos) {
		if (pos < 0 || pos > a.X.size()) { return false; }
		a.X.resize(a.X.size() + 1);
		int buff[2] = { num, 0 };
		for (pos; pos < a.X.size(); pos++) {
			buff[1] = a.X[pos];
			a.X[pos] = buff[0];
			int x = buff[0];
			buff[0] = buff[1];
			buff[1] = x;
		}
		return true;
	}
	static int searchindexprost(Type& a, int& r) {
		int k = 0;
		for (int pos = 0; pos < a.X.size(); pos++) {
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
		for (int pos = 0; pos < a.X.size(); pos++) {
			if (a.X[pos] % multiple == 0)
				ADT::deleteinpos(a, pos);
		}
	}
	static bool addinposwithold(Type& a, int pos, int number) {
		if (pos < 0 || pos > a.X.size() || a.X.size() == 100) { return false; }
		int c = 0, b = a.X[pos], h = a.X.size();
		h++;
		a.X.resize(h);
		int buff[2] = { number, 0 };
		for (int p = pos; p < a.X.size(); p++) {
			buff[1] = a.X[p];
			a.X[p] = buff[0];
			int x = buff[0];
			buff[0] = buff[1];
			buff[1] = x;
		}
		return true;
	}
	static void NewMas(Type& a, Type& b) {
		int k = 0, s = 0;
		for (int pos = 0; pos < a.X.size(); pos++) {
			for (int i = 2; i <= sqrt(a.X[pos]); i++) {
				if (a.X[pos] % i == 0) {
					k = a.X[pos];
					a.X[pos] = 0;
				}
			}
			if (a.X[pos] != 0) {
				s++;
				b.X.resize(s);
				b.X[s - 1] = a.X[pos];
			}
			if (a.X[pos] == 0)
				a.X[pos] = k;
		}
	}
};

int main()
{
	setlocale(0, "");
	cout << "������ �������: ";
	int n = 0;
	cin >> n;
	ADT::Type a(n), b(1);
	char ch = 0;
	system("cls");
	while (ch != 27) {
		cout << "������� �������� � ���:\n";
		ADT::output(a);
		cout << "\n\n�������� ��������:\n1. ������ ��������� �������� � ���\n2. ������ �������� � ����������";
		cout << (a.X.size() != 0 ? "\n3. ������� ��������.\n4. �������� ������� � �������" : "");
		cout << (a.X.size() != 0 ? "\n5. ������� ��� ����� ������� 7\n6. �������� �������� � ������� ����� �������� �����" : "");
		cout << (a.X.size() != 0 ? "\n7. �������� ������ �������� �����" : "");
		cout << (a.X.size() != 0 ? "\n8. ����� ������" : "");
		ch = _getch();
		system("cls");
		if (ch == '1') {
			ADT::randominput(a);
		}
		else if (ch == '2') {
			ADT::input(a);
		}
		else if (ch == '3' && a.X.size() != 0) {
			cout << "������� �������: ";
			int r;
			cin >> r;
			if (!ADT::deleteinpos(a, r)) {
				cout << "\n������. ������� ��� ���\a\n������� ����� �������, ����� ����������";
				_getch();
			}
		}
		else if (ch == '4' && a.X.size() != 0) {
			cout << "������� �������: ";
			int r, g;
			cin >> r;
			cout << "������� �����: ";
			cin >> g;
			ADT::addelement(a, g, r);
		}
		else if (ch == '5' && a.X.size() != 0) {
			ADT::deletemultipleelements(a, 7);
		}
		else if (ch == '6' && a.X.size() != 0) {
			int r, g;
			ADT::searchindexprost(a, r);
			cout << "������� �����: ";
			cin >> g;
			if (!ADT::addinposwithold(a, r, g)) {
				cout << "\n������. ������� ��� ���\a\n������� ����� �������, ����� ����������";
				_getch();
			}
		}
		else if (ch == '7' && a.X.size() != 0) {
			int r;
			cout << "������ �������� �����: " << ADT::searchindexprost(a, r);
			cout << "\n������� ����� �������, ����� ����������";
			_getch();
		}
		else if (ch == '8' && a.X.size() != 0) {
			ADT::NewMas(a, b);
			cout << "������ ������: ";
			ADT::output(a);
			cout << "\n\n";
			cout << "����� ������: ";
			ADT::output(b);
			_getch();
		}
		system("cls");
	}
}