#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <string>

class FirstOrderNode {
public:
	FirstOrderNode() : left(nullptr), right(nullptr) {}

	FirstOrderNode* left;
	FirstOrderNode* right;
	std::string value;
	char connector;
	bool negation = false;
	char opType;
};

class FirstOrderTree {
public: 
	FirstOrderTree();
	FirstOrderTree(const FirstOrderTree& s);

	//Combine two statements with a connector
	FirstOrderTree(const FirstOrderTree& s1, const FirstOrderTree& s2);
	FirstOrderTree(const std::string& statement);

	void changeHeadValue(const std::string& statement);
	
	void print() const;
	void printNode(FirstOrderNode* s) const;
	void printTree() const;
	void printTreeHelper(FirstOrderNode* s, int depth) const;

private:
	FirstOrderNode* copy_statement(FirstOrderNode* old_node);
	void parseStatement(FirstOrderNode* n, const std::string& statement);
	FirstOrderNode* head;
	friend class StatementEvaluator;
};

#endif
