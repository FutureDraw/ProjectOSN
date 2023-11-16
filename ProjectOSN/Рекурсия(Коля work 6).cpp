#include <iostream>
#include <string>

using namespace std;

bool checkBalance(string expr, int index = 0, int count = 0) {
    if (index == expr.length()) {
        return (count == 0);
    }
    else {
        if (expr[index] == '(') {
            return checkBalance(expr, index + 1, count + 1);
        }
        else if (expr[index] == ')') {
            if (count == 0) {
                return false;
            }
            else {
                return checkBalance(expr, index + 1, count - 1);
            }
        }
        else {
            return checkBalance(expr, index + 1, count);
        }
    }
}

int main() {
    setlocale(0, "");
    string s;
    cout << "Введите арифметическое выражение >> ";
    getline(cin, s);
    if (checkBalance(s)) {
        cout << "Скобки в выражении сбалансированы.\n";
    }
    else {
        cout << "Скобки в выражении НЕ сбалансированы.\n";
    }
    return 0;
}
