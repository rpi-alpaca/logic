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

int main(int argc, char* argv[]) {
	cout << "Start of Testing For ALPACA-LOGIC Engine." << endl;
	string stConstructor;

	cout << "Input Valid Statement of the Format (A) & (B): ";
	getline(cin, stConstructor);
	StatementParser testStatement(stConstructor);

	cout << endl;
	cout << "Output Print() Test:" << endl;
	testStatement.print();
	cout << "Output PrintTree() Test: " << endl;
	testStatement.printTree();

	statementParserTest();
	statementEvaluatorTest();

	cout << endl;
	cout << "Test Expression Evaluation For (A & B) | (C & D): " << endl;
	cout << "Input: A = T, B = F, C = T, D = F." << endl;
	StatementParser evalExample("(A & B) | (C & D)");
	vector<pair<string, bool> > varTruthValues;
	varTruthValues.push_back(make_pair("A", true));
	varTruthValues.push_back(make_pair("B", false));
	varTruthValues.push_back(make_pair("C", true));
	varTruthValues.push_back(make_pair("D", false));
	StatementEvaluator eval;
	cout << "Output = " << eval.evaluateStatement(evalExample, varTruthValues) << endl;

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
