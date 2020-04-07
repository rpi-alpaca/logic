#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <string>
using namespace std;

//StatementNode = Nodes In Expression Tree For Logical Expresssions.
class StatementNode {
public:
	StatementNode() : left(nullptr), right(nullptr) {}
	//Left + Right Children Values:
	StatementNode* left;
	StatementNode* right;
	std::string value;
	char connector;
	//Default Value = False.
	bool negation = false;
	//Operator Value.
	char opType;
};

class StatementParser {
public: 
	StatementParser();
	StatementParser(const StatementParser& s);
	//Combine Two Statements w/ Connector.
	StatementParser(const StatementParser& s1, const StatementParser& s2);
	StatementParser(const std::string& statement);
	void changeHeadValue(const std::string& statement);
	void print() const;
	void print(std::ostream& o) const;
	void printNode(StatementNode* s, std::ostream& o) const;
	void printTree() const;
	void printTreeHelper(StatementNode* s, int depth) const;

private:
	StatementNode* copy_statement(StatementNode* old_node);
	void parseStatement(StatementNode*& n, const std::string& statement);
	StatementNode* head;
	friend class StatementEvaluator;
};

#endif
