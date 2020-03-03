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
	string formatInputValue(string currentInput);
	string runShuntingYardAlgorithm(string str);

private:
	string output;
};
