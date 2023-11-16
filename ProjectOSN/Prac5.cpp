#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <chrono>

using namespace std;

struct BinaryNode {
	int value = -1;
	int pos = -1;
	BinaryNode* left = NULL;
	BinaryNode* right = NULL;
	BinaryNode(int value = -1, int pos = -1, BinaryNode* left = NULL, BinaryNode* right = NULL) : value(value), pos(pos), left(left), right(right) {}
	void print(int depth = 5) {
		cout << setw(depth) << this->value << endl;
		if (this->left)
			left->print(depth + 5);
		if (this->right)
			right->print(depth + 5);
	}

	void add(int value, int pos) {
		if (this->value == -1 && this->pos == -1) {
			this->left = (this->left ? this->left : NULL);
			this->right = (this->right ? this->right : NULL);
			this->value = value;
			this->pos = pos;
			return;
		}
		if (this->value < value)
			if (this->left)
				left->add(value, pos);
			else
				left = new BinaryNode(value, pos);
		else
			if (this->right)
				right->add(value, pos);
			else
				right = new BinaryNode(value, pos);
	}

	void remove(int value) {
		if (this->value < value)
			if (this->left) {
				if (this->left->value == value)
					this->left = new BinaryNode(-1, -1, this->left->left, this->left->right);
				else this->left->remove(value);
			}
			else
				if (this->right)
					if (this->right->value == value)
						this->right = new BinaryNode(-1, -1, this->right->left, this->right->right);
					else this->right->remove(value);
	}

	int search(int value) {
		if (this->value == value)
			return this->pos;
		if (this->value < value)
			return this->left->search(value);
		else
			return this->right->search(value);
	}
};

struct BinaryTree
{
private:
	BinaryNode* root;
public:
	BinaryTree(int value = -1, int pos = -1, BinaryNode* left = NULL, BinaryNode* right = NULL) : root(new BinaryNode(value, pos, left, right)) {}
	void print() { root->print(); }
	void add(int value, int pos) { root->add(value, pos); }
	int search(int value) { return root->search(value); }
	void remove(int value) { root->remove(value); }
};

struct BalanceNode {
	int value = -1;
	int pos = -1;
	bool isBlack = false;
	BalanceNode* left = NULL;
	BalanceNode* right = NULL;
	BalanceNode* parent = NULL;
	BalanceNode(int value = -1, int pos = -1, bool isBlack = false, BalanceNode* parent = NULL, BalanceNode* left = NULL, BalanceNode* right = NULL) : value(value), pos(pos), isBlack(isBlack), left(left), right(right), parent(parent) {}
	void print(int depth = 5) {
		cout << setw(depth) << this->value << " " << isBlack << endl;
		if (this->left)
			left->print(depth + 5);
		if (this->right)
			right->print(depth + 5);
	}

	BalanceNode* add(int value, int pos) {
		if (this->value == -1 && this->pos == -1) {
			this->value = value;
			this->pos = pos;
			return this;
		}
		if (this->value < value)
			if (left)
				return left->add(value, pos);
			else
				return left = new BalanceNode(value, pos, false, this);
		else
			if (right)
				return right->add(value, pos);
			else
				return right = new BalanceNode(value, pos, false, this);
	}
	bool isBalck() { return (this ? this->isBlack : true); }
	void setBlack(bool isBlack) { this->isBlack = isBlack; }

	BalanceNode* remove(int value) {
		if (this->value < value)
			if (this->left) {
				if (this->left->value == value)
					return this->left = new BalanceNode(-1, -1, true, this->left->parent, this->left->left, this->left->right);
				else
					return this->left->remove(value);
			}
			else
				if (this->right)
					if (this->right->value == value)
						return this->right = new BalanceNode(-1, -1, true, this->right->parent, this->right->left, this->right->right);
					else
						return this->right->remove(value);
		return this;
	}

	int search(int value) {
		if (this->value == value)
			return this->pos;

		if (this->value < value)
			return this->left->search(value);
		else
			return this->right->search(value);
	}

