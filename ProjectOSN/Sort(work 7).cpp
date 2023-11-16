#include <iostream>
#include <conio.h>
#include <chrono>

using namespace std;
int N = 0;
long long ci = 0, d = 0;

struct Type {
    chrono::time_point<chrono::steady_clock> start, end_time;
    double cpu_ms = 0;
    int* X = new int[N];

    Type() {
        cout << "Выбери способ заполнения массива:\n1. Рандомно\n2. По возрастанию\n3. По убыванию\n";
        char cc = _getch();
        switch (cc)
        {
        default:
            break;
        case '1':
            randominput();
            break;
        case '2':
            increasing();
            break;
        case '3':
            decreasing();
            break;
        }
        system("cls");
    }

    void randominput() {
        srand(time(0));
        for (int i = 0; i < N; i++)
            X[i] = rand() % 101;
    }

    void increasing() {
        for (int i = 0; i < N; i++)
            X[i] = i;
    }

    void decreasing() {
        int startvalue = N-1;
        for (int i = 0; i < N; i++) {
            X[i] = startvalue;
            startvalue--;
        }
    }

    void output() {
        for (int i = 0; i < N; i++) {
            cout << X[i] << " ";
        }
    }

    void sort_pus() {
        start = chrono::steady_clock::now();
        for (int i = 0; i < N - 1; i++) {
            for (int j = 0; j < N - i - 1; j++) {
                ci++;
                if (X[j] > X[j + 1]) {
                    d++;
                    swap(X[j], X[j + 1]);
                }
            }
        }
        end_time = chrono::steady_clock::now();
        cpu_ms = chrono::duration<double, milli>(end_time - start).count();
    }

    void upsort_pus() {
        start = chrono::steady_clock::now();
        for (int i = 0; i < N - 1; i++) {
            for (int j = 0; j < N - i - 1; j++) {
                if (X[j] < X[j + 1]) {
                    swap(X[j], X[j + 1]);
                }
            }
        }
        end_time = chrono::steady_clock::now();
        cpu_ms = chrono::duration<double, milli>(end_time - start).count();
    }

    void shakerSort() {
        start = chrono::steady_clock::now();
        bool swapped = true;
        int stat = 0;
        int end = N - 1;
        while (swapped) {
            swapped = false;
            for (int i = stat; i < end; i++) {
                ci++;
                if (X[i] > X[i + 1]) {
                    d++;
                    swap(X[i], X[i + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
            swapped = false;
            end--;
            for (int i = end - 1; i >= stat; i--) {
                ci++;
                if (X[i] > X[i + 1]) {
                    d++;
                    swap(X[i], X[i + 1]);
                    swapped = true;
                }
            }
            stat++;
        }
        end_time = chrono::steady_clock::now();
        cpu_ms = chrono::duration<double, milli>(end_time - start).count();
    }

    void upshakerSort() {
        start = chrono::steady_clock::now();
        bool swapped = true;
        int stat = 0;
        int end = N - 1;
        while (swapped) {
            swapped = false;
            for (int i = stat; i < end; i++) {
                if (X[i] < X[i + 1]) {
                    swap(X[i], X[i + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
            swapped = false;
            end--;
            for (int i = end - 1; i >= stat; i--) {
                if (X[i] < X[i + 1]) {
                    swap(X[i], X[i + 1]);
                    swapped = true;
                }
            }
            stat++;
        }
        end_time = chrono::steady_clock::now();
        cpu_ms = chrono::duration<double, milli>(end_time - start).count();
    }

    void merge(Type& arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int* L = new int[n1], * R = new int[n2];
        for (int i = 0; i < n1; i++)
            L[i] = arr.X[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr.X[m + 1 + j];
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr.X[k] = L[i];
                i++;
            }
            else {
                arr.X[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            arr.X[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr.X[k] = R[j];
            j++;
            k++;
        }
        delete[] L;
        delete[] R;
    }

    void mergeSort(Type& arr, int l, int r) {
        ci++;
        if (l >= r) {
            d++;
            return;
        }
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }

    void sort_ms() {
        start = chrono::steady_clock::now();
        mergeSort(*this, 0, N - 1);
        end_time = chrono::steady_clock::now();
        cpu_ms = chrono::duration<double, milli>(end_time - start).count();
    }

    void upmerge(Type& arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int* L = new int[n1], * R = new int[n2];
        for (int i = 0; i < n1; i++)
            L[i] = arr.X[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr.X[m + 1 + j];
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] >= R[j]) {
                arr.X[k] = L[i];
                i++;
            }
            else {
                arr.X[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            arr.X[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr.X[k] = R[j];
            j++;
            k++;
        }
        delete[] L;
        delete[] R;
    }

    void upmergeSort(Type& arr, int l, int r) {
        if (l >= r) {
            return;
        }
        int m = l + (r - l) / 2;
        upmergeSort(arr, l, m);
        upmergeSort(arr, m + 1, r);
        upmerge(arr, l, m, r);
    }

    void upsort_ms() {
        start = chrono::steady_clock::now();
        upmergeSort(*this, 0, N - 1);
        end_time = chrono::steady_clock::now();
        cpu_ms = chrono::duration<double, milli>(end_time - start).count();
    }
};

int main() {
    setlocale(0, "");
    cout << "Выбери размер массива:\n1. 100\n2. 1000\n3. 10000\n4. 100000\n5. 1000000\n";
    char c = _getch();
    switch (c)
    {
    default:
        break;
    case '1':
        N = 100;
        break;
    case '2':
        N = 1000;
        break;
    case '3':
        N = 10000;
        break;
    case '4':
        N = 100000;
        break;
    case '5':
        N = 1000000;
        break;
    }
    system("cls");
    Type a;
    a.output();
    cout << "\n1. Сортировка пузырьком по возрастанию\n2. Шейкерная сортировка по возрастанию\n3. Сортировка простым слиянием по возрастанию\n4. Сортировка пузырьком по убыванию\n5. Шейкерная сортировка по убыванию\n6. Сортировка простым слиянием по убыванию\n";
    char ch = _getch();
    switch (ch)
    {
    default:
        break;
    case '1':
        a.sort_pus();
        break;
    case '2':
        a.shakerSort();
        break;
    case '3':
        a.sort_ms();
        break;
    case '4':
        a.upsort_pus();
        break;
    case '5':
        a.upshakerSort();
        break;
    case '6':
        a.upsort_ms();
        break;
    }
    a.output();
    cout << "\nВремя: " << a.cpu_ms << "ms" << "\nПеремещений: " << d << "\nВходов: " << ci;
}
