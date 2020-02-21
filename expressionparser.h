#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class ExpressionParser {
public:
	ExpressionParser();
	bool isOperator(char token);
	int precedence(char op);
	string read_token(string str);
	bool calculate(string input);
	string getOutput();
	string formatInputValue(string currentInput);
	~ExpressionParser();

private:
	string output;
	
};
