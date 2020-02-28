#include "FirstOrderTree.h"

FirstOrderTree::FirstOrderTree(){
	head = new FirstOrderNode;
	head->opType = 'v';
}

FirstOrderTree::FirstOrderTree(const FirstOrderTree& s) {
	head = new FirstOrderNode;
	head = copy_statement(s.head);
}

FirstOrderTree::FirstOrderTree(const FirstOrderTree& s1, const FirstOrderTree& s2) {
	head = new FirstOrderNode;
	head->opType = '&';
	head->left = copy_statement(s1.head);
	head->right = copy_statement(s2.head);
}

FirstOrderTree::FirstOrderTree(const std::string& statement){
	//this->head = nullptr;
	//split it up
	head = new FirstOrderNode();
	parseStatement(head, statement);
}

void FirstOrderTree::changeHeadValue(const std::string& statement) {
	head->value = statement;
}

//Prints the tree in order
void FirstOrderTree::print() const {
	printNode(head);
	std::cout << std::endl;
}

//Helper function for print
void FirstOrderTree::printNode(FirstOrderNode* s) const {
	if (s->negation) 
		std::cout << '~';
	if (s->opType == 'v') 
		std::cout << s->value;
	else {
		std::cout << '(';
		printNode(s->left);
		std::cout << " ";
		std::cout << s->opType << " ";
		printNode(s->right);
		std::cout << ")";
	}
}

//Print the tree as its structure
void FirstOrderTree::printTree() const {
	printTreeHelper(head, 0);
}

//Helper function for tree print
void FirstOrderTree::printTreeHelper(FirstOrderNode* s, int depth) const {
	if (!s)
		return;
	printTreeHelper(s->right, depth+1);
	std::cout << std::string(depth, '\t') << (s->negation ? '~' : ' ') << s->opType;
	if (s->opType == 'v')
		std::cout << ": " << (s->negation ? '~' : ' ') << s->value;
	std::cout << std::endl;
	printTreeHelper(s->left, depth+1);
}

//Copy helper function for copying nodes
FirstOrderNode* FirstOrderTree::copy_statement(FirstOrderNode* old_node) {
	if (old_node == nullptr)
		return nullptr;
	FirstOrderNode* new_node = new FirstOrderNode;
	new_node->value = old_node->value;
	new_node->opType = old_node->opType;
	new_node->left = copy_statement(old_node->left);
	new_node->right = copy_statement(old_node->right);
	return new_node;
}

// Recursively parses a statment
// Assumes statement is of format ((A) & (B)) & (~C)
void FirstOrderTree::parseStatement(FirstOrderNode* n, const std::string& statement){
	int parenCount = 0;

	// If there is a negation character, negate the current head node and recurse
	if (statement[0] == '~') {
		n->negation = !(n->negation);
		//If there's no parenthesis after, statement is basic
		if (statement[1] != '(') {
			n->value = statement.substr(1, statement.size()-1);
			n->opType = 'v';
			return;
		}
		//Otherwise, statement is compound
		//Recurse with outer parentheses removed
		parseStatement(n, statement.substr(2, statement.size()-3));
		return;
	}

	//If there's no parenthesis at the start, statement is basic
	if (statement[0] != '(') {
		n->value = statement;
		n->opType = 'v';
		return;
	}

	std::string subStatementL;
	std::string::size_type i;
	// Evaluates the left
	for (i = 0; i < statement.size(); i++) {
		if (statement[i] == '(')
			parenCount++;
		else if (statement[i] == ')')
			parenCount--;
		//parenCount == zero suggests a fully closed statement
		if (parenCount == 0) {
			//subStatementL is the inner statement without parentheses
			subStatementL = statement.substr(1, i-1);
			break;
		}
	}

	//Statement is compound, find the opType
	n->opType = statement[i+2];

	//subStatementR is the inner statement without parentheses after the operation
	std::string subStatementR = statement.substr(i+5, statement.size()-(i+5)-1);

	//Give subStatementL to left node for parsing
	n->left = new FirstOrderNode();

	//Create a node for the right statement
	n->right = new FirstOrderNode();

	parseStatement(n->left, subStatementL);
	parseStatement(n->right, subStatementR);
} 

// std::string conditional(std::string A, std::string B){
// 	return "(" + B + ") | (~(" + A + "))";
// }
