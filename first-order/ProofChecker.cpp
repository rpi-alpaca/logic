#include "ProofChecker.h"
#include "FirstOrderTree.h"
#include <iterator>
using namespace std;

// ProofChecker provides a way to create first order logic proofs in ALPACA.
// mainStatement is the logical expression you are trying to prove (represented as a FirstOrderTree object).
// mainStatement is supported by several children statements, stored in the childStatements array.
// When the user provides a valid justification, ProofChecker checks whether mainStatement follows from 
// the childStatements by the justification.


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

// Change the justification 
void ProofChecker::changeJustification(const string& just) {
	justification = just;
} 

// Modify the main statement
void ProofChecker::changeMainStatement(const string& mainStatementString) {
	// TODO: Is there a better way of doing this
	// besides constructing an entirely new tree?
	
	// If we delete a tree in order to make a new one,
	// how problematic is that for parent statements?
	mainStatement = FirstOrderTree(mainStatementString);
	bool validity = isValid();
}

// This function adds child statements to support the main statement
void ProofChecker::addChild(const FirstOrderTree& child){
	childStatements.push_back(FirstOrderTree(child));
}

void ProofChecker::printMainTree() const{
    return mainStatement.printTree();
}

// This function provides the main functionality of the class.
// It checks whether the main statement logically follows from the
// child statements according to the justification.
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
            std::cout << "Child 1 opposite of 3" << std::endl;
            // TODO: Need to figure out how to verify that child 2 is the parent of child 3... 
            
            // one and three are opposites; mainstatement should be equal to child 2 with an added negation
            if(child2.getHeadFirstOrderNode()->value.compare(mainStatement.getHeadFirstOrderNode()->value) && !child2.getHeadFirstOrderNode()->negation && mainStatement.getHeadFirstOrderNode()->negation){
                return true;
            }
            else{
                return false;
            }
        }
        else{ // case where child 2 is opposite of child 3:
            // TODO: Need to figure out how to verify that child 1 is the parent of child 3... 
            std::cout << "Child 2 opposite of 3" << std::endl;
            // two and three are opposites; mainstatement should be equal to child 1 with an added negation
            if(child1.getHeadFirstOrderNode()->value.compare(mainStatement.getHeadFirstOrderNode()->value) && !child1.getHeadFirstOrderNode()->negation && mainStatement.getHeadFirstOrderNode()->negation){
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
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
        const FirstOrderTree& child1 = *(itr++);
        const FirstOrderTree& child2 = *(itr++);
        const FirstOrderTree& child3 = *(itr++);

        // child 3 should be the exact opposite of either child 1 or child 2

        // case where child 1 is opposite of child 3:
        if(child1.getHeadFirstOrderNode()->value.compare(child3.getHeadFirstOrderNode()->value) && !child1.getHeadFirstOrderNode()->negation != !child3.getHeadFirstOrderNode()->negation){
            // TODO: Need to figure out how to verify that child 2 is the parent of child 3... 
            
            // one and three are opposites; mainstatement should be equal to child 2 without its negation
            if(child2.getHeadFirstOrderNode()->value.compare(mainStatement.getHeadFirstOrderNode()->value) && child2.getHeadFirstOrderNode()->negation && !mainStatement.getHeadFirstOrderNode()->negation){
                return true;
            }
            else{
                return false;
            }
        }
        else{ // case where child 2 is opposite of child 3:
            // TODO: Need to figure out how to verify that child 1 is the parent of child 3... 
            // two and three are opposites; mainstatement should be equal to child 1 without its negation
            if(child1.getHeadFirstOrderNode()->value.compare(mainStatement.getHeadFirstOrderNode()->value) && child1.getHeadFirstOrderNode()->negation && !mainStatement.getHeadFirstOrderNode()->negation){
                return true;
            }
            else{
                return false;
            }
        }
        return false;
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
        FirstOrderNode* root = mainStatement.getHeadFirstOrderNode();
        FirstOrderNode* oneNode = child1.getHeadFirstOrderNode();
        FirstOrderNode* twoNode = child2.getHeadFirstOrderNode();
        string oneValue = oneNode->value;
        bool oneNegation = oneNode->negation;
        string twoValue = twoNode->value;
        bool twoNegation = twoNode->negation;
        cout << root->left->negation << " "; 
        cout << root->right->negation << " ";
        //Check Root Left's Child Value == Child 1 Value
        //Case 1: Root Left Value != Child 1 Value
        if(root->left->value == oneValue && root->left->negation == oneNegation){
            //Equal => Return Root Right Value == Child 1 Value.
            if(root->right->value == twoValue && root->right->negation == twoNegation){
                return true;
            }
            return false;
        }
        else{
            if(root->left->value == twoValue && root->left->negation == twoNegation){
                if(root->right->value == oneValue && root->right->negation == oneNegation){
                    cout << "2" << endl;
                    return true;
                }
                return false;
            }
            return false;
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
        
        const FirstOrderTree* conditional = nullptr;
        const FirstOrderTree* antecedent = nullptr;
        if(child1.getHeadFirstOrderNode()->opType == '>'){
            conditional = &child1;
            antecedent = &child2;
        }
        else if(child2.getHeadFirstOrderNode()->opType == '>'){
            conditional = &child2;
            antecedent = &child1;
        }
        else{
            return false;
        }
        // Get both sides of the operation
        FirstOrderTree first(conditional->getHeadFirstOrderNode()->left);
        FirstOrderTree second(conditional->getHeadFirstOrderNode()->right);
        // return true if child1 matches the left side and
        // the main statement matches the right side
        if(first.getString() == antecedent->getString() && second.getString() == mainStatement.getString()){
            return true;
        }
        return false;
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