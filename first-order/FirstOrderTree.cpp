#include "FirstOrderTree.h"
#include "expressionparser.h"
#include <stack>

using namespace std;

// FirstOrderTree is the structure used for storing logical expressions in the first
// order logic system. It is very similar to the original Tree structure, but it will
// also eventually support statements with quanitifers. There are other modifications we
// have made as well to support the type of operations required by ProofChecker.

// Constructor; creates an empty tree
FirstOrderTree::FirstOrderTree(){
	head = new FirstOrderNode;
	head->opType = 'v';
}

// Copy constructor
FirstOrderTree::FirstOrderTree(const FirstOrderTree& s) {
	head = copy_statement(s.head);
}

// Constructor which takes in two tree expressions and conjuncts them together
FirstOrderTree::FirstOrderTree(const FirstOrderTree& s1, const FirstOrderTree& s2) {
	head = new FirstOrderNode;
	head->opType = '&';
	head->left = copy_statement(s1.head);
	head->right = copy_statement(s2.head);
}

// Constructor to convert a string to a FirstOrderTree
FirstOrderTree::FirstOrderTree(const std::string& statement){
	//split it up
	parseStatement(head, statement);
}

// constructs a FirstOrderTree given an firstOrderNode with that node as the head
FirstOrderTree::FirstOrderTree(FirstOrderNode* s){
	head = copy_statement(s);
}

// Modify the value at the head of the tree
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

//Returns Head Node of Tree For isValid() Determination In ProofChecker:
FirstOrderNode* FirstOrderTree::getHeadFirstOrderNode() const {
	return head;
}

//Returns the tree as a string in order
std::string FirstOrderTree::getString() const {
	return getStringNode(head);
}

//Helper function for print
std::string FirstOrderTree::getStringNode(FirstOrderNode* s) const {
    string result = "";
	if(s->negation){ 
		result = result + '~';
	}
	if(s->opType == 'v'){
		result = result + s->value;
	}
	else {
		result = result +  '(';
		result = result +  getStringNode(s->left);
		result = result +  " ";
		result = result +  s->opType + " ";
		result = result +  getStringNode(s->right);
	    result = result +  ")";
	}
    return result;
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
	new_node->negation = old_node->negation;
	new_node->connector = old_node->connector;
	new_node->left = copy_statement(old_node->left);
	new_node->right = copy_statement(old_node->right);
	return new_node;
}

//Recursively Parses Any String Input Statment
//Previously Assumed That Statement Format = ((A) & (B)) & (~C)
//However, Now = Implementation w/ Shunting-Yard Algorithm
//Assesses The Precedence Of Operators To Construct Expression Tree.
void FirstOrderTree::parseStatement(FirstOrderNode*& n, const std::string& statement){
	//Make A Copy Of Input Statement:
	string currentInput = string(statement);
	//Run Shunting-Yard Algorithm To Grab Output Reverser Polish Notation of Statement.
	ExpressionParser currentExpressionParser;
	string currentOutput = currentExpressionParser.runShuntingYardAlgorithm(currentInput);
	stack<FirstOrderNode*> convertToTree;
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
		if(currentExpressionParser.isOperator(currentOutput[k]) && currentOutput[k] != negValue){
			//Compute First Previous Stack Value.
			//= Most Recent Stack Value.
			FirstOrderNode* prevOne = NULL;
			if(!convertToTree.empty()){
				prevOne = convertToTree.top();
				convertToTree.pop();
			}
			//Compute Second Previous Stack Value.
			//= Second Most Recent Stack Value.
			FirstOrderNode* prevTwo = NULL;
			if(!convertToTree.empty()){
				prevTwo = convertToTree.top();
				convertToTree.pop();
			}
			//Create New New Holding 'Operator' w/ Children = Two Previous Values On Stack.
			FirstOrderNode* currentNode = new FirstOrderNode();
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
		else if(currentExpressionParser.isOperator(currentOutput[k]) && currentOutput[k] == negValue){
			FirstOrderNode* prevOne = NULL;
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
			FirstOrderNode* currentNode = new FirstOrderNode();
			currentNode->value = currentOutput[k];
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
	//Set New Head Value = Top/Root of Stack.
	n = convertToTree.top();
}

// Helper function for garbage collection
void FirstOrderTree::delete_helper(FirstOrderNode* s) {
	if (!s)
		return;
	this->delete_helper(s->right);
	this->delete_helper(s->left);

	delete s;
	s = NULL;
}

// Destructor for garbage collection of pointers
FirstOrderTree::~FirstOrderTree() {
	this->delete_helper(this->head);
	this->head = nullptr;
}

FirstOrderTree& FirstOrderTree::operator=(const FirstOrderTree& tree) {
	if (&tree == this) return *this;

	this->delete_helper(this->head);
	head = copy_statement(tree.head);
	return *this;
}
// std::string conditional(std::string A, std::string B){
// 	return "(" + B + ") | (~(" + A + "))";
// }