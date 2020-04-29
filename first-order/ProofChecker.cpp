#include "ProofChecker.h"
#include "FirstOrderTree.h"
#include <iterator>
using namespace std;

// ProofChecker provides a way to create first order logic proofs in ALPACA.
// mainStatement is the logical expression you are trying to prove (represented as a FirstOrderTree object).
// mainStatement is supported by several children statements, stored in the childStatements array.
// When the user provides a valid justification, ProofChecker checks whether mainStatement follows from 
// the childStatements by the justification.

bool isSubtreeSame(FirstOrderNode* root, FirstOrderNode* same);

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
            cout << "Child 1 Opposite of Child 3 => Output:" << " ";
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
            cout << "Child 2 Opposite of Child 3 => Output:" << " ";
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
        //AND Introduction Rule:
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

        //By Our Definition, AND Introduction Rule, If More Than 2 Children, Return False.
        if(childStatements.size() > 2){
            return false;
        }

        //If Root NULL, Cannot Be Valid.
        if(!root){
            return false;
        }

        //Assert Dealing w/ AND Node.
        if(root->value != "&"){
            return false;
        }

        //Check Root Left Subtree == Child One Subtree.
        //Case 1: Check Root Left Subtree == Child One Subtree.
        if(isSubtreeSame(root->left, oneNode)){
            //Equal => Return Root Right Subtree == Child One Subtree.
            if(isSubtreeSame(root->right, twoNode)){
                return true;
            }
            return false;
        }
        else{
            //Case 2: Check Root Right Subtree == Child Two Subtree.
            if(isSubtreeSame(root->left, twoNode)){
                //Equal => Return Root Right Subtree == Child One Subtree.
                if(isSubtreeSame(root->right, oneNode)){
                    return true;
                }
                return false;
            }
            return false;
        }

    }

    if(justification=="&E"){
        //And Elimination Rule:
        FirstOrderTree child;
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
        child = *itr;
        //Obtain Appropriate FirstOrderNodes From FirstOrderTrees.
        FirstOrderNode* root = mainStatement.getHeadFirstOrderNode();
        FirstOrderNode* childNode = child.getHeadFirstOrderNode();

        if(childStatements.size() != 1){
            return false;
        }  

        //Child Is Ideally An AND Node. 
        //Parent Root Should Be A Subset of AND Node.
        //If Either Are NULL Must Return False.
        if(!root || !childNode){
            return false;
        }

        //Child Statement Must Be AND.
        if(childNode->value != "&"){
            return false;
        }

        //Case 1: AND Elimination Performed On Left Part of AND/Conjunction.
        if(isSubtreeSame(root, childNode->left)){
            return true;
        }
        else{ 
            //AND Elimination Performed On Right Part of AND/Conjunction.
            if(isSubtreeSame(root, childNode->right)){
                return true;
            }
            return false;
        }
    }

    if(justification=="|I"){
        //OR Introduction Rule:
        FirstOrderTree child;
        std::list<FirstOrderTree>::const_iterator itr = childStatements.begin();
        child = *itr;
        FirstOrderNode* root = mainStatement.getHeadFirstOrderNode();
        FirstOrderNode* childNode = child.getHeadFirstOrderNode();

        //By Our Definition, OR Introduction Rule, If Not Exactly 1 Child, Return False.
        if(childStatements.size() != 1){
            return false;
        }

        //If Root NULL, Cannot Be Valid.
        if(!root){
            return false;
        }

        //Assert Dealing w/ OR Node.
        if(root->value != "|"){
            return false;
        }
        
        if(isSubtreeSame(root->left, childNode)){
            //Case 1: Root Left Subtree == Child Subtree.
            return true;
        }
        else if (isSubtreeSame(root->right, childNode)){
            //Case 2: Root Right Subtree == Child Subtree.
            return true;
        }
        return false;
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
        FirstOrderNode* root = mainStatement.getHeadFirstOrderNode();
        FirstOrderNode* oneNode = child1.getHeadFirstOrderNode();
        FirstOrderNode* twoNode = child2.getHeadFirstOrderNode();

        if(isSubtreeSame(root->left, oneNode)){
            //Case 1: Root Left Subtree == Child Subtree.
            return true;
        }
        else{
            //Case 2: Root Right Subtree == Child Subtree.
            return true;
        }
        return false;
    }
	return false; 

}

//Private Helper Function:
//Invoked By AND Introduction Rule:
//Basic Implementation of Comparing Two Trees w/ Same Tree Values:
bool isSubtreeSame(FirstOrderNode* root, FirstOrderNode* same){
    //Base True Case:
    if(!root && !same){
        return true;
    }
    //Base False Case:
    else if((!root && same) || (root && !same)){
        return false;
    }
    //Check Current Values Are Same. 
    //If Not, Return False.
    if(root->value != same->value || root->negation != same->negation){
        return false;
    }
    //Recursive Step.
    return isSubtreeSame(root->left, same->left) && isSubtreeSame(root->right, same->right);

}