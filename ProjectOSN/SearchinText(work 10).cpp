#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <unordered_map>
#include<chrono>

using namespace std;
chrono::time_point<chrono::steady_clock> start, end_time;
double cpu_ms = 0;
int ci = 0, N;

string X;

void input() {
    cout << "Введите предложение >> ";
    getline(cin, X);
}

int boyerMooreSearch(string X, string substring) {
    ci = 0;
    start = chrono::steady_clock::now();
    unordered_map<char, int> shifts;
    for (int i = 0; i < substring.size() - 1; i++) {
        shifts[substring[i]] = substring.size() - i - 1;
    }
    int i = substring.size() - 1;
    while (i < X.size()) {
        int j = substring.size() - 1;
        while (j >= 0 && X[i] == substring[j]) {
            i--; j--;
        }
        ci++;
        if (j < 0) {
            end_time = chrono::steady_clock::now();
            cpu_ms = chrono::duration<double, milli>(end_time - start).count();
            return i + 1;
        }
        else {
            i += max(shifts[X[i]], substring.size() - j);
        }
    }
    end_time = chrono::steady_clock::now();
    cpu_ms = chrono::duration<double, milli>(end_time - start).count();
    return -1;
}

void switcher() {
    ci = 0;
    start = chrono::steady_clock::now();
    string pattern = "ru";
    string replacement = "рус";
    unordered_map<char, int> shifts;
    for (int i = 0; i < pattern.size() - 1; i++) {
        shifts[pattern[i]] = pattern.size() - i - 1;
    }
    int i = pattern.size() - 1;
    while (i < X.size()) {
        int j = pattern.size() - 1;
        while (j >= 0 && X[i] == pattern[j]) {
            i--; j--;
        }
        ci++;
        if (j < 0) {
            X.replace(i + 1, pattern.size(), replacement);
            i += pattern.size();
        }
        else {
            i += max(shifts[X[i]], pattern.size() - j);
        }
    }
    end_time = chrono::steady_clock::now();
    cpu_ms = chrono::duration<double, milli>(end_time - start).count();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string substring;
    input();
    cout << "Введите подстроку >> ";
    getline(cin, substring);
    int position = boyerMooreSearch(X, substring);
    if (position != -1) {
        cout << "Подстрока найдена на позиции: " << position;
        cout << "\nВремя: " << cpu_ms << "ms" << "\nСравнений: " << ci;
    }
    else
        cout << "Подстрока не найдена.";
    switcher();
    cout << "\n" << X;
    cout << "\nВремя: " << cpu_ms << "ms" << "\nСравнений: " << ci;
    return 0;
}