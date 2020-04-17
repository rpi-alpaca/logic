#include "ProofChecker.h"
#include "FirstOrderTree.h"
#include <iterator>
using namespace std;

// Default constructor
ProofChecker::ProofChecker() {
	mainStatement = FirstOrderTree();
	justification = "Introduction";
}

// String constructor
ProofChecker::ProofChecker(const string& mainStatementString) {
	mainStatement = FirstOrderTree(mainStatementString);
	justification = "Introduction";
} 

void ProofChecker::changeJustification(const string& just) {
	justification = just;
} 

void ProofChecker::changeMainStatement(const string& mainStatementString) {
	// TODO: Is there a better way of doing this
	// besides constructing an entirely new tree?
	
	// If we delete a tree in order to make a new one,
	// how problematic is that for parent statements?
	mainStatement = FirstOrderTree(mainStatementString);
	bool validity = isValid();
}

void ProofChecker::addChild(const FirstOrderTree& child){
	childStatements.push_back(FirstOrderTree(child));
}

bool ProofChecker::isValid() const{
	// TODO

    if(justification=="~I"){
        // NOT INTRO

        // If you have A, and from A you get B, and you have ~B, you can get ~A
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
        const FirstOrderTree& child1 = *(itr++);
        const FirstOrderTree& child2 = *(itr++);
        const FirstOrderTree& child3 = *(itr++);

        // child 3 should be the exact opposite of either child 1 or child 2

        // case where child 1 is opposite of child 3:
        if(child1.getHeadFirstOrderNode()->value.compare(child3.getHeadFirstOrderNode()->value) && child1.getHeadFirstOrderNode()->negation != child3.getHeadFirstOrderNode()->negation){
            // one and three are opposites; mainstatement should be equal to child 2 with an added negation

            if(child2.getHeadFirstOrderNode()->value.compare(mainStatement.getHeadFirstOrderNode()->value) && child2.getHeadFirstOrderNode()->negation && !mainStatement.getHeadFirstOrderNode()->negation){
                return true;
            }
            else{
                return false;
            }
        }
        else{ // case where child 2 is opposite of child 3:
            // two and three are opposites; mainstatement should be equal to child 1 with an added negation
            if(child1.getHeadFirstOrderNode()->value.compare(mainStatement.getHeadFirstOrderNode()->value) && child1.getHeadFirstOrderNode()->negation && !mainStatement.getHeadFirstOrderNode()->negation){
                return true;
            }
            else{
                return false;
            }
        }
        return false;
    }
	
    if(justification=="~E"){
	// NOT ELIM

    // If you have ~A, and from ~A you get B, and you have ~B, you can get A
    }

    if(justification=="&I"){
        //AND Introduction:
        FirstOrderTree child1;
        FirstOrderTree child2;
        //Start At Begininng of Children Statements:
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
        child1 = *itr;
        itr++;
        child2 = *itr;
        //Get Head of Main Statement:
        cout << childStatements.size() << endl;
        FirstOrderNode* root = mainStatement.getHeadFirstOrderNode();
        if(root->left != child1.getHeadFirstOrderNode()){
            //Case 1: 
            if(root->left != child2.getHeadFirstOrderNode()){
                return false;
            }
            else{
                return root->right == child1.getHeadFirstOrderNode(); 
            }
        }
        else{
            return root->right == child2.getHeadFirstOrderNode();
        }

    }

    if(justification=="&E"){
        // AND ELIM
        FirstOrderTree child;
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
        child = *itr;
    }

    if(justification=="|I"){
        // OR INTRO
        FirstOrderTree child;
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
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
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
        const FirstOrderTree& child1 = *(itr++);
        const FirstOrderTree& child2 = *(itr++);
        // assume the child2 is the conditional being eliminted
        // get both sides of the conditional
        // If the head operator is not a conditional, return false
        FirstOrderNode* head = child2.getHeadFirstOrderNode();

        if(!(head->opType == '>')) {
            return false;
        }
        // otherwise, get both sides of the operation
        FirstOrderTree* first;
        FirstOrderTree* second;
        first = new FirstOrderTree(head->left);
        second = new FirstOrderTree(head->right);

        // return true if child1 matches the left side and
        // the main statement matches the right side
        if(first->getString() == child1.getString() && second->getString() == mainStatement.getString())
            return true;
        // If the child1 is not the left side of the operation and
        // the main statement is not the right side of the operation, return false
        //if(first)
        // also later compare while assuming the child1 is the conditional being eliminated
    }

    if(justification=="=I"){
        // <-> INTRO
        FirstOrderTree child1;
        FirstOrderTree child2;
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
        child1 = *itr;
        itr++;
        child2 = *itr;
    }

    if(justification=="=E"){
        // <-> ELIM
        FirstOrderTree child1;
        FirstOrderTree child2;
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
        child1 = *itr;
        itr++;
        child2 = *itr;
    }
	return false; 

}