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

using namespace std;

class Node {
public:
	string ID;
	string elevation;
	bool visited; //this is for the BFS compressable functionality to know whether or not it has been visited yet

	//unordered_sets are used for parents and children so that access, search, and delete functionality are all in O(1) complexity for average case (implemented through hash table)
	unordered_set<Node*> parents;
	unordered_set<Node*> children;
	vector<string> collapsed;

	Node();
	Node(string ID);
	Node(string ID, string elevation);
	void operator=(const Node* TN);


};

