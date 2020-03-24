#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//Expression Parser = Main Class For Shunting-Yard Algorithm
//Expression Parser Places A Given Expression Into Reverse Polish Notation.
class ExpressionParser {
public:
	ExpressionParser();
	bool isOperator(char token);
	char getAssociativity(char op);
	int getPrecedence(char op);
	bool getGenerality(char op);
	bool isCorrectSyntax(string input);
	string formatInputValue(string currentInput);
	string runShuntingYardAlgorithm(string str);
};
