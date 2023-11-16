#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <vector>
#include <cstdio>

using namespace std;

void Cfile(string filename) {
	ofstream File(filename+".txt");
}

void completion(string filename, int ln) {
	srand(time(0));
	fstream file(filename + ".txt", ios::out | ios::binary);
	if (!file.is_open()) return;
	for (int i = 0; i < ln; i++) {
		for (int j = 0; j < 5; j++) {
			file << rand() % 9;
			if (rand() % 2 == 0 && j < 4) file << " ";
			if (file.fail()) break;
		}
		file << "\n";
	}
	file.close();
}

void output(string filename) {
	fstream file(filename + ".txt", ios::in);
	string line;
	if (!file.is_open()) return;
	while (getline(file, line)){
		cout << line << endl;
		if (file.fail()) break;
	}
	file.close();
}

void fileappend(string filename) {
	fstream file(filename + ".txt", ios::app | ios::binary);
	if (!file.is_open()) return;
		for (int j = 0; j < 5; j++) {
			file << rand() % 9;
			if (rand() % 2 == 0 && j < 4) file << " ";
			if (file.fail()) break;
		}
		file << "\n";
	file.close();
}

void meaningpos(string filename, int n) {
	fstream file(filename + ".txt", ios::in);
	if (!file.is_open()) return;
	int count = 0;
	string number;
	while (!file.eof()) {
		char temp;
		file.get(temp);
		if (temp >= '0' && temp <= '9') {
			number += temp;
			while (file.get(temp) && (temp >= '0' && temp <= '9')) 
				number += temp;
			count++;
			if (count == n) {
				cout << n << " �����: " << number << endl;
				file.close();
				return;
			}
			number = "";
		}
	}
	cout << "�� ������� ��� �����" << endl;
	file.close();
}

int counter(string filename) {
	int number, count = 0;
	fstream file(filename + ".txt", ios::in);
	if (!file.is_open()) return -1;
	while (file >> number) {
		count++;
		if (file.fail()) break;
	}
	file.close();
	return count;
}

void deletestr(string filename, int pos) {
	vector<string> buffer;
	string line;
	fstream file(filename + ".txt", ios::in);
	if (!file.is_open()) return;
	while (getline(file, line)) {
		buffer.push_back(line);
		if (file.fail()) break;
	}
	file.close();
	if (!(remove((filename + ".txt").c_str()) == 0)) return;
	buffer.erase(buffer.begin() + pos);
	ofstream File(filename + "new.txt", ios::out | ios::binary);
	if (!File.is_open()) return;
	for (int i = 0; i < buffer.size(); i++) {
		File << buffer[i] << "\n";
		if (File.fail()) break;
	}
	File.close();
	if (!(rename((filename + "new.txt").c_str(), (filename + ".txt").c_str()) == 0)) cout << "������ �������������� ���������� �����" << endl;
}

struct Table {
	int key;
	char name[20];
	char address[20];
};

void textToBinary(string binaryfilename) {
	fstream file("Table.txt", ios::in);
	ofstream binaryfile(binaryfilename + ".txt", ios::out | ios::binary);
	if (!file.is_open() || !binaryfile.is_open()) return;
	Table table;
	while (file >> table.key) {
		file >> table.name >> table.address;
		binaryfile.write(reinterpret_cast<char*>(&table), sizeof(Table));
		if (file.fail()) break;
	}
	file.close();
	binaryfile.close();
}

void binaryToText(string binaryfileName) {
	fstream binaryfile(binaryfileName + ".txt", ios::in | ios::binary);
	if (!binaryfile.is_open()) return;
	ofstream newfile("New Table.txt", ios::out);
	if (!newfile.is_open()) return;
	Table table;
	while (binaryfile.read(reinterpret_cast<char*>(&table), sizeof(Table))) {
		newfile << table.key << " " << table.name << " " << table.address << endl;
		if (newfile.fail()) break;
	}
	binaryfile.close();
	newfile.close();
}

