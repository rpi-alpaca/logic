#include "Tree.h"
#include "expressionparser.h"
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

//Constructor For Statement Parser w/ Root Head Node:
StatementParser::StatementParser(){
	head = new StatementNode;
	head->opType = 'v';
}

//Copy-Constructor For Statement Parser:
StatementParser::StatementParser(const StatementParser& s) {
	//Copy new data
	head = copy_statement(s.head);
	variableNames = s.getVariableNames();
}

//Constructor To Merge Two StatementParsers:
//(i.e., Merges Two Logical Expressions Into One By Conjuncting Them Together)
StatementParser::StatementParser(const StatementParser& s1, const StatementParser& s2) {
	head = new StatementNode;
	head->opType = '&';
	head->value = '&';
	head->left = copy_statement(s1.head);
	head->right = copy_statement(s2.head);

	// A set is used to account for a variable that appears in both statments
	set<string> variableNamesTemp;
	for(string varName : s1.getVariableNames()) {
		variableNamesTemp.insert(varName);
	}
	for(string varName : s2.getVariableNames()) {
		variableNamesTemp.insert(varName);
	}

	for(string varName : variableNamesTemp) {
		variableNames.emplace_back(varName);
	}

}

//Constructor Based On String Input:
//Runs Shunting-Yard Algorithm And Sets New Value For Head.
StatementParser::StatementParser(const std::string& statement){
	head = new StatementNode();
	parseStatement(head, statement);
}

StatementParser::~StatementParser() {
	destroy_statement(head);
}

StatementParser& StatementParser::operator=(const StatementParser& s) {
	//Delete old data
	destroy_statement(head);
	variableNames.clear();

	//Copy new data
	head = copy_statement(s.head);
	variableNames = s.getVariableNames();

	return *this;
}

//Changes The Statement That An Underlying Expression Represents.
//Could Be Dangerous?
void StatementParser::changeHeadValue(const std::string& statement) {
	head->value = statement;
}

//In-Order Traversal Printing of Expression Tree:
void StatementParser::print() const {
	print(std::cout);
}

void StatementParser::print(std::ostream& o) const {
	//Invokes Helper Function:
	printNode(head, o);
	o << std::endl;
}

//Helper Function For print():
void StatementParser::printNode(StatementNode* s, std::ostream& o) const {
	if(!s){
		return;
	}
	//If Negation Node, Append Negation Prior To Printing Value
	if(s->negation){
		o << "~";
	}
	//Case 1: Not Operator, Simply Print Value.
	if(s->opType == 'v'){
		o << s->value;
	}
	//Case 2: Operator
	//Simply Print Left Child + Current Value Operator + Right Child.
	else{
		o << '(';
		printNode(s->left, o);
		o << " ";
		o << s->value << " ";
		printNode(s->right, o);
		o << ")";
	}
}

//Print The Tree In An Interesting Tree Structure
//Method To Visualize Tree In Reality
void StatementParser::printTree() const {
	printTreeHelper(head, 0);
}

//Helper Function For printTree()
void StatementParser::printTreeHelper(StatementNode* s, int depth) const {
	if (!s)
		return;
	printTreeHelper(s->right, depth+1);
	std::cout << std::string(depth, '\t') << (s->negation ? '~' : ' ') << s->opType;
	if (s->opType == 'v')
		std::cout << ": " << (s->negation ? '~' : ' ') << s->value;
	std::cout << std::endl;
	printTreeHelper(s->left, depth+1);
}

//Copy Helper Function For Copying Nodes
StatementNode* StatementParser::copy_statement(StatementNode* old_node) {
	if (old_node == nullptr)
		return nullptr;
	StatementNode* new_node = new StatementNode;
	new_node->value = old_node->value;
	new_node->opType = old_node->opType;
	new_node->connector = old_node->connector;
	new_node->negation = old_node->negation;
	new_node->left = copy_statement(old_node->left);
	new_node->right = copy_statement(old_node->right);
	return new_node;
}

//Destroy Helper Function For Destroying Nodes
void StatementParser::destroy_statement(StatementNode*& old_node) {
	if(old_node) {
		destroy_statement(old_node->left);
		destroy_statement(old_node->right);
		delete old_node;
		old_node = nullptr;
	}
}

