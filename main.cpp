// this is the main file for the logic team


/*
	This is a program that will take in a logical statement and do various functions
	
*/


#include "statementevaluator.h"
#include "LogicGate.h"
#include "expressionparser.h"
#include "Tree.h"


void statementEvaluatorTest();
void statementParserTest();

int main(int argc, char* argv[]) {
	std::cout << "Testing" << std::endl;

	std::string stConstructor;
	std::cout << "Input a statement of format (A) & (B): ";
	std::getline(std::cin, stConstructor);

	StatementParser testStatement(stConstructor);
	testStatement.print();
	testStatement.printTree();

	statementParserTest();
	statementEvaluatorTest();

	StatementParser evalExample("(A & B) | (C & D)");
	std::vector<std::pair<std::string, bool> > varTruthValues;
	varTruthValues.push_back(make_pair("A", true));
	varTruthValues.push_back(make_pair("B", true));
	varTruthValues.push_back(make_pair("C", true));
	varTruthValues.push_back(make_pair("D", true));
	StatementEvaluator eval;
	std::cout << eval.evaluateStatement(evalExample, varTruthValues) << std::endl;

	return 0;
}

void statementParserTest() {
	std::cout << "RUNNING STATEMENTPARSERTEST" << std::endl << std::endl;

	StatementParser state1;
	StatementParser state2;
	state1.changeHeadValue("The sky is blue");
	state2.changeHeadValue("Hali's shirt is blue");
	StatementParser combined(state1, state2);

	state1.print();
	state2.print();
	combined.print();
}

void statementEvaluatorTest() {
	std::cout << "RUNNING STATEMENTEVALUATORTEST" << std::endl << std::endl;

	StatementParser state1;
	StatementParser state2;
	state1.changeHeadValue("The sky is blue");
	state2.changeHeadValue("Hali's shirt is blue");
	StatementParser combined(state1, state2);

	std::vector<std::string> variables;
	variables.emplace_back("The sky is blue");
	variables.emplace_back("Hali's shirt is blue");

	// Testing printTruthTable and evaluateStatement
	StatementEvaluator eval;
	eval.printTruthTable(combined, variables);
}
