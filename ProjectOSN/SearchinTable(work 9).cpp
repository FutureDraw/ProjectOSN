#include<iostream>
#include<vector>
#include<iomanip>
#include<Windows.h>
#include<conio.h>
#include<chrono>
#include<string>

using namespace std;
int ci = 0;
int N;

struct Table {
    int key;
    string firstname;
    string name;
    string adress;
    string house;
};

struct Type {
    chrono::time_point<chrono::steady_clock> start, end_time;
    double cpu_ms = 0;
    vector<Table> X;
    Type() = default;

    void randominput() {
        srand(time(0));
        for (int i = 0; i < N; i++) {
            Table record;
            record.key = rand() % 101;
            record.firstname = "Firstname " + to_string(i);
            record.name = "Name " + to_string(i);
            record.adress = "Address " + to_string(i);
            record.house = "House " + to_string(i);
            X.push_back(record);
        }
    }

    int linearSearch(int key) {
        ci = 0;
        start = chrono::steady_clock::now();
        for (int i = 0; i < X.size(); i++) {
            ci++;
            if (X[i].key == key) {
                end_time = chrono::steady_clock::now();
                cpu_ms = chrono::duration<double, milli>(end_time - start).count();
                return i + 1;
            }
        }
        return -1;
    }

    int BarrierSearch(int key) {
        ci = 0;
        start = chrono::steady_clock::now();
        int last = X.size() - 1;
        Table lastRecord = X[last];
        X[last].key = key;
        int i = 0;
        while (X[i].key != key) {
            ++i;
        }
        X[last] = lastRecord;
        ci++;
        if (i < last || X[last].key == key) {
            end_time = chrono::steady_clock::now();
            cpu_ms = chrono::duration<double, milli>(end_time - start).count();
            return i + 1;
        }
        return -1;
    }

    int interpolationSearch(int key) {
        ci = 0;
        start = chrono::steady_clock::now();
        int low = 0;
        int high = X.size() - 1;
        while (low <= high && key >= X[low].key && key <= X[high].key) {
            ci++;
            if (low == high) {
                if (X[low].key == key) {
                    end_time = chrono::steady_clock::now();
                    cpu_ms = chrono::duration<double, milli>(end_time - start).count();
                    return low + 1;
                }
                return -1;
            }
            int pos = low + ((key - X[low].key) * (high - low)) / (X[high].key - X[low].key);
            ci++;
            if (X[pos].key == key) {
                return pos + 1;
            }
            if (X[pos].key < key) {
                low = pos + 1;
            }
            else {
                high = pos - 1;
            }
        }
        return -1;
    }

    void input() {
        int key;
        string firstname, name, adress, house;
        cout << "Введите данные:\nНомер Ч.Б. ФИО Адресс >> ";
        cin >> key >> firstname >> name >> adress >> house;
        X.push_back(Table{ key, firstname, name, adress, house });
    }

    void output() {
        cout << "Номер Ч.Б." << setw(12) << "ФИО" << setw(22) << "Адресс\n";
        cout << setfill('-') << setw(49) << "" << setfill(' ') << endl;
        for (int pos = 0; pos < X.size(); pos++) {
            cout << setw(7) << X[pos].key << setw(14) << X[pos].firstname << " " << X[pos].name << setw(18) << X[pos].adress << " " << X[pos].house << setw(5) << "\n";
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Type a;
    int key, index;
    char ch = 0;
    while (ch != 27) {
        system("cls");
        a.output();
        cout << "\n1. Добавить запись в таблицу\n2. Линейный поиск методом грубой силы\n3. Барьерный поиск\n4. Интерполяционный поиск";
        ch = _getch();
        switch (ch)
        {
        default:
            break;
        case '1':
            system("cls");
            cin >> N;
            a.randominput();
            //a.input();
            break;
        case '2':
            system("cls");
            cout << "Номер читательского билета >> ";
            cin >> key;
            system("cls");
            index = a.linearSearch(key);
            if (index != -1) {
                cout << "Номер в таблице: " << index;
                cout << "\nВремя: " << a.cpu_ms << "ms" << "\nСравнений: " << ci;
                _getch();
            }
            else {
                cout << "Данные отсутствуют";
                _getch();
            }
            break;
        case '3':
            system("cls");
            cout << "Номер читательского билета >> ";
            cin >> key;
            system("cls");
            index = a.BarrierSearch(key);
            if (index != -1) {
                cout << "Номер в таблице: " << index;
                cout << "\nВремя: " << a.cpu_ms << "ms" << "\nСравнений: " << ci;
                _getch();
            }
            else {
                cout << "Данные отсутствуют";
                _getch();
            }
            break;
        case '4':
            system("cls");
            cout << "Номер читательского билета >> ";
            cin >> key;
            system("cls");
            index = a.interpolationSearch(key);
            if (index != -1) {
                cout << "Номер в таблице: " << index;
                cout << "\nВремя: " << a.cpu_ms << "ms" << "\nСравнений: " << ci;
                _getch();
            }
            else {
                cout << "Данные отсутствуют";
                _getch();
            }
            break;
        }
    }
    cout << "\nВыход";
    return 0;
}