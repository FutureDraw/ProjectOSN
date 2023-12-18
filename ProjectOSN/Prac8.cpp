#include <iostream>
#include <vector>

using namespace std;

long long bruteForceCount = 0;
long long DPCount = 0;

bool containsConsecutiveOnes(int sequence, int length) {
    for (int i = 0; i < length - 1; i++) {
        if (((sequence >> i) & 3) == 3)
            return true;
    }
    return false;
}

int countSequencesBruteforce(int n, long long& bruteForceCount) {
    int totalSequences = 0;
    for (int i = 0; i < pow(2, n); i++) {
        if (!containsConsecutiveOnes(i, n)) totalSequences++;
        bruteForceCount++; 
    }
    return totalSequences;
}

int countSequencesDP(int n) {
    vector<vector<int>> DP(n + 1, vector<int>(2, 0));
    DP[1][0] = 1; 
    DP[1][1] = 1; 
    for (int i = 2; i <= n; i++) {
        DP[i][0] = DP[i - 1][0] + DP[i - 1][1];
        DP[i][1] = DP[i - 1][0];
        DPCount++;
    }
    return DP[n][0] + DP[n][1];
}

int main() {
    setlocale(0, "");
    int n;
    cout << "Введите число n >> ";
    cin >> n;

    int resultBruteForce = countSequencesBruteforce(n, bruteForceCount);
    cout << "Число последовательностей (грубая сила): " << resultBruteForce << endl;
    cout << "Количество переборов (грубая сила): " << bruteForceCount << endl;

    int resultDP = countSequencesDP(n);
    cout << "Число последовательностей (динамическое программирование): " << resultDP << endl;
    cout << "Количество переборов (динамическое программирование): " << DPCount << endl;
    return 0;
}
