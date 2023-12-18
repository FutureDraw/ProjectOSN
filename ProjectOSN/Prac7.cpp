#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <queue>
#include <conio.h>
#include <Windows.h>

using namespace std;

string compressRLE(const string& input) {
    string compressed;
    for (size_t i = 0; i < input.length(); i++) {
        char currentChar = input[i];
        int count = 1;
        while (i < input.length() - 1 && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        compressed += to_string(count) + currentChar;
    }
    return compressed;
}

string compressLZ77(const string& input) {
    string compressed;
    size_t inputSize = input.size();
    for (size_t i = 0; i < inputSize; i++) {
        size_t matchLength = 0;
        size_t matchPosition = 0;
        for (size_t j = 0; j < i; j++) {
            size_t k = 0;
            while (i + k < inputSize && input[j + k] == input[i + k]) k++;
            if (k > matchLength) {
                matchLength = k;
                matchPosition = j;
            }
        }
        if (matchLength > 0) {
            compressed += "<" + to_string(i - matchPosition) + "," + to_string(matchLength) + ">";
            i += matchLength - 1;
        }
        else compressed += input[i];
    }
    return compressed;
}

string compressLZ78(const string& input) {
    string compressed;
    size_t inputSize = input.size();
    vector<pair<string, char>> dictionary;
    for (size_t i = 0; i < inputSize; i++) {
        string currentSubstring(1, input[i]);
        size_t j = i + 1;
        while (j < inputSize && find(dictionary.begin(), dictionary.end(), make_pair(currentSubstring, input[j])) != dictionary.end()) {
            currentSubstring += input[j];
            j++;
        }
        if (j < inputSize) {
            dictionary.push_back(make_pair(currentSubstring, input[j]));
            compressed += "<" + to_string(dictionary.size() - 1) + "," + input[j] + ">";
            i = j;
        }
        else {
            compressed += "<" + to_string(dictionary.size() - 1) + ">";
            break;
        }
    }
    return compressed;
}

struct Node {
    char symbol;
    int frequency;
    Node* left;
    Node* right;
    Node(char sym, int freq) : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}
    void postorder(int indent, const vector<pair<char, string>>& shannonFanoCodes) {
        if (right) right->postorder(indent + 4, shannonFanoCodes);
        if (indent) cout << setw(indent) << ' ';
        if (right) cout << "/\n" << setw(indent) << ' ';
        if (symbol != '\0') {
            auto it = find_if(shannonFanoCodes.begin(), shannonFanoCodes.end(), [this](const pair<char, string>& p) {
                return p.first == symbol;
                });
            if (it != shannonFanoCodes.end())
                cout << symbol << "(" << it->second << ")\n";
        }
        else cout << "1\n" << setw(indent) << ' ' << "0\n";
        if (left) {
            cout << setw(indent) << ' ' << " \\\n";
            left->postorder(indent + 4, shannonFanoCodes);
        }
    }
};

void postorder(Node* p, int indent, const vector<pair<char, string>>& shannonFanoCodes) {
    if (p == nullptr) return;
    p->postorder(indent, shannonFanoCodes);
}

bool sortByFrequency(const Node* a, const Node* b) {
    return a->frequency > b->frequency;
}

Node* buildShannonFanoTree(vector<Node*>& nodes, int start, int end) {
    if (start == end)
        return nodes[start];
    int totalFrequency = 0;
    for (int i = start; i <= end; i++)
        totalFrequency += nodes[i]->frequency;
    if (totalFrequency == 0)
        return nullptr;
    int currentSum = 0;
    int splitIndex = start;
    while (currentSum + nodes[splitIndex]->frequency * 2 < totalFrequency) {
        currentSum += nodes[splitIndex]->frequency;
        ++splitIndex;
    }
    Node* root = new Node('\0', totalFrequency);
    root->left = buildShannonFanoTree(nodes, start, splitIndex);
    root->right = buildShannonFanoTree(nodes, splitIndex + 1, end);
    return root;
}

