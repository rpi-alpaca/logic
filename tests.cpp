#include "statementevaluator.h"
#include "LogicGate.h"
#include "expressionparser.h"
#include "Tree.h"
using namespace std;

void defaultTest() {
	cout << "---------- DEFAULT TEST ----------\n\n";
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
	cout << endl;
}

void variableHeaderTest() {
	cout << "---------- VARIABLE HEADER TEST ----------\n\n";

	StatementEvaluator eval;

	// Variable Header Test
	StatementParser headerTest("A & B & C");

	vector<string> varTruthValues;
	varTruthValues.emplace_back("Red");
	varTruthValues.emplace_back("Green");
	varTruthValues.emplace_back("Blue");

	eval.printTruthTable(headerTest, varTruthValues);
	cout << endl;
}

void equivalenceTest() {
	cout << "---------- EQUIVALENCE TEST ----------\n\n";
	StatementEvaluator eval;
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
}

void memoryTest() {
	cout << "---------- MEMORY TEST ----------\n\n";

	StatementEvaluator eval;

	StatementParser statement1("A & ~B");
	StatementParser statement2("A & B");

	// Assignment Operator
	statement2 = statement1;
	cout << "\nShould Be Truth Table For " << "A & ~B" << ": " << endl;
	eval.printTruthTable(statement2);

	// Copy Constructor
	StatementParser statement3(statement2);
	cout << "\nShould Be Truth Table For " << "A & ~B" << ": " << endl;
	eval.printTruthTable(statement3);

	// Join Constructor
	StatementParser statement4("A");
	StatementParser statement5("~B");
	StatementParser statement6(statement4, statement5);
	cout << "\nShould Be Truth Table For " << "A & ~B" << ": " << endl;
	eval.printTruthTable(statement6);
	cout << endl;
}