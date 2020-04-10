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

    if(justification=="~I"){
        // NOT INTRO
        FirstOrderTree* child;
        std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
        child = *itr;
    }
	
    if(justification=="~E"){
	// NOT ELIM
    }

    if(justification=="&I"){
        // AND INTRO
        FirstOrderTree* child1;
        FirstOrderTree* child2;
        std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
        child1 = *itr;
        itr++;
        child2 = *itr;
    }

    if(justification=="&E"){
        // AND ELIM
        FirstOrderTree* child;
        std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
        child = *itr;
    }

    if(justification=="|I"){
        // OR INTRO
        FirstOrderTree* child;
        std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
        child = *itr;
    }

    if(justification=="|E"){
	    // OR ELIM
    }
	
    if(justification==">I"){
	    // -> INTRO
    }

    if(justification==">E"){
        // -> ELIM
        FirstOrderTree* child;
        std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
        child = *itr;
    }

    if(justification=="=I"){
        // <-> INTRO
        FirstOrderTree* child1;
        FirstOrderTree* child2;
        std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
        child1 = *itr;
        itr++;
        child2 = *itr;
    }

    if(justification=="=E"){
        // <-> ELIM
        FirstOrderTree* child1;
        FirstOrderTree* child2;
        std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
        child1 = *itr;
        itr++;
        child2 = *itr;
    }
	return false; 

}