void generateCodes(Node* root, string currentCode, vector<pair<char, string>>& codes) {
    if (root->left == nullptr && root->right == nullptr) {
        codes.push_back(make_pair(root->symbol, currentCode));
        return;
    }
    generateCodes(root->left, currentCode + "0", codes);
    generateCodes(root->right, currentCode + "1", codes);
}

string compressText(const string& text, const vector<pair<char, string>>& codes) {
    string compressedText;
    for (char c : text) {
        auto it = find_if(codes.begin(), codes.end(), [c](const pair<char, string>& p) {
            return p.first == c;
            });
        if (it != codes.end())
            compressedText += it->second;
    }
    return compressedText;
}

string decompressText(const string& compressedText, const Node* root) {
    string decompressedText;
    const Node* currentNode = root;
    for (char bit : compressedText) {
        if (bit == '0' && currentNode->left != nullptr)
            currentNode = currentNode->left;
        else if (bit == '1' && currentNode->right != nullptr)
            currentNode = currentNode->right;
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            decompressedText += currentNode->symbol;
            currentNode = root;
        }
    }
    return decompressedText;
}

struct HuffmanNode {
    char symbol;
    double probability;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char s, double p) : symbol(s), probability(p), left(nullptr), right(nullptr) {}
    HuffmanNode(double p) : symbol('\0'), probability(p), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) const {
        return a->probability > b->probability;
    }
};

void buildHuffmanTree(HuffmanNode*& root, priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes>& minHeap) {
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();
        HuffmanNode* internalNode = new HuffmanNode(left->probability + right->probability);
        internalNode->left = left;
        internalNode->right = right;
        minHeap.push(internalNode);
    }
    root = minHeap.top();
}

void generateHuffmanCodes(HuffmanNode* root, unordered_map<char, string>& codes, string currentCode = "") {
    if (root == nullptr)
        return;
    if (root->symbol != '\0')
        codes[root->symbol] = currentCode;
    generateHuffmanCodes(root->left, codes, currentCode + '0');
    generateHuffmanCodes(root->right, codes, currentCode + '1');
}

void postorder(HuffmanNode* p, int indent, const unordered_map<char, string>& huffmanCode) {
    if (p == nullptr) return;
    if (p->right) postorder(p->right, indent + 4, huffmanCode);
    if (indent) cout << setw(indent) << ' ';
    if (p->right) cout << "/\n" << setw(indent) << ' ';
    if (p->symbol != '\0')
        cout << p->symbol << "(" << huffmanCode.at(p->symbol) << ")\n";
    else
        cout << "1\n" << setw(indent) << ' ' << "0\n";
    if (p->left) {
        cout << setw(indent) << ' ' << " \\\n";
        postorder(p->left, indent + 4, huffmanCode);
    }
}

void writeCompressedTextToFile(const string& compressedText, const string& fileName) {
    ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        for (char bit : compressedText) {
            if (bit == '0') 
                outputFile << 'A';
            else if (bit == '1')
                outputFile << 'B';
        }
        outputFile.close();
    }
    else 
        cout << "Невозможно открыть файл для записи" << endl;
}

string decodeHuffmanText(const string& compressedText, const HuffmanNode* root) {
    string decodedText;
    const HuffmanNode* currentNode = root;
    for (char bit : compressedText) {
        if (bit == '0' && currentNode->left != nullptr)
            currentNode = currentNode->left;
        else if (bit == '1' && currentNode->right != nullptr)
            currentNode = currentNode->right;
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            decodedText += currentNode->symbol;
            currentNode = root;
        }
    }

    return decodedText;
}

void writeHuffmanDecodedTextToFile(const string& decodedText, const string& fileName) {
    ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        outputFile << decodedText;
        outputFile.close();
    }
    else
        cout << "Невозможно открыть файл для записи" << endl;
}

