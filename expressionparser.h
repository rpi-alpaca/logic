#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class ExpressionParser {
public:
	ExpressionParser();
	bool isOperator(char token);
	char getAssociativity(string op);
	bool isBoolean(string c);
	int getPrecedence(char op);
	bool isLeftP(char c);
	bool isRightP(char c);
	string read_token(string str);
	bool calculate(string input);
	string getOutput();
	string formatInputValue(string currentInput);
	string runShuntingYardAlgorithm(string str);
	~ExpressionParser();

private:
	string output;
	char*[] operatorsList = {'&', '|', '~', '=', '>'};
	
};
