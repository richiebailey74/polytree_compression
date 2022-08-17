#include "Node.h"

Node::Node() {
	this->ID = "";
	this->elevation = "";
	this->visited = false;
}

Node::Node(string ID) {
	this->ID = ID;
	this->elevation = "";
	this->visited = false;
}

Node::Node(string ID, string elevation) {
	this->ID = ID;
	this->elevation = elevation;
	this->visited = false;
}

void Node::operator=(const Node* TN) {
	this->ID = TN->ID;
	this->elevation = TN->elevation;
	this->parents = TN->parents;
	this->children = TN->children;
	this->collapsed = TN->collapsed;
}