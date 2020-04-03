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
	// Input Test
	cout << "Start of Testing For ALPACA-LOGIC Engine." << endl;
	string stConstructor;

	cout << "Input Valid Statement of the Format A & B: ";
	getline(cin, stConstructor);
	StatementParser testStatement(stConstructor);

	cout << endl;
	cout << "Output Print() Test:" << endl;
	testStatement.print();
	cout << "Output PrintTree() Test: " << endl;
	testStatement.printTree();

	cout << endl;

	cout << "Truth Table For " << stConstructor << ": " << endl;

	StatementEvaluator eval;
	eval.printTruthTable(testStatement);

	cout << endl << endl;

	// Variable Header Test
	StatementParser headerTest("A & B & C");

	vector<string> varTruthValues;
	varTruthValues.emplace_back("Red");
	varTruthValues.emplace_back("Green");
	varTruthValues.emplace_back("Blue");

	eval.printTruthTable(headerTest, varTruthValues);

	// Equivalence Test 1 (DeMorgan's : True)
	StatementParser statement1("A & B");
	cout << "\nTruth Table For " << "A & B" << ": " << endl;
	eval.printTruthTable(statement1);

	StatementParser statement2("~(~A | ~B)");
	cout << "\nTruth Table For " << "~(~A | ~B)" << ": " << endl;
	eval.printTruthTable(statement2);

	cout << endl << "statement1 and statement2 are equal: " << boolalpha << eval.areLogicallyEquivalent(statement1, statement2) << endl << endl;

	// Equivalence Test 2 (Complex : True)
	StatementParser statement3("~(A | ~(B | (~C & D))) | (C & B) | ~A");
	cout << "\nTruth Table For " << "~(A | ~(B | (~C & D))) | (C & B) | ~A" << ": " << endl;
	eval.printTruthTable(statement3);

	StatementParser statement4("~A | (C & B)");
	cout << "\nTruth Table For " << "~A | (C & B)" << ": " << endl;
	eval.printTruthTable(statement4);

	cout << endl << "statement3 and statement4 are equal: " << boolalpha << eval.areLogicallyEquivalent(statement3, statement4) << endl << endl;

	// Equivalence Test 3 (Basic : False)
	StatementParser statement5("A & B");
	cout << "\nTruth Table For " << "A & B" << ": " << endl;
	eval.printTruthTable(statement5);

	StatementParser statement6("A & ~B");
	cout << "\nTruth Table For " << "A & ~B" << ": " << endl;
	eval.printTruthTable(statement6);

	cout << endl << "statement5 and statement6 are equal: " << boolalpha << eval.areLogicallyEquivalent(statement5, statement6) << endl << endl;

	// Equivalence Test 4 (Extra Variables : False)
	cout << endl << "Should be false: " << boolalpha << eval.areLogicallyEquivalent(statement5, headerTest) << endl << endl;

	// Memory Tests

	// Assignment Operator
	statement5 = statement6;
	cout << "\nTruth Table For " << "A & ~B" << ": " << endl;
	eval.printTruthTable(statement5);

	// Copy Constructor
	StatementParser statement7(statement6);
	cout << "\nTruth Table For " << "A & ~B" << ": " << endl;
	eval.printTruthTable(statement7);

	// Join Constructor
	StatementParser statement8("A");
	StatementParser statement9("~B");
	StatementParser statement10(statement8, statement9);
	cout << "\nTruth Table For " << "A & ~B" << ": " << endl;
	eval.printTruthTable(statement10);

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
