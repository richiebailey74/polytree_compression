#include "Poly.h"


Poly::Poly() {
	this->root = nullptr;
}

Poly::Poly(vector<string> inputLines) {
	this->root = nullptr;
	unordered_map<string, Node*> existingTreeNodes;


	//parse all input lines and construct poly tree
	for (unsigned int i = 0; i < inputLines.size(); i++) {

		//parse each line
		string keyVal = "";
		string elevation = "";
		vector<string> parents;
		vector<string> children;

		int index = 0;

		//get the ID value
		while (inputLines[i][index] != ',') {
			keyVal += inputLines[i][index];
			index++;
		}

		index++; //consume the comma

		//get the elevation value
		while (inputLines[i][index] != ':') {
			elevation += inputLines[i][index];
			index++;
		}

		index++; //consume the colon



		while (inputLines[i][index] != ';') {
			//we will assume input will be valid and there won't be any misplaced commas
			string tempString = "";
			while (inputLines[i][index] != ',' && inputLines[i][index] != ';') {
				tempString += inputLines[i][index];
				index++;
			}
			if (inputLines[i][index] == ',') {
				index++; // consume the comma
			}
			parents.push_back(tempString);
		}

		index++; //consume the semicolon

		//must continuously check if index is out of bounds or else it might throw an error
		while (index != inputLines[i].size()) {

			string tempString = "";
			while (inputLines[i][index] != ',' && index != inputLines[i].size()) {
				tempString += inputLines[i][index];
				index++;
			}
			children.push_back(tempString);
			if (inputLines[i][index] == ',') {
				index++; //consume comma if there is a comma (otherwise it is the end of the string)
			}

		}


		//have all parents, children, ID, and elevation all stored as strings
		//now must properly create Node*

		Node* tempToAdd;

		//depending on if the node already exists will determine how the pointer is assigned, create new one if it doesn't exist and extract from map if it does exist (map tracks existing Node*)
		if (existingTreeNodes.find(keyVal) == existingTreeNodes.end()) { //treenode for an ID doesn't exist

			//create and add new Node* to map
			tempToAdd = new Node(keyVal, elevation);
			existingTreeNodes[keyVal] = tempToAdd;

			if (root == nullptr) {//ASSIGN ROOT IF THERE ISN"T ONE (access to the entire tree)
				assignRoot(tempToAdd);
			}

		}
		else { //treenode for an ID already exists

			tempToAdd = existingTreeNodes[keyVal]; //extract the pointer since it already exists
			tempToAdd->elevation = elevation; //since when it was created, an elevation wasn't added to it
		}

		//add parents and children, see if they exist first to avoid duplicating
		for (unsigned int i = 0; i < parents.size(); i++) {//adding all parents
			
			if (existingTreeNodes.find(parents[i]) != existingTreeNodes.end()) {
				
				tempToAdd->parents.insert(existingTreeNodes[parents[i]]); //since the node already exists, find it in the map and pushback that node pointer
				
			}
			else { //if the parent to add to the node to add doesn't exist yet, create it and add it to the map
				
				Node* tempParent = new Node(parents[i]);
				existingTreeNodes[parents[i]] = tempParent;
				tempToAdd->parents.insert(tempParent);
				
			}

		}
		for (unsigned int i = 0; i < children.size(); i++) { //adding all children
			
			if (existingTreeNodes.find(children[i]) != existingTreeNodes.end()) {
				
				tempToAdd->children.insert(existingTreeNodes[children[i]]); //since the node already exists, find it in the map and pushback that node pointer
				
			}
			else { //if the child to add to the node to add doesn't exist yet, create it and add it to the map

				Node* tempChild = new Node(children[i]);
				existingTreeNodes[children[i]] = tempChild;
				tempToAdd->children.insert(tempChild);
				
			}

		}

		
		tempToAdd->collapsed.push_back(keyVal);
		
	}
}

void Poly::assignRoot(Node* rootToAssign) {
	this->root = rootToAssign;
}

//helper function for the BFS compression by collapsing one node into another node and making sure all the Node* references are updated correctly
void Poly::collapseNodes(Node* remain, Node* collapses, bool PorC) {

	//push back the collapsing node ID into the vector that tracks the nodes collapsed into this particular node
	remain->collapsed.push_back(collapses->ID);
	
	//itera needs to restart to its respective .begin() that way the collaspeBFS can add the additional kids/parents that may have been added to the list

	//checks to see if the collapsing node is in the remaining nodes parents (true pased) or children (false passed)

	//each if statement has two loops that essentially have the same goals:
		//erase the collapsing node from all references in its children and parents
		//replace where it was erased with the remaining node it is being collapsed into
		//add all collapsing nodes parents and children to the remaining node
		//now, effectively, the Node* has been compressed
	if (PorC) {

		for (auto it = collapses->parents.begin(); it != collapses->parents.end(); it++) {
			(*it)->children.erase((*it)->children.find(collapses));
			(*it)->children.insert(remain);
			remain->parents.insert((*it));
		}
		for (auto it = collapses->children.begin(); it != collapses->children.end(); it++) {
			if ((*it) != remain) {
				(*it)->parents.erase((*it)->parents.find(collapses));
				(*it)->parents.insert(remain);
				remain->children.insert((*it));
			}
		}

		remain->parents.erase(remain->parents.find(collapses));
	}
	else {

		for (auto it = collapses->children.begin(); it != collapses->children.end(); it++) {
			(*it)->parents.erase((*it)->parents.find(collapses));
			(*it)->parents.insert(remain);
			remain->children.insert((*it));
		}
		for (auto it = collapses->parents.begin(); it != collapses->parents.end(); it++) {
			if ((*it) != remain) {
				(*it)->children.erase((*it)->children.find(collapses));
				(*it)->children.insert(remain);
				remain->parents.insert((*it));
			}
		}

		remain->children.erase(remain->children.find(collapses));
	}


}

