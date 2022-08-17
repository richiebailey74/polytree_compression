#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <cstring>
#include <limits>
#include <set>
#include <unordered_set>
#include <fstream>

#include "Poly.h"
#include "Node.h"

using namespace std;


int main() {

	//will store all input lines in a vector to pass to the Poly constructor which will parse it and build the tree
	vector<string> inputLines;
	/*
	//get all input lines
	while (true) {

		string inputLine;
		std::cout << "Input valid string line or enter # to finish: \n";
		cin >> inputLine;

		//if the input line is a #, the input is done and break out of the loop and continue the program
		if (inputLine == "#") {
			break;
		}

		inputLines.push_back(inputLine);
	}
	*/


	//FIX THIS FILE READING ****** FIGURE IT OUT  (reference programming 2 labs on file IO to see how to properly do it)
	string fileName = "samll_input.txt";

	ifstream theFile;

	theFile.open(fileName);

	string currentLine;

	while (getline(theFile, currentLine)) {
		cout << currentLine << "/n";
		inputLines.push_back(currentLine);
	}

	theFile.close();

	for (int i = 0; i < inputLines.size(); i++) {
		cout << inputLines[i] << "\n";
	}


	//pass vector of strings into  Poly constructor to get poly tree of nodes
	//Poly* TREE = new Poly(inputLines);

	//cout << "Output before collapsing\n\n\n";
	//TREE->printBFS();

	//TREE->collapseBFS();

	//cout << "Output after collapsing\n";
	//TREE->printBFS();


	return 0;
}