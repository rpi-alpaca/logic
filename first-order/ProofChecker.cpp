#include "ProofChecker.h"
#include "FirstOrderTree.h"
#include <iterator>
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
	bool validity = isValid();
} 

void ProofChecker::changeMainStatement(const string& mainStatementString) {
	// TODO: Is there a better way of doing this
	// besides constructing an entirely new tree?
	
	// If we delete a tree in order to make a new one,
	// how problematic is that for parent statements?
	
	delete mainStatement;
	mainStatement = new FirstOrderTree(mainStatementString);
	bool validity = isValid();
}

void ProofChecker::addChild(const FirstOrderTree& child){
	childStatements.push_back(new FirstOrderTree(child));
}

bool ProofChecker::isValid() const{
	// TODO

	// NOT INTRO
	FirstOrderTree* child;
	std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
	child = *itr;

	// NOT ELIM

	// AND INTRO
	FirstOrderTree* child1;
	FirstOrderTree* child2;
	std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
	child1 = *itr;
	itr++;
	child2 = *itr;

	// AND ELIM
	FirstOrderTree* child;
	std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
	child = *itr;

	// OR INTRO
	FirstOrderTree* child;
	std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
	child = *itr;

	// OR ELIM
	

	// -> INTRO

	// -> ELIM
	FirstOrderTree* child;
	std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
	child = *itr;

	// <-> INTRO
	FirstOrderTree* child1;
	FirstOrderTree* child2;
	std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
	child1 = *itr;
	itr++;
	child2 = *itr;

	// <-> ELIM
	FirstOrderTree* child1;
	FirstOrderTree* child2;
	std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
	child1 = *itr;
	itr++;
	child2 = *itr;
	return false; 
}