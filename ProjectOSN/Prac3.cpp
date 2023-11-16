#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <Windows.h>
#include <conio.h>

using namespace std;

struct Hashtable {
    int key = -1;
    int filepos = -1;
    bool insert = 0;
};

struct Table {
    int key = -1;
    char data1[20] = "";
    char data2[20] = "";
};

int myhash(int key, int size) {
    int hash = key;
    hash = hash * (31 + key);
    hash = hash % size;
    return hash;
}

int rehash(int hash, int size) {
    hash++;
    hash = hash % size;
    return hash;
}

void inputBF(int FILESIZE) {
    ofstream file("binaryfile.txt", ios::out | ios::binary);
    for (int i = 0; i < FILESIZE; i++) {
        Table table{ 10000 + i };
        char data1[20] = "СмирновА.В";
        char data2[20] = "МИРЭА7";
        strcat_s(data1, to_string(i).c_str());
        strcpy_s(table.data1, data1);
        strcat_s(data2, to_string(i).c_str());
        strcpy_s(table.data2, data2);
        file.write((char*)&table, sizeof(Table));
    }
    file.close();
}

void outputBF(int FILESIZE) {
    cout << "[ ключ]:\t          Имя|\t       Адрес|\n" << "=============================================\n";
    fstream file("binaryfile.txt", ios::in | ios::binary);
    for (int i = 0; i < FILESIZE; i++) {
        Table table;
        file.read((char*)&table, sizeof(Table));
        printf("[%5d]:\t%13s|\t%12s|\n", table.key, table.data1, table.data2);
    }
    cout << endl;
    file.close();
}

void inputHT(int FILESIZE, Hashtable* hashtable, int TABLESIZE) {
    fstream file("binaryfile.txt", ios::in | ios::binary);
    file.seekg(0);
    for (int i = 0; i < FILESIZE; i++) {
        Table table;
        file.read((char*)&table, sizeof(Table));
        int hash = myhash(table.key, TABLESIZE);
        while (hashtable[hash].key != -1) hash = rehash(hash, TABLESIZE);
        hashtable[hash].key = table.key;
        hashtable[hash].filepos = i * sizeof(Table);
        hashtable[hash].insert = 1;
    }
    file.close();
}

void outputHT(int FILESIZE, Hashtable* hashtable, int TABLESIZE) {
    cout << "[hash]:\t    Ключ|\tПоизиция|\n" << "=================================\n";
    for (int i = 0; i < TABLESIZE; i++) {
        if (hashtable[i].key == -1) printf("[%4d]:\n", i);
        else printf("[%4d]:\t%8d|\t%8d|\n", i, hashtable[i].key, hashtable[i].filepos);
    }
}

void resizeHashtable(Hashtable*& hashtable, int& TABLESIZE) {
    int newTableSize = TABLESIZE * 2;
    Hashtable* newHashtable = new Hashtable[newTableSize];
    for (int i = 0; i < TABLESIZE; i++) {
        if (hashtable[i].insert) {
            int key = hashtable[i].key;
            int hash = myhash(key, newTableSize);
            while (newHashtable[hash].insert) {
                hash = rehash(hash, newTableSize);
            }
            newHashtable[hash] = hashtable[i];
        }
    }
    hashtable = newHashtable;
    TABLESIZE = newTableSize;
}

void insertKey(int& key, const char* data1, const char* data2, Hashtable*& hashtable, int& FILESIZE, int& TABLESIZE) {
    if (FILESIZE >= TABLESIZE) resizeHashtable(hashtable, TABLESIZE);
    Table table{ key };
    strcpy_s(table.data1, data1);
    strcpy_s(table.data2, data2);
    fstream file("binaryfile.txt", ios::out | ios::binary | ios::app);
    file.write((char*)&table, sizeof(Table));
    file.close();
    int hash = myhash(key, TABLESIZE);
    while (hashtable[hash].insert) {
        if (hashtable[hash].key == key) {
            hashtable[hash].filepos = FILESIZE * sizeof(Table);
            return;
        }
        hash = rehash(hash, TABLESIZE);
    }
    hashtable[hash].key = key;
    hashtable[hash].filepos = FILESIZE * sizeof(Table);
    hashtable[hash].insert = true;
    FILESIZE++;
}