//collapses the poly tree using a breadth first traversal to complete in O(n)
void Poly::collapseBFS() {

	//queue to keep BFS in the correct order and so the BFS works properly
	list<Node*> queue;

	queue.push_back(this->root);

	//once queue is empty, the BFS is done
	while (!queue.empty()) {

		Node* cur = queue.front();
		queue.pop_front();

		//if it has already been visited, then continue onto the next loop iteration and thus the next Node* in the queue
		if (cur->visited == true) {
			continue;
		}

		//mark as visited
		cur->visited = true;

		//matchRerun functionality is for when we are mid compression and items are added to the parents in the children loop, and thus unreachable so it must go from beginning to be thorough
		bool matchRerun = true;
		while (matchRerun) {
			matchRerun = false;

			//parents
			for (auto it = cur->parents.begin(); it != cur->parents.end(); it++) {

				if ((*it)->visited == true) {
					continue;
				}

				if (cur->elevation == (*it)->elevation) {
					//if there's a match compress the tree
					//the compressed node shouldn't be visited again to avoid redundancy, so mark visited as true
					(*it)->visited = true;
					collapseNodes(cur, (*it), true);
					it = cur->parents.begin();
					matchRerun = true;
				}
				else {
					//no match, then don't compress and add to queue
					if ((*it)->visited != true) {
						queue.push_back((*it));
					}
				}
				//to prevent pointer errors by iterating a .end() iterator
				if (it == cur->parents.end()) {
					break;
				}
			}

			//children
			for (auto it = cur->children.begin(); it != cur->children.end(); it++) {

				if ((*it)->visited == true) {
					continue;
				}

				if (cur->elevation == (*it)->elevation) {
					//if there's a match compress the tree
					//the compressed node shouldn't be visited again to avoid redundancy, so mark visited as true
					(*it)->visited = true;
					collapseNodes(cur, (*it), false);
					it = cur->children.begin();
					matchRerun = true;
				}
				else {
					//no match, then don't compress and add to queue
					if ((*it)->visited != true) {
						queue.push_back((*it));
					}

				}
				//to prevent pointer errors by iterating a .end() iterator
				if (it == cur->children.end()) {
					break;
				}
			}
		}
		

		

	}

}

//Prints the elements in the poly tree through a breadth first traversal
void Poly::printBFS() {
	//this set tracks the Nodes already printed so there aren't repeats
	unordered_set<Node*> alreadyPrinted;

	list<Node*> queue;

	queue.push_back(this->root);

	while (!queue.empty()) {

		Node* cur = queue.front();
		queue.pop_front();

		//checks to see if the current Node* has been printed/visited and if it has then continue onto the next loop
		if (alreadyPrinted.find(cur) != alreadyPrinted.end()) {
			continue;
		}

		//following two loops exist to add elements to the queue
		//children
		for (auto it = cur->children.begin(); it != cur->children.end(); it++) {

			if (alreadyPrinted.find(cur) == alreadyPrinted.end()) {
				queue.push_back((*it));
			}

		}
		//parents
		for (auto it = cur->parents.begin(); it != cur->parents.end(); it++) {

			if (alreadyPrinted.find(cur) == alreadyPrinted.end()) {
				queue.push_back((*it));
			}

		}

		//store the current Node* in the set to show that it has been visited
		alreadyPrinted.insert(cur);

		//actually print everything with respect to the correct format
		cout << cur->ID;

		cout << ":";

		cout << cur->elevation;

		cout << ":";

		for (auto it = cur->parents.begin(); it != cur->parents.end(); it++) {

			cout << (*it)->ID;

			if (it != prev(cur->parents.end())) {
				cout << ",";
			}


		}

		cout << ";";

		for (auto it = cur->children.begin(); it != cur->children.end(); it++) {

			cout << (*it)->ID;

			if (it != prev(cur->children.end())) {
				cout << ",";
			}
		}

		cout << ":";

		for (unsigned int j = 0; j < cur->collapsed.size(); j++) {
			cout << cur->collapsed[j];

			if (j != cur->collapsed.size() - 1) {
				cout << ",";
			}

		}

		cout << "\n";



	}

}
