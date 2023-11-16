#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

struct Document {
private:
	pair<vector<string>, vector<vector<string>>> Data;

	void check_num() {
		if (Data.first.size() != 4)
			Data.first.resize(4);
		Data.first[3] = to_string(Data.second.size());
	}

public:
	Document() {
		string a, b, c;
		cout << "Введите номер института: ";
		cin >> a;
		cout << "Введите номер дисциплины: ";
		cin >> b;
		cout << "ФИО преподавателя: ";
		cin >> c;

		Data.first.push_back(a);
		Data.first.push_back(b);
		Data.first.push_back(c);
	}
	Document(string num_inst, string num_dic, string name) {
		Data.first.push_back(num_inst);
		Data.first.push_back(num_dic);
		Data.first.push_back(name);
	}

	bool add_score(string num_k, int score) {
		for (size_t i = 0; i < Data.second.size(); i++) {
			if (num_k == Data.second[i][1]) {
				Data.second[i][3] = to_string(score); return true;
			}
		}
		return false;
	}

	int students(bool exist = false) {
		int num = 0;
		for (size_t i = 0; i < Data.second.size(); i++) {
			if ((Data.second[i][3] == "1" && exist == false) || (Data.second[i][3] != "1" && exist == true))
				num++;
		}
		return num;
	}

	void del_bstudent() {
		for (size_t i = 0; i < Data.second.size(); i++) {
			if (Data.second[i][3] == "6")
				Data.second.erase(Data.second.begin() + i--);
		}
	}

	bool add_student(string st_name, string num_k, string date, int score = 1) {
		vector<string> student_info;

		student_info.push_back(st_name);
		student_info.push_back(num_k);
		student_info.push_back(date);
		student_info.push_back(to_string(score));

		int num = stoi(num_k);

		for (size_t i = 0; i < Data.second.size(); i++) {
			if (num < stoi(Data.second[i][1])) {
				Data.second.insert(Data.second.begin() + i, student_info);
				return true;
			}
		}
		Data.second.push_back(student_info);
		return true;
	}

	void output() {
		check_num();
		cout << "---------------------------------------------------------------\n\n";
		for (size_t i = 0; i < Data.first.size(); i++) {
			cout << Data.first[i] << (i < Data.first.size() - 1 ? " | " : "");
		}

		cout << "\n";

		for (size_t i = 0; i < Data.second.size(); i++) {
			cout << "\n---------------------------------------------------------------\n";
			for (size_t j = 0; j < Data.second[i].size(); j++) {
				cout << Data.second[i][j] << (j < Data.first.size() - 1 ? " | " : "");
			}
		}
		cout << "\n---------------------------------------------------------------\n";

	}
};

int main()
{
	setlocale(0, "");
	Document Vedomost("1.1.2", "1414", "Petrov A.I.");
	system("cls");
	char ch = 0;
	while (ch != 27) {
		system("cls");
		cout << "1. Добавить оценку студенту за экзамен"
			<< "\n2. Вставить сведения по студенту за экзамен"
			<< "\n3. Подсчитать количество студентов, не явившихся на экзамен"
			<< "\n4. Удалить сведения о студентах, не допущенных на экзамен";

		cout << "\n\n";
		Vedomost.output();
		string name, num_k, date;
		switch (_getch())
		{
			int score;

		default:
			system("cls");
			cout << "\a";
			break;
		case '1':
			system("cls");
			cout << "Введите номер студенчиского: ";
			cin >> num_k;

			cout << "Введите оценку: ";
			cin >> score;
			Vedomost.add_score(num_k, score);
			break;
		case '2':
			system("cls");
			cout << "Введите имя студента: ";
			cin >> name;
			cout << "Введите номер студенчиского: ";
			cin >> num_k;
			cout << "Введите время сдачи: ";
			cin >> date;
			cout << "Введите оценку: ";
			cin >> score;
			Vedomost.add_student(name, num_k, date, score);
			break;
		case '3':
			system("cls");
			cout << "Студентов не явилось: " << Vedomost.students();
			_getch();
			break;
		case '4':
			system("cls");
			Vedomost.del_bstudent();
			break;
		}
	}
}
