#pragma once

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
#include <algorithm>

#include "Node.h"

using namespace std;

class Poly {
public:
	Node* root;

	Poly();
	Poly(vector<string> inputLines);
	~Poly();

	void assignRoot(Node* rootToAssign);

	//collapse function (BFS)'
	//use visited bool in Node to assist
	void collapseBFS();

	//helper function to collapse one node into another 
	void collapseNodes(Node* remain, Node* collapses, bool PorC); 

	//print functionality for non vector(so BFS traversal print) (use an unordered_map to track visited)
	void printBFS(); 


};

