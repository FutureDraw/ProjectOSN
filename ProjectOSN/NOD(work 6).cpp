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
	cout << "Введите два числа >> ";
	cin >> a >> b;
	cout << "НОД чисел: " << a << " и " << b << " = " << nod(a, b);
	return 0;
}