void outputbinaryfile(string binaryfilename) {
	fstream binaryfile(binaryfilename + ".txt", ios::in | ios::binary);
	if (!binaryfile.is_open()) return;
	Table table;
	while (binaryfile.read(reinterpret_cast<char*>(&table), sizeof(Table))) {
		cout << table.key << " " << table.name << " " << table.address << endl;
		if (binaryfile.fail()) break;
	}
	binaryfile.close();
}

Table findbykey(string binaryfilename, int key) {
	fstream binaryfile(binaryfilename + ".txt", ios::in | ios::binary);
	Table nfk = { -1, "������ �� �������" };
	if (!binaryfile.is_open()) return nfk;
	Table table;
	while (binaryfile.read(reinterpret_cast<char*>(&table), sizeof(Table))) {
		if (table.key == key) {
			binaryfile.close();
			return table;
		}
		if (binaryfile.fail()) break;
	}
	binaryfile.close();
	cout << "������ � �������� ������ �� �������" << endl;
	return nfk;
}

void deletebykey(string binaryfilename, int keyToDelete) {
	fstream binaryfile(binaryfilename + ".txt", ios::in | ios::binary);
	if (!binaryfile.is_open()) return;
	string tempfilename = binaryfilename + ".temp";
	fstream tempbinaryfile(tempfilename, ios::out | ios::binary);
	if (!tempbinaryfile.is_open()) {
		binaryfile.close();
		return;
	}
	size_t tableSize = sizeof(Table);
	Table table;
	while (binaryfile.read(reinterpret_cast<char*>(&table), tableSize)) {
		if (table.key != keyToDelete) tempbinaryfile.write(reinterpret_cast<const char*>(&table), tableSize);
		if (binaryfile.fail()) break;
	}
	binaryfile.close();
	tempbinaryfile.close();
	if (remove((binaryfilename + ".txt").c_str()) != 0) return;
	if (rename(tempfilename.c_str(), (binaryfilename + ".txt").c_str()) != 0) cout << "������ �������������� ���������� �����" << endl;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string filename = " ", binaryfilename = " ";
	int key;
	char ch = 0;
	while (ch != 27) {
		system("cls");
		cout << "��������� ����:\n";
		output(filename);
		cout << "\n�������� ����:\n";
		outputbinaryfile(binaryfilename);
		cout << "\n�������� ��������:\n1. �������� �����\n2. ��������� ���������� �����\n3. ���������� ��������� ������ � ����� �����\n4. ����� ����� �� �������\n5. ������� ���������� �����\n6. �������� ������ �� ������\n7. �������� ��������� ����� � ������� � ���� ������\n8. ������� �� ��������� ����� � ���������\n9. ����� �� ����� �� ��������� �����\n0. �������� �� ����� �� ��������� �����\n";
		ch = _getch();
		switch (ch)
		{
		default:
			break;
		case '1':
			cout << "\n������� �������� ����� >> ";
			cin >> filename;
			Cfile(filename);
			break;
		case '2':
			int ln;
			cout << "\n������� ���������� ����� >> ";
			cin >> ln;
			completion(filename, ln);
			break;
		case '3':
			fileappend(filename);
			break;
		case '4':
			int pos;
			cout << "\n������� ������� ����� >> ";
			cin >> pos;
			meaningpos(filename, pos);
			_getch();
			break;
		case '5':
			cout << "\n����������� ����� � �����: " << counter(filename);
			_getch();
			break;
		case '6':
			int pos1;
			cout << "\n������� ����� ������ >> ";
			cin >> pos1;
			deletestr(filename, pos1);
			break;
		case '7':
			cout << "\n������� �������� ��������� ����� >> ";
			cin >> binaryfilename;
			textToBinary(binaryfilename);
			break;
		case '8':
			binaryToText(binaryfilename);
			break;
		case '9':
			cout << "\n������� ���� >> ";
			cin >> key;
			Table tablekey = findbykey(binaryfilename, key);
			if (tablekey.key != -1) cout << tablekey.key << " " << tablekey.name << " " << tablekey.address << endl;
			_getch();
			break;
		case '0':
			cout << "\n������� ���� >> ";
			cin >> key;
			deletebykey(binaryfilename, key);
			break;
		}
	}
	cout << "\n�����";
	return 0;
}