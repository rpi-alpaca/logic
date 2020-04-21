#include <iostream>
#include <string>
#include "ProofChecker.h"
#include "FirstOrderTree.h"
using namespace std;

int main(int argc, char* argv[]){
    //Test Cases For AND Introduction Rule:
    cout << "Test Suite For AND Introduction Rule: " << endl;
    ProofChecker expression = ProofChecker("A & B");
    expression.addChild(FirstOrderTree("A"));
    expression.addChild(FirstOrderTree("B"));
    expression.changeJustification("&I");
    cout << "Expected Output: 1" << endl;
    std::cout << "Result of AND Introduction Rule Test #1: " << expression.isValid() << endl;
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

    // Test AND Elim
    expression = ProofChecker("A");
    expression.addChild(FirstOrderTree("A & B"));
    expression.changeJustification("&E");
    std::cout << "Result of AND Eliminiation Rule Test #1: " << expression.isValid() << endl;
    cout << endl;

    // Test OR Intro
    expression = ProofChecker("A | B");
    expression.addChild(FirstOrderTree("A"));
    expression.changeJustification("|I");
    std::cout << "Result of OR Introduction Rule Test #1: " << expression.isValid() << endl;
    cout << endl;

    // OR Elim

    // Test NOT Intro
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

    // Test NOT Elim
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

    // IF Intro cannot be tested yet, as we have not figured out how to represent
    // subproofs

    // Test IF Elim
    expression = ProofChecker("B");
    expression.addChild(FirstOrderTree("A"));
    expression.addChild(FirstOrderTree("A > B"));
    expression.changeJustification(">E");
    std::cout << "Result of IF Elimination Rule Test #1: " << expression.isValid() << endl;
    expression.addChild(FirstOrderTree("A > B"));
    expression.addChild(FirstOrderTree("A"));
    std::cout << "Result of IF Elimination Rule Test #2: " << expression.isValid() << endl;
    cout << endl;

    // Test IFF Intro
    expression = ProofChecker("A = B");
    expression.addChild(FirstOrderTree("A > B"));
    expression.addChild(FirstOrderTree("B > A"));
    expression.changeJustification("=I");
    std::cout << "Result of IFF Introduction Rule Test #1: " << expression.isValid() << endl;
    cout << endl;

    // Test IFF Elim
    expression = ProofChecker("A");
    expression.addChild(FirstOrderTree("A = B"));
    expression.addChild(FirstOrderTree("=E"));
    std::cout << "Result of IFF Introduction Rule Test #2: " << expression.isValid() << endl;
    cout << endl;

    // Tests for quantifiers have not yet been written, as it has not been decided
    // what the symbols for forall expression exists will be; thus, writing tests for these
    // is impossible.
}
