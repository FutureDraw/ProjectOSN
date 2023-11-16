#include <iostream>
#include <unordered_set>
#include <conio.h>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void insertStart(Node** L, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = *L;

    *L = newNode;
}

void insertEnd(Node** L, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = NULL;

    if (*L != NULL) {
        Node* current = *L;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
    else
        *L = newNode;
}

void createList(Node** L, int n) {
    for (int i = 1; i <= n; i++) {
        insertStart(L, i);
    }
}

Node* createL(Node* L1, Node* L2) {
    Node* L3 = NULL;
    unordered_set<int> uniqueValues;

    Node* current1 = L1;
    while (current1 != NULL) {
        if (uniqueValues.find(current1->data) == uniqueValues.end()) {
            insertEnd(&L3, current1->data);
            uniqueValues.insert(current1->data);
        }
        current1 = current1->next;
    }

    Node* current2 = L2;
    while (current2 != NULL) {
        if (uniqueValues.find(current2->data) == uniqueValues.end()) {
            insertEnd(&L3, current2->data);
            uniqueValues.insert(current2->data);
        }
        current2 = current2->next;
    }

    return L3;
}

void deletepos(Node** L) {
    if (*L == NULL || (*L)->next == NULL) {
        return;
    }

    Node* prev = NULL;
    Node* current = *L;
    int position = 1;

    while (current != NULL) {
        if (position % 2 == 0) {
            Node* nextNode = current->next;
            delete current;
            if (prev != NULL) {
                prev->next = nextNode;
            }
            else {
                *L = nextNode;
            }
            current = nextNode;
        }
        else {
            prev = current;
            current = current->next;
        }
        position++;
    }
}

void insertSum(Node* L2) {
    if (L2 == NULL || L2->next == NULL) {
        return;
    }

    Node* current = L2;
    while (current != NULL && current->next != NULL) {
        int sum = current->data + current->next->data;

        Node* newNode = new Node;
        newNode->data = sum;
        newNode->next = current->next->next;

        current->next->next = newNode;
        current = newNode->next;
    }
}

void output(Node* L) {
    Node* current = L;

    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }

    cout << endl;
}

int main() {
    setlocale(0, "");
    Node* L1 = NULL;
    Node* L2 = NULL;
    char ch = 0;
    int value;
    system("cls");
    while (ch != 27) {
        Node* L3 = createL(L1, L2);
        system("cls");
        cout << "L1: "; output(L1);
        cout << "\nL2: "; output(L2);
        cout << "\n1. Добавить число в список\n2. Добавить число в начало списка\n3. Создание списка из n узлов, используя функцию вставки перед узлом\n4. Вывести список L\n5. Удалить из списка L1 чётные позиции\n6. Вставить в списке L2 сумму пар после этих пар";
        ch = _getch();
        switch (ch)
        {
        default:
            break;
        case '1':
            system("cls");
            cout << "1. Список L1 | 2. Список L2";
            ch = _getch();
            switch (ch)
            {
            default:
                break;
            case '1':
                system("cls");
                cin.clear();
                cout << "Введите число >> ";
                cin >> value;
                insertEnd(&L1, value);
                break;
            case  '2':
                system("cls");
                cin.clear();
                cout << "Введите число >> ";
                cin >> value;
                insertEnd(&L2, value);
                break;
            }
            break;
        case '2':
            system("cls");
            cout << "1. Список L1 | 2. Список L2";
            ch = _getch();
            switch (ch)
            {
            default:
                break;
            case '1':
                system("cls");
                cin.clear();
                cout << "Введите число >> ";
                cin >> value;
                insertStart(&L1, value);
                break;
            case  '2':
                system("cls");
                cin.clear();
                cout << "Введите число >> ";
                cin >> value;
                insertStart(&L2, value);
                break;
            }
            break;
        case '3':
            system("cls");
            cout << "1. Список L1 | 2. Список L2";
            ch = _getch();
            switch (ch)
            {
            default:
                break;
            case '1':
                system("cls");
                cin.clear();
                cout << "Введите число n >> ";
                cin >> value;
                createList(&L1, value);
                break;
            case  '2':
                system("cls");
                cin.clear();
                cout << "Введите число n >> ";
                cin >> value;
                createList(&L2, value);
                break;
            }
            break;
        case '4':
            system("cls");
            cout << "L: ";
            output(L3);
            _getch();
            break;
        case '5':
            deletepos(&L1);
            break;
        case '6':
            insertSum(L2);
            break;
        }
    }
    cout << "\nВыход";
    return 0;
}
