//This is the Main File for the Logic Team.
//Currently, this is simply a Command-Line Interface to be Integrated with the Frontend GUI.
//That is, this is a Program that will take in a Logical Statement + Perform Various Operations.

#include "statementevaluator.h"
#include "LogicGate.h"
#include "expressionparser.h"
#include "Tree.h"
using namespace std;

void statementEvaluatorTest();
void statementParserTest();

void defaultTest();
void variableHeaderTest();
void equivalenceTest();
void memoryTest();

int main(int argc, char* argv[]) {
	
	defaultTest();
	variableHeaderTest();
	equivalenceTest();
	memoryTest();
	
	return EXIT_SUCCESS;
}

void statementParserTest() {
	cout << endl;
	cout << "Running Statement Parser Test." << endl << endl;

	StatementParser state1;
	StatementParser state2;
	state1.changeHeadValue("The Sky Is Blue");
	state2.changeHeadValue("Hali's Shirt Is Blue");
	StatementParser combined(state1, state2);

	state1.print();
	state2.print();
	combined.print();
}

void statementEvaluatorTest() {
	cout << endl;
	cout << "Running Statement Evaluator Test." << endl << endl;

	StatementParser state1;
	StatementParser state2;
	state1.changeHeadValue("The Sky Is Blue");
	state2.changeHeadValue("Hali's Shirt Is Blue");
	StatementParser combined(state1, state2);

	vector<string> variables;
	variables.emplace_back("The Sky Is Blue");
	variables.emplace_back("Hali's Shirt Is Blue");

	// Testing printTruthTable and evaluateStatement
	StatementEvaluator eval;
	eval.printTruthTable(combined, variables);
}
