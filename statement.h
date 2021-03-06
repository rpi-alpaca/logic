//Header class for statement objects
#ifndef statement_h
#define statement_h

#include <string>
#include <vector>

class Statement {
private:
	//Input statement is the statement to be interpreted from user input
	std::string input_statement;
	std::vector<std::string> variables;
	std::vector<char> connectors;
	//"v" for variable
	//"&" for and
	//"|" for or
	//"~" for not
	char statement_type;
	bool value;
	bool is_provable;

	//Interpreter for input_statment
	void interpretStatement();
public:
	Statement();
	Statement(const std::string& input);
};

#endif