void fileremove(int position) {
    const char* originalFile = "binaryfile.txt";
    const char* tempFile = "tempfile.txt";
    Table table;
    ifstream inFile(originalFile, ios::in | ios::binary);
    ofstream outFile(tempFile, ios::out | ios::binary);
    if (!inFile || !outFile) return;
    int recordSize = sizeof(Table);
    int fileSize = 0;
    inFile.seekg(0, ios_base::end);
    fileSize = inFile.tellg();
    inFile.seekg(0, ios_base::beg);
    for (int i = 0; i < position; i += recordSize) {
        inFile.read((char*)&table, recordSize);
        outFile.write((char*)&table, recordSize);
    }
    inFile.seekg(recordSize, ios_base::cur);
    while (inFile.read((char*)&table, recordSize))
        outFile.write((char*)&table, recordSize);
    inFile.close();
    outFile.close();
    remove(originalFile);
    rename(tempFile, originalFile);
}

void remove(int key, Hashtable* hashtable, int TABLESIZE, int& FILESIZE) {
    int hash = myhash(key, TABLESIZE);
    while (hashtable[hash].key != key) {
        if (hashtable[hash].insert == 0) return;
        hash = rehash(hash, TABLESIZE);
    }
    int removeposition = hashtable[hash].filepos;
    fileremove(removeposition);
    FILESIZE--;
    hashtable[hash].key = -1;
    hashtable[hash].filepos = -1;
    hashtable[hash].insert = 0;
    for (int i = 0; i < TABLESIZE; i++) {
        if (hashtable[i].filepos > removeposition) 
            hashtable[i].filepos -= sizeof(Table);
    }
}

void findekey(int TABLESIZE, Hashtable* hashtable, int keytofind) {
    chrono::time_point<chrono::steady_clock> start, end_time;
    double cpu_ms = 0;
    fstream file("binaryfile.txt", ios::in | ios::binary);
    Table table;
    start = chrono::steady_clock::now();
    int hash = myhash(keytofind, TABLESIZE);
    while (hashtable[hash].key != keytofind) hash = rehash(hash, TABLESIZE);
    file.seekg(hashtable[hash].filepos);
    file.read((char*)&table, sizeof(Table));
    end_time = chrono::steady_clock::now();
    cpu_ms = chrono::duration<double, milli>(end_time - start).count();
    cout << "Двоичный файл:\n" << "[ ключ]:\t          Имя|\t       Адрес|\n" << "=============================================\n";
    printf("[%5d]:\t%13s|\t%12s|\nВремя поиска: %fms\n", table.key, table.data1, table.data2, cpu_ms);
    file.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int FILESIZE = -1;
    cout << "Введите размер таблицы >> ";
    cin >> FILESIZE;
    inputBF(FILESIZE);
    int TABLESIZE = FILESIZE + 20;
    Hashtable* hashtable = new Hashtable[TABLESIZE];
    inputHT(FILESIZE, hashtable, TABLESIZE);
    int key = -1;
    char data1[20] = "СмирновГ.Г";
    char data2[20] = "МИРЭАГГ";
    char ch = 0;
    while (ch != 27) {
        system("cls");
        cout << "Двоичный файл:\n";
        outputBF(FILESIZE);
        cout << "\nВыберите действие:\n1. Удалить по ключу\n2. Поиск по ключу\n3. Вставь ключ\n4. Хеш таблица\n\n";
        ch = _getch();
        switch (ch)
        {
        default:
            break;
        case '1':
            cout << "Введите ключ >> ";
            cin >> key;
            remove(key, hashtable, TABLESIZE, FILESIZE);
            break;
        case '2':
            cout << "Введите ключ >> ";
            cin >> key;
            system("cls");
            findekey(TABLESIZE, hashtable, key);
            _getch();
            break;
        case '3':
            cout << "Введите ключ для вставки >> ";
            cin >> key;
            insertKey(key, data1, data2, hashtable, FILESIZE, TABLESIZE);
            break;
        case '4':
            system("cls");
            cout << "Хеш таблица:\n";
            outputHT(FILESIZE, hashtable, TABLESIZE);
            _getch();
            break;
        }
    }
    cout << "\nВыход";
    return 0;
}