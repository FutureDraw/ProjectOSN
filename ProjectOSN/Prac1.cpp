#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>

using namespace std;

string xtob(int x) {
	int ox = x;
	string x1;
	if (x == 0) x1 = "000000000";
	while (x){
		if ((x % 2) == 1) x1 = "1" + x1;
		else x1 = "0" + x1;
		x /= 2;
	}
	return x1 + " " + to_string(ox);
}

int task1(int x) {
	unsigned int mask = ((1 << 5) | (1 << 7));
	return x|mask;
}

int task2(int x) {
	unsigned int mask = ~((1 << 10) | (1 << 11) | (1 << 12) | (1 << 13));
	return x&mask;
}

int task3(int x) {
	return x<<3;
}

int task4(int x) {
	return x>>3;
}

int task5(int bit, int x) {
	unsigned int mask1 = 1;
	return x|(mask1 << bit);
}

int main(){
	setlocale(0, "");
	const int x = 0x358F;
	int num = 0;
	char ch = 0;
	while (ch != 27) {
		system("cls");
		cout << "¬ыберите действие:\n1. ”пр. 1\n2. ”пр. 2\n3. ”пр. 3\n4. ”пр. 4\n5. ”пр. 5";
		ch = _getch();
		switch (ch)
		{
		default:
			break;
		case '1':
			system("cls");
			cout << xtob(x) << endl;
			cout << xtob(task1(x)) << endl;
			_getch();
			break;
		case '2':
			system("cls");
			int num;
			cout << "¬ведите число >> ";
			cin >> num;
			cout << setw(49) << xtob(num) << endl;
			cout << setw(49) << xtob(task2(num)) << endl;
			_getch();
			break;
		case '3':
			system("cls");
			cout << "¬ведите число >> ";
			cin >> num;
			cout << setw(49) << xtob(num) << endl << setw(50) << xtob(task3(num));
			_getch();
			break;
		case '4':
			system("cls");
			cout << "¬ведите число >> ";
			cin >> num;
			cout << setw(50) << xtob(num) << endl << setw(49) << xtob(task4(num));
			_getch();
			break;
		case '5':
			system("cls");
			int bit;
			cout << "¬ведите число >> ";
			cin >> num;
			cout << "¬ведите номер бита >> ";
			cin >> bit;
			cout << setw(49) << xtob(num) << endl;
			cout << setw(49) << xtob(task5(bit, num)) << endl;
			_getch();
			break;
		}
	}
	cout << "\n¬ыход";
	return 0;
}