//Recursively Parses Any String Input Statment
//Previously Assumed That Statement Format = ((A) & (B)) & (~C)
//However, Now = Implementation w/ Shunting-Yard Algorithm
//Assesses The Precedence Of Operators To Construct Expression Tree.
void StatementParser::parseStatement(StatementNode*& n, const std::string& statement){
	//Make A Copy Of Input Statement:
	string currentInput = string(statement);
	//Run Shunting-Yard Algorithm To Grab Output Reverser Polish Notation of Statement.
	ExpressionParser* currentExpressionParser = new ExpressionParser();
	string currentOutput = currentExpressionParser->runShuntingYardAlgorithm(currentInput);
	stack<StatementNode*> convertToTree;
	cout << "Output of Shunting-Yard Algorithm (Reverse Polish Notation) = " << currentOutput << endl;
	//Case = Invalid Expression Communicated By Expression Parser.
	if(currentOutput == "ERROR"){
		return;
	}
	//Constant For Negation Operator Check.
	char negValue = '~';
	//Loop Through Current Output To Construct Expression Tree:
	for(unsigned int k=0; k<currentOutput.size(); k++){
		//Case 1: Operator != '~'
		//Create New Node w/ Appropriate Previous Children.
		if(currentExpressionParser->isOperator(currentOutput[k]) && currentOutput[k] != negValue){
			//Compute First Previous Stack Value.
			//= Most Recent Stack Value.
			StatementNode* prevOne = NULL;
			if(!convertToTree.empty()){
				prevOne = convertToTree.top();
				convertToTree.pop();
			}
			//Compute Second Previous Stack Value.
			//= Second Most Recent Stack Value.
			StatementNode* prevTwo = NULL;
			if(!convertToTree.empty()){
				prevTwo = convertToTree.top();
				convertToTree.pop();
			}
			//Create New New Holding 'Operator' w/ Children = Two Previous Values On Stack.
			StatementNode* currentNode = new StatementNode();
			//Set Operator/Value = 'Operator'
			currentNode->opType = currentOutput[k];
			currentNode->value = currentOutput[k];
			//Sanity Check: Set Default False, Negation To False.
			currentNode->negation = false;
			//Left Child = Eldest Recent Stack Value.
			currentNode->left = prevTwo;
			//Right Child = Youngest Recent Stack Value.
			currentNode->right = prevOne;
			//Append New Node To Stack.
			convertToTree.push(currentNode);
		}
		//Case 2: Operator == '~'
		//Do Not Create New Node.
		//Rather Set Flag of Node To Be Negation = True;
		else if(currentExpressionParser->isOperator(currentOutput[k]) && currentOutput[k] == negValue){
			StatementNode* prevOne = NULL;
			if(!convertToTree.empty()){
				prevOne = convertToTree.top();
				convertToTree.pop();
			}
			//As Long As No NULL, Add prevOne w/ Flag negation = True Back To Stack.
			if(prevOne != NULL){
				prevOne->negation = !(prevOne->negation);
				convertToTree.push(prevOne);
			}
		}
		//Case 3: Non-Operator Atomic Statement
		else{
			//Set Operator Type = 'v' To Consistently Print
			//Value Set To Name of Node (e.g., 'A', 'B', ...)
			//Note: v' May Indicate Leaf Node?
			StatementNode* currentNode = new StatementNode();
			currentNode->value = currentOutput[k];
			if(find(variableNames.begin(), variableNames.end(), currentNode->value) == variableNames.end()) {
				variableNames.push_back(currentNode->value);
			}
			currentNode->opType = 'v';
			//Set Negation = False As Sanity Check Once Again.
			currentNode->negation = false;
			//Append New Node To Stack:
			convertToTree.push(currentNode);
		}
	}
	//Error Check For Random Error Edge Scenarios Unaccounted For:
	if(convertToTree.size() != 1){
		cout << "Error In Construction. Must Review Input/Output." << endl;
	}
	//Deletes memory
	delete n;
	delete currentExpressionParser;
	//Set New Head Value = Top/Root of Stack.
	n = convertToTree.top();
	
}

const vector<string>& StatementParser::getVariableNames() const {
	return variableNames;
}

bool sortByVariableName(const pair<string, bool>& a, const pair<string, bool>& b) {
	return a.first < b.first;
}
