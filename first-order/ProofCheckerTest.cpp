#include <iostream>
#include <string>
#include "ProofChecker.h"
#include "FirstOrderTree.h"
using namespace std;

int main(int argc, char* argv[]){
    cout << "Start of ProofCheckerTest.cpp Testing Suite." << endl;
    cout << endl;
    //Test Cases For AND Introduction Rule:
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Test Suite For AND Introduction Rule: " << endl;
    ProofChecker expression = ProofChecker("A & B");
    expression.addChild(FirstOrderTree("A"));
    expression.addChild(FirstOrderTree("B"));
    expression.changeJustification("&I");
    cout << "Expected Output: 1" << endl;
    std::cout << "Result of AND Introduction Rule Test #1A: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("A & B");
    expression.addChild(FirstOrderTree("B"));
    expression.addChild(FirstOrderTree("A"));
    expression.changeJustification("&I");
    cout << "Expected Output: 1" << endl;
    std::cout << "Result of AND Introduction Rule Test #1B: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("~A & ~B");
    expression.addChild(FirstOrderTree("A"));
    expression.addChild(FirstOrderTree("B"));
    expression.changeJustification("&I");
    cout << "Expected Output: 0" << endl;
    std::cout << "Result of AND Introduction Rule Test #2: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("~A & ~B");
    expression.addChild(FirstOrderTree("~A"));
    expression.addChild(FirstOrderTree("~B"));
    expression.changeJustification("&I");
    cout << "Expected Output: 1" << endl;
    std::cout << "Result of AND Introduction Rule Test #3: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("~A & ~A");
    expression.addChild(FirstOrderTree("~A"));
    expression.addChild(FirstOrderTree("~A"));
    expression.changeJustification("&I");
    cout << "Expected Output: 1" << endl;
    std::cout << "Result of AND Introduction Rule Test #4: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("~A & A");
    expression.addChild(FirstOrderTree("~A"));
    expression.addChild(FirstOrderTree("A"));
    expression.changeJustification("&I");
    cout << "Expected Output: 1" << endl;
    std::cout << "Result of AND Introduction Rule Test #5: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("(A & B) & (C & D)");
    expression.addChild(FirstOrderTree("(A & B)"));
    expression.addChild(FirstOrderTree("(C & D)"));
    expression.changeJustification("&I");
    cout << "Expected Output: 1" << endl;
    std::cout << "Result of AND Introduction Rule Test #6: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("(A & B) & (C | D)");
    expression.addChild(FirstOrderTree("(A & B)"));
    expression.addChild(FirstOrderTree("(C | D)"));
    expression.changeJustification("&I");
    cout << "Expected Output: 1" << endl;
    std::cout << "Result of AND Introduction Rule Test #7: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("(A = (B > ~D)) & (C | D)");
    expression.addChild(FirstOrderTree("(A = (B > ~D))"));
    expression.addChild(FirstOrderTree("(C | D)"));
    expression.changeJustification("&I");
    cout << "Expected Output: 1" << endl;
    std::cout << "Result of AND Introduction Rule Test #8: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("(A & B) | (C & D)");
    expression.addChild(FirstOrderTree("(A & B)"));
    expression.addChild(FirstOrderTree("(C & D)"));
    expression.changeJustification("&I");
    cout << "Expected Output: 0" << endl;
    std::cout << "Result of AND Introduction Rule Test #9: " << expression.isValid() << endl;
    cout << endl;

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;

    //Test Cases For AND Elimination Rule:
    cout << "Test Suite For AND Elimination Rule: " << endl;
    expression = ProofChecker("A");
    expression.addChild(FirstOrderTree("A & B"));
    expression.changeJustification("&E");
    std::cout << "Result of AND Eliminiation Rule Test #1: " << expression.isValid() << endl;
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;

    //Test Cases For OR Introduction Rule:
    cout << "Test Suite For OR Introduction Rule: " << endl;
    expression = ProofChecker("A | B");
    expression.addChild(FirstOrderTree("A"));
    expression.changeJustification("|I");
    std::cout << "Result of OR Introduction Rule Test #1: " << expression.isValid() << endl;
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;

    //OR Elimination Rule == NOT YET IMPLEMENTED.

    //Test Cases For NOT Introduction Rule:
    cout << "Test Suite For NOT Introduction Rule: " << endl;
    expression = ProofChecker("~A");
    expression.addChild(FirstOrderTree("A"));
    expression.addChild(FirstOrderTree("B"));
    expression.addChild(FirstOrderTree("~B"));
    expression.changeJustification("~I");
    std::cout << "Result of NOT Introduction Rule Test #1: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("~A");
    expression.addChild(FirstOrderTree("B"));
    expression.addChild(FirstOrderTree("A"));
    expression.addChild(FirstOrderTree("~B"));
    expression.changeJustification("~I");
    std::cout << "Result of NOT Introduction Rule Test #2: " << expression.isValid() << endl;
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;

    //Test Cases For NOT Elimination Rule: 
    cout << "Test Suite For NOT Elimination Rule: " << endl;
    expression = ProofChecker("C");
    expression.addChild(FirstOrderTree("~C"));
    expression.addChild(FirstOrderTree("~B"));
    expression.addChild(FirstOrderTree("B"));
    expression.changeJustification("~E");
    std::cout << "Result of NOT Elimination Rule Test #1: " << expression.isValid() << endl;
    cout << endl;

    expression = ProofChecker("C");
    expression.addChild(FirstOrderTree("~B"));
    expression.addChild(FirstOrderTree("~C"));
    expression.addChild(FirstOrderTree("B"));
    expression.changeJustification("~E");
    std::cout << "Result of NOT Elimination Rule Test #2: " << expression.isValid() << endl;
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;

    //IF Introduction Rule cannot be tested yet, 
    //  as we have not figured out how to represent subproofs.

    //Test Cases For IF Elimination Rule:
    cout << "Test Suite For IF Elimination Rule: " << endl;
    expression = ProofChecker("B");
    expression.addChild(FirstOrderTree("A"));
    expression.addChild(FirstOrderTree("A > B"));
    expression.changeJustification(">E");
    std::cout << "Result of IF Elimination Rule Test #1: " << expression.isValid() << endl;
    expression.addChild(FirstOrderTree("A > B"));
    expression.addChild(FirstOrderTree("A"));
    std::cout << "Result of IF Elimination Rule Test #2: " << expression.isValid() << endl;
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;

    //Test Cases For IFF Introduction Rule:
    cout << "Test Suite For IFF Introduction Rule: " << endl;
    expression = ProofChecker("A = B");
    expression.addChild(FirstOrderTree("A > B"));
    expression.addChild(FirstOrderTree("B > A"));
    expression.changeJustification("=I");
    std::cout << "Result of IFF Introduction Rule Test #1: " << expression.isValid() << endl;
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;

    //Test Cases For IFF Elimination Rule:
    cout << "Test Suite For IFF Elimination Rule: " << endl;
    expression = ProofChecker("A");
    expression.addChild(FirstOrderTree("A = B"));
    expression.addChild(FirstOrderTree("B"));
    expression.changeJustification("=E");
    std::cout << "Result of IFF Elimination Rule Test #1: " << expression.isValid() << endl;
    cout << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << "Termination of ProofCheckTest.cpp Testing Suite." << endl;
    // Tests for quantifiers have not yet been written, as it has not been decided
    // what the symbols for forall expression exists will be; thus, writing tests for these
    // is impossible.
}
