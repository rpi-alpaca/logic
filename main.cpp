//This is the Main File for the Logic Team.
//Currently, this is simply a Command-Line Interface to be Integrated with the Frontend GUI.
//That is, this is a Program that will take in a Logical Statement + Perform Various Operations.

#include "statementevaluator.h"
#include "LogicGate.h"
#include "expressionparser.h"
#include "Tree.h"
using namespace std;

void defaultTest() {
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

int main(int argc, char* argv[]) {
	defaultTest();
	return EXIT_SUCCESS;
}