	static void fix(BalanceNode*& root, BalanceNode*& node) {
		BalanceNode* parent = nullptr;
		BalanceNode* grandParent = nullptr;
		while (node != root && !node->isBalck() && !node->parent->isBalck()) {
			parent = node->parent;
			grandParent = parent->parent;
			if (parent == grandParent->left) {
				BalanceNode* uncle = grandParent->right;
				if (!uncle->isBalck()) {
					uncle->setBlack(true);
					parent->setBlack(true);
					grandParent->setBlack(false);
					node = grandParent;
				}
				else {
					if (node == parent->right) {
						parent->rotateLeft(root);
						node = parent;
						parent = node->parent;
					}
					grandParent->rotateRight(root);
					const bool color = grandParent->isBlack;
					grandParent->isBlack = parent->isBlack;
					parent->isBlack = color;
					node = parent;
				}
			}
			else {
				BalanceNode* uncle = grandParent->left;
				if (!uncle->isBalck()) {
					uncle->setBlack(true);
					parent->setBlack(true);
					grandParent->setBlack(false);
					node = grandParent;
				}
				else {
					if (node == parent->left) {
						parent->rotateRight(root);
						node = parent;
						parent = node->parent;
					}
					grandParent->rotateLeft(root);
					const bool color = grandParent->isBlack;
					grandParent->isBlack = parent->isBlack;
					parent->isBlack = color;
					node = parent;
				}
			}
		}
		root->setBlack(true);
	}

	void rotateRight(BalanceNode*& root) {
		BalanceNode* leftChild = this->left;
		this->left = leftChild->right;
		if (this->left != nullptr)
			this->left->parent = this;
		leftChild->parent = this->parent;
		if (this->parent == nullptr)
			root = leftChild;
		else if (this == this->parent->left)
			this->parent->left = leftChild;
		else
			this->parent->right = leftChild;
		leftChild->right = this;
		this->parent = leftChild;
	}

	void rotateLeft(BalanceNode*& root) {
		BalanceNode* rightChild = this->right;
		this->right = rightChild->left;
		if (this->right != nullptr)
			this->right->parent = this;
		rightChild->parent = this->parent;
		if (this->parent == nullptr)
			root = rightChild;
		else if (this == this->parent->left)
			this->parent->left = rightChild;
		else
			this->parent->right = rightChild;
		rightChild->left = this;
		this->parent = rightChild;
	}
};

struct BalanceTree
{
private:
	BalanceNode* root;
public:
	BalanceTree(int value = -1, int pos = -1, BalanceNode* left = NULL, BalanceNode* right = NULL) : root(new BalanceNode(value, pos, false, left, right)) {}
	void print() { root->print(); }
	void add(int value, int pos) { BalanceNode* node = root->add(value, pos); BalanceNode::fix(root, node); }
	void remove(int value) { BalanceNode* node = root->remove(value); BalanceNode::fix(root, node); }
	int search(int value) { return root->search(value); }
};

struct Table {
	int key;
	char data1[20];
	char data2[20];
};

void textToBinary() {
	fstream file("Table.txt", ios::in);
	ofstream binaryfile("binaryfile.txt", ios::out | ios::binary);
	if (!file.is_open() || !binaryfile.is_open()) return;
	Table table;
	while (file >> table.key) {
		file >> table.data1 >> table.data2;
		binaryfile.write(reinterpret_cast<char*>(&table), sizeof(Table));
		if (file.fail()) break;
	}
	file.close();
	binaryfile.close();
}

void outputBF() {
    cout << "[ ключ]:\t          Имя|\t       Адрес|\n" << "=============================================\n";
    fstream binaryfile("binaryfile.txt", ios::in | ios::binary);
    Table table;
    while (binaryfile.read(reinterpret_cast<char*>(&table), sizeof(Table)))
        printf("[%5d]:\t%13s|\t%12s|\n", table.key, table.data1, table.data2);
    cout << endl;
    binaryfile.close();
}

