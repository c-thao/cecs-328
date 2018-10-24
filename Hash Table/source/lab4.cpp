// Chou Thao
// 012647516
// CECS 328
// Lab 4
// April 13, 2016

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include "RedBlackTreeMap.h"

using namespace std;

int main() {
	RedBlackTreeMap<string, int> tree;

	// opens a file to read
	ifstream in("players_homeruns.csv", ios::in);
	string userInput, line;
	
	while(getline(in, line)) {
		stringstream lineStream(line);
		string name, homeruns;
		getline(lineStream, name, ',');
		getline(lineStream, homeruns, ',');
		int hRuns = stoi(homeruns, nullptr, 10);
		tree.insert(name, hRuns);
	}

	tree.printStructure();

	cout << "\nfound Stan Musial, the value " << tree.find("Stan Musial");
	cout << "\nfound Honus Wagner the value " << tree.find("Honus Wagner");
	cout << "\nfound Rogers Hornsby the value " << tree.find("Rogers Hornsby");
	cout << "\nfound Ted Williams the value " << tree.find("Ted Williams");

	return 0;
}
