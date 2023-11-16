#include <iostream>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

int Height(Node* root) {
    if (root == nullptr) return 0;
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);
    return 1 + max(leftHeight, rightHeight);
}

int PathLength(Node* root) {
    if (root == nullptr) return 0;
    return PathLength(root->left) + PathLength(root->right) + 1;
}

Node* insert(Node* root, int value) {
    if (root == nullptr) return new Node(value);
    if (value < root->data) 
        root->left = insert(root->left, value);
    else 
        root->right = insert(root->right, value);
    return root;
}

Node* insertBalanced(Node* root, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    root = insert(root, mid);
    root->left = insertBalanced(root->left, start, mid - 1);
    root->right = insertBalanced(root->right, mid + 1, end);
    return root;
}

void print(Node* root, int indent = 0) {
    if (root != nullptr) {
        print(root->right, indent + 4);
        for (int i = 0; i < indent; i++) 
            cout << " ";
        cout << root->data << "\n";
        print(root->left, indent + 4);
    }
}

double Average(Node* root, int& sum, int& count) {
    if (root == nullptr) return 0.0;
    sum += root->data;
    count++;
    double leftAvg = Average(root->left, sum, count);
    double rightAvg = Average(root->right, sum, count);
    return (leftAvg + rightAvg + root->data);
}

int main() {
    setlocale(0, "");
    Node* root = nullptr;
    int n; 
    cout << "Введите количество узлов >> ";
    cin >> n;
    root = insertBalanced(root, 1, n);
    system("cls");
    print(root);
    int sum = 0, count = 0;
    double average = Average(root, sum, count);
    cout << "\nВысота дерева: " << Height(root) << endl;
    cout << "Длина пути дерева: " << PathLength(root) - 1 << endl;
    cout << "Среднее арифметическое всех чисел в дереве: " << average / count << endl;
    return 0;
}
