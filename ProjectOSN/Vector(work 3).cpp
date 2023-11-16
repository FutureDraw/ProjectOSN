#include <iostream>
#include <vector>
#include <cmath>
#include <conio.h>

using namespace std;

class ADT {
public:
    struct Type {
        vector<pair<double, double>> X;
        Type(int n) {
            X.resize(n);
        }
    };

    static void input(Type& a, int n, int m) {
        for (int pos1 = 0; pos1 < n; pos1++) {
            system("cls");
            cout << "Многоугольник " << m << ": \n";
            cout << "Введите координаты x, y точки " << pos1 + 1 << " >> ";
            cin >> a.X[pos1].first;
            cin >> a.X[pos1].second;
        }
    }

    static void randominput(Type& a, Type& b) {
        srand(time(0));
        for (int pos1 = 0; pos1 < a.X.size(); pos1++) {
            a.X[pos1].first = rand() % 101;
            a.X[pos1].second = rand() % 101;
            b.X[pos1].first = rand() % 101;
            b.X[pos1].second = rand() % 101;
        }
    }

    static void output(Type& a, int n) {
        cout << "<";
        for (int pos1 = 0; pos1 < n; pos1++) {
            cout << "{" << a.X[pos1].first << "," << a.X[pos1].second << "}";
        }
        cout << ">\n";
    }

    static double Gaus(Type& a) {
        double area = 0;
        for (int pos1 = 0; pos1 < a.X.size(); pos1++) {
            int j = (pos1 + 1) % a.X.size();
            area += a.X[pos1].first * a.X[j].second - a.X[j].first * a.X[pos1].second;
        }
        area /= 2;
        return abs(area);
    }

    static bool is_inside(Type& a, Type& b) {
        int n = a.X.size(), m = b.X.size();
        for (int i = 0; i < n; i++) {
            bool flag = false;
            for (int j = 0; j < m; j++) {
                int k = (j + 1) % m;
                if ((b.X[j].second <= a.X[i].second && a.X[i].second < b.X[k].second ||
                    b.X[k].second <= a.X[i].second && a.X[i].second < b.X[j].second) &&
                    a.X[i].first < (b.X[k].first - b.X[j].first) * (a.X[i].second - b.X[j].second) / (b.X[k].second - b.X[j].second) + b.X[j].first) {
                    flag = !flag;
                }
            }
            if (flag) return false;
        }
        return true;
    }
};

int main() {
    setlocale(0, "");
    int n = 0, m = 1;
    char ch = 0;
    cout << "Введите количесвто углов у многоугольников (от 4 углов) >> ";
    cin >> n;
    if (n < 4) { cout << "Некорректного введеные данные "; return 0; }
    ADT::Type a(n), b(n);
    system("cls");
    while (ch != 27) {
        cout << "Текущие значения в АТД:\n\n";
        ADT::output(a, n);
        ADT::output(b, n);  
        cout << "\nВыберете действие:\n1. Задать значения с клавиатуры\n2. Вывести площадь многоугольников\n3. Проверить вложенность многоугольников\n4. Рандомное заполнение\n";
        ch = _getch();
        system("cls");
        if (ch == '1') {
            system("cls");
            ADT::input(a, n, m);
            m++;
            ADT::input(b, n, m);
            system("cls");
        }
        else if (ch == '2') {
            system("cls");
            cout << "Площать первого многоугольника = " << ADT::Gaus(a) << "\nПлощадь второго многоугольника = " << ADT::Gaus(b) << "\n\n";
            system("pause");
            system("cls");
        }
        else if (ch == '3') {
            system("cls");
            if (ADT::is_inside(a, b))
                cout << "Ни один из многоугольников не вложен\n\n";
            else
                cout << "Один из многоугольников вложен\n\n";
            system("pause");
            system("cls");
        }
        else if (ch == '4')
            ADT::randominput(a, b);
    }
    cout << "Выход ";
}
