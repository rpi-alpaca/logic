#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class ExpressionParser {
public:
	ExpressionParser();
	bool isOperator(char token);
	char getAssociativity(char op);
	bool isBoolean(char c);
	int getPrecedence(char op);
	bool getGenerality(char op);
	bool isCorrectSyntax(string input);
	string formatInputValue(string currentInput);
	string runShuntingYardAlgorithm(string str);

private:
	string output;
};
