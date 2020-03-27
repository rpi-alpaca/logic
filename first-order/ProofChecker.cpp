#include "ProofChecker.h"
using namespace std;

// Default constructor
ProofChecker::ProofChecker() {
	mainStatement = new FirstOrderTree();
	justification = "Introduction"
}

// String constructor
ProofChecker::ProofChecker(const string& mainStatementString) {
	mainStatement = new FirstOrderTree(mainStatementString);
	justification = "Introduction";
} 

void ProofChecker::changeJustification(const string& just) {
	justification = just;
	// TODO: check for validity?
} 

void ProofChecker::changeMainStatement(const string& mainStatementString) {
	// TODO: Is there a better way of doing this
	// besides constructing an entirely new tree?
	
	// If we delete a tree in order to make a new one,
	// how problematic is that for parent statements?
	
	delete mainStatement;
	mainStatement = new FirstOrderTree(mainStatementString);
	// Check for validity?
}

