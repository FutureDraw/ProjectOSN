#include <iostream>

using namespace std;

int nod(int a, int b) {
	if (b == 0)
		return a;
	else
		return nod(b, a % b);
}

int main() {
	setlocale(0, "");
	int a, b;
	cout << "������� ��� ����� >> ";
	cin >> a >> b;
	cout << "��� �����: " << a << " � " << b << " = " << nod(a, b);
	return 0;
}