#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <Windows.h>

using namespace std;

struct Hashtable {
	int key = -1;
	int filepos = -1;
	bool insert = 0;
};
#endif
