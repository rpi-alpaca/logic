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

        string neg1 = child->print();

    }
	
    if(justification=="~E"){
	// NOT ELIM
    }

    if(justification=="&I"){
        //AND Introduction:
        FirstOrderTree* child1;
        FirstOrderTree* child2;
        //Start At Begininng of Children Statements:
        std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
        child1 = *itr;
        itr++;
        child2 = *itr;
        //Get Head of Main Statement:
        FirstOrderNode* root = mainStatement.getHeadNode();
        if(root->left != child1.getHeadNode()){
            if(root->left != child2.getHeadNode()){
                return false;
            }
            else{
                return root->right == child1.getHeadNode(); 
            }
        }
        else{
            return root->right == child2.getHeadNode();
        }

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
        // assign child1 and child2 to the two statements starting the inference rule
        FirstOrderTree* child1;
        FirstOrderTree* child2;
        std::list<FirstOrderTree*>::const_iterator itr = childStatements.begin();
        child1 = *itr;
        itr++;
        child2 = *itr;
        // assume the child2 is the conditional being eliminted
        // get both sides of the conditional
        // If the head operator is not a conditional, return false
        FirstOrderNode* head = child2.getHeadFirstOrderNode()
        if(!(head->opType() == '>')) {
            return false;
        }
        // otherwise, get both sides of the operation
        FirstOrderNode* first;
        FirstOrderNode* second;
        first = *(head->left)
        second = *(head->right)
        // If the child1 is not the left side of the operation and
        // the main statement is not the right side of the operation, return false
        //if(first)
        // also later compare while assuming the child1 is the conditional being eliminated


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