void writeHuffmanEncodedTextToFile(const string& inputText, const unordered_map<char, string>& huffmanCodes, const string& fileName) {
    ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        for (char c : inputText) {
            auto it = huffmanCodes.find(c);
            if (it != huffmanCodes.end())
                outputFile << it->second;
        }
        outputFile.close();
    }
    else
        cout << "Невозможно открыть файл для записи" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char ch = 0;
    string inputText;
    vector<Node*> nodes;
    string compressedText;
    string compressedLZ;
    double compressionRatio;
    string compressedShannonFano;
    string decompressedShannonFano;
    double compressedBits;
    double originalBits;
    double averageCodeLength = 0;
    double variance = 0;
    HuffmanNode* huffmanRoot = nullptr;
    unordered_map<char, string> huffmanCodes;
    unordered_map<char, double> frequencies;
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;
    vector<pair<char, string>> codes;
    string decompressedText;
    Node* root;
    while (ch != 27) {
        system("cls");
        cout << "Выберите действие:\n";
        cout << "1. Сжатие RLE\n";
        cout << "2. Сжатие LZ77\n";
        cout << "3. Сжатие LZ78\n";
        cout << "4. Сжатие Шеннона-Фано\n";
        cout << "5. Сжатие Хаффмана (ФИО)\n";
        cout << "6. Сжатие Хаффмана (Большой текст)\n\n";
        ch = _getch();
        switch (ch)
        {
        default:
            break;
        case '1':
            inputText = "AAAABBBCCDAA";
            compressedText = compressRLE(inputText);
            cout << "Исходная строка: " << inputText << "\nСжатый текст: " << compressedText << endl;
            compressionRatio = static_cast<double>(inputText.length()) / compressedText.length();
            cout << "Коэффициент сжатия: " << compressionRatio << endl;
            _getch();
            break;
        case '2':
            inputText = "0001010010101001101";
            compressedLZ = compressLZ77(inputText);
            cout << "Исходная строка: " << inputText << "\nLZ77: " << compressedLZ << endl;
            compressionRatio = static_cast<double>(inputText.length()) / compressedLZ.length();
            cout << "Коэффициент сжатия LZ77: " << compressionRatio << endl;
            _getch();
            break;
        case '3':
            inputText = "кукуркукурекурекун";
            compressedLZ = compressLZ78(inputText);
            cout << "Исходная строка: " << inputText << "\nLZ78: " << compressedLZ << endl;
            compressionRatio = static_cast<double>(inputText.length()) / compressedLZ.length();
            cout << "Коэффициент сжатия LZ77: " << compressionRatio << endl;
            _getch();
            break;
        case '4':
            nodes.clear();
            codes.clear();
            inputText = "Ана, дэус, рики, паки, Дормы кормы констунтаки, Дэус дэус канадэус – бац!";
            //cin >> inputText;
            for (char c : inputText) {
                auto it = find_if(nodes.begin(), nodes.end(), [c](const Node* n) {
                    return n->symbol == c;
                    });
                if (it != nodes.end())
                    (*it)->frequency++;
                else
                    nodes.push_back(new Node(c, 1));
            }
            sort(nodes.begin(), nodes.end(), sortByFrequency);
            root = buildShannonFanoTree(nodes, 0, nodes.size() - 1);
            generateCodes(root, "", codes);
            cout << "Таблица кодов Шеннона-Фано:\n";
            for (const auto& code : codes)
                cout << code.first << ": " << code.second << "\n";
            cout << "\nДерево префиксов Шеннона-Фано:\n";
            postorder(root, 0, codes);
            compressedText = compressText(inputText, codes);
            cout << "Сжатый текст:\n" << compressedText << "\n";
            writeCompressedTextToFile(compressedText, "compressed_text.txt");
            originalBits = inputText.length() * 8.0;
            compressedBits = compressedText.length();
            compressionRatio = originalBits / compressedBits;
            cout << "\nКоэффициент сжатия Шеннона-Фано: " << compressionRatio << "\n";
            decompressedText = decompressText(compressedText, root);
            cout << "\nВосстановленный текст:\n" << decompressedText << "\n";
            for (Node* node : nodes)
                delete node;
            _getch();
            break;
        case '5':
            inputText = "Авдеев Александр Юрьевич";
            //cin >> inputText;
            for (char c : inputText)
                frequencies[c]++;
            for (const auto& pair : frequencies)
                minHeap.push(new HuffmanNode(pair.first, pair.second / inputText.size()));
            buildHuffmanTree(huffmanRoot, minHeap);
            generateHuffmanCodes(huffmanRoot, huffmanCodes);
            cout << "Дерево префиксов Хаффмана:" << endl;
            postorder(huffmanRoot, 0, huffmanCodes);
            cout << "\nСимвол\tВероятность\t        Код\n";
            for (const auto& pair : huffmanCodes)
                cout << pair.first << "\t" << frequencies[pair.first] / inputText.size() << "\t\t" << pair.second << "\n";
            originalBits = inputText.length() * 8.0;
            compressedBits = 0;
            for (const auto& pair : huffmanCodes)
                compressedBits += frequencies[pair.first] * pair.second.length();
            compressionRatio = originalBits / compressedBits;
            cout << "\nКоэффициент сжатия Хаффмана: " << compressionRatio << "\n";
            for (const auto& pair : huffmanCodes)
                averageCodeLength += frequencies[pair.first] * pair.second.length() / inputText.size();
            cout << "Средняя длина кода: " << averageCodeLength;
            for (const auto& pair : huffmanCodes)
                variance += frequencies[pair.first] * pow(pair.second.length() - averageCodeLength, 2) / inputText.size();
            cout << "\nДисперсия длины кода: " << variance;
            writeHuffmanEncodedTextToFile(inputText, huffmanCodes, "encoded_text1.txt");
            _getch();
            break;
        case '6':
            ifstream inputFile("input.txt");
            if (!inputFile.is_open()) {
                cout << "Невозможно открыть файл для чтения" << endl;
                _getch();
                break;
            }
            string inputText((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
            inputFile.close();
            unordered_map<char, double> frequencies;
            priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;
            HuffmanNode* huffmanRoot = nullptr;
            unordered_map<char, string> huffmanCodes;
            for (char c : inputText)
                frequencies[c]++;
            for (const auto& pair : frequencies)
                minHeap.push(new HuffmanNode(pair.first, pair.second / inputText.size()));
            buildHuffmanTree(huffmanRoot, minHeap);
            generateHuffmanCodes(huffmanRoot, huffmanCodes);
            cout << "Дерево префиксов Хаффмана:" << endl;
            postorder(huffmanRoot, 0, huffmanCodes);
            cout << "\nСимвол\tВероятность\t        Код\n";
            for (const auto& pair : huffmanCodes)
                cout << pair.first << "\t" << frequencies[pair.first] / inputText.size() << "\t\t" << pair.second << "\n";
            double originalBits = inputText.length() * 8.0;
            double compressedBits = 0;
            for (const auto& pair : huffmanCodes)
                compressedBits += frequencies[pair.first] * pair.second.length();
            double compressionRatio = originalBits / compressedBits;
            cout << "\nКоэффициент сжатия Хаффмана: " << compressionRatio << "\n";
            double averageCodeLength = 0;
            for (const auto& pair : huffmanCodes)
                averageCodeLength += frequencies[pair.first] * pair.second.length() / inputText.size();
            cout << "Средняя длина кода: " << averageCodeLength;
            double variance = 0;
            for (const auto& pair : huffmanCodes)
                variance += frequencies[pair.first] * pow(pair.second.length() - averageCodeLength, 2) / inputText.size();
            cout << "\nДисперсия длины кода: " << variance;
            writeHuffmanEncodedTextToFile(inputText, huffmanCodes, "encoded_text2.txt");
            ifstream encodedFile("encoded_text2.txt");
            if (!encodedFile.is_open()) {
                cout << "Невозможно открыть закодированный файл для чтения" << endl;
                _getch();
                break;
            }
            string compressedText((istreambuf_iterator<char>(encodedFile)), (istreambuf_iterator<char>()));
            encodedFile.close();
            string decodedText = decodeHuffmanText(compressedText, huffmanRoot);
            writeHuffmanDecodedTextToFile(decodedText, "decoded_text2.txt");
            _getch();
            break;
        }
    }
    return 0;
}