bool FindbyLinearSr(int key) {
    fstream binaryfile("binaryfile.txt", ios::in | ios::binary);
    if (!binaryfile.is_open()) {
        cout << "Failed to open binary file." << endl;
        return false;
    }
    Table table;
    bool found = false;
    while (binaryfile.read(reinterpret_cast<char*>(&table), sizeof(Table))) {
        if (table.key == key) {
            cout << "Двоичный файл:\n" << "[ ключ]:\t          Имя|\t       Адрес|\n" << "=============================================\n";
            printf("[%5d]:\t%13s|\t%12s|\n", table.key, table.data1, table.data2);
            found = true;
            break;
        }
    }
    if (!found) cout << "Нет записи с текущим ключем\n";
    binaryfile.close();
    return found;
}

bool FindbyAddress(streampos faddress) {
    fstream binaryfile("binaryfile.txt", ios::in, ios::binary);
    if (!binaryfile.is_open()) return false;
    binaryfile.seekg(faddress);
    Table table;
    if (binaryfile.read(reinterpret_cast<char*>(&table), sizeof(Table))) {
        cout << "Двоичный файл:\n" << "[ ключ]:\t          Имя|\t       Адрес|\n" << "=============================================\n";
        printf("[%5d]:\t%13s|\t%12s|\n", table.key, table.data1, table.data2);
        binaryfile.close();
        return true;
    }
    else {
        cout << "Нет строки по текущему адрессу\n";
        binaryfile.close();
        return false;
    }
}

void AddRecord(const Table& newRecord) {
    fstream binaryfile("binaryfile.txt", ios::binary | ios::app);
    if (!binaryfile.is_open()) return;
    binaryfile.write(reinterpret_cast<const char*>(&newRecord), sizeof(Table));
    binaryfile.close();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Table table;
	BinaryTree binaryTree;
	BalanceTree balanceTree;
	Table reader;
	fstream binaryfile("binaryfile.txt", ios::in | ios::binary);
	chrono::time_point<chrono::steady_clock> start, end_time;
	double cpu_ms = 0;
	int val, pos = 0;
	char ch = 0;
	textToBinary();
	while (binaryfile.read(reinterpret_cast<char*>(&table), sizeof(Table))) {
		binaryTree.add(table.key, pos);
		balanceTree.add(table.key, pos);
		pos++;
	}
	while (ch != 27) {
		system("cls");
		cout << "Бинарное дерево:\n";
		binaryTree.print();
		cout << "\n\nСбалансированное дерево:\n";
		balanceTree.print();
		cout << "\n1. Поиск по ключу в бинарном дереве\n2. Поиск по ключу в сбалансированном дереве (красно-черное)\n3. Поиск по ключу в бинарном файле по ключу (линейный поиск)\n4. Таблица\n\n";
		ch = _getch();
		switch (ch)
		{
		default:
			break;
		case '1':
			cout << "Введите ключ >> ";
			cin >> val;
			start = chrono::steady_clock::now();
			FindbyAddress(sizeof(Table) * binaryTree.search(val));
			end_time = chrono::steady_clock::now();
			cpu_ms = chrono::duration<double, milli>(end_time - start).count();
			cout << "Время поиска: " << cpu_ms << "ms";
			_getch();
			break;
		case '2':
			cout << "Введите ключ >> ";
			cin >> val;
			start = chrono::steady_clock::now();
			FindbyAddress(sizeof(Table) * balanceTree.search(val));
			end_time = chrono::steady_clock::now();
			cpu_ms = chrono::duration<double, milli>(end_time - start).count();
			cout << "Время поиска: " << cpu_ms << "ms";
			_getch();
			break;
		case '3':
			cout << "Введите ключ >> ";
			cin >> val;
			start = chrono::steady_clock::now();
			FindbyLinearSr(val);
			end_time = chrono::steady_clock::now();
			cpu_ms = chrono::duration<double, milli>(end_time - start).count();
			cout << "Время поиска: " << cpu_ms << "ms";
			_getch();
			break;
		case '4':
			system("cls");
			outputBF();
			_getch();
			break;
		}
	}
	cout << "Выход";
	return 0;
}