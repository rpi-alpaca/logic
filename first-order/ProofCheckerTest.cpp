#include <iostream>
#include <string>
#include "ProofChecker.h"
#include "FirstOrderTree.h"
using namespace std;

int main(int argc, char* argv[]){
    // Test AND Intro
    ProofChecker* expression = new ProofChecker("A & B");
    expression->addChild(FirstOrderTree("A"));
    expression->addChild(FirstOrderTree("B"));
    expression->changeJustification("&I");
    std::cout << "Result of AND Intro (A, B) => A & B: " << expression->isValid() << endl;

    // Test AND Elim
    expression = new ProofChecker("A");
    expression->addChild(FirstOrderTree("A & B"));
    expression->changeJustification("&E");
    std::cout << "Result of AND Elim (A & B) => A: " << expression->isValid() << endl;

    // Test OR Intro
    expression = new ProofChecker("A | B");
    expression->addChild(FirstOrderTree("A"));
    expression->changeJustification("|I");
    std::cout << "Result of OR Intro (A) => A | B: " << expression->isValid() << endl;

    // OR Elim and NOT Intro cannot be tested yet, as we have not figured out how to represent
    // subproofs

    // Test NOT Elim
    expression = new ProofChecker("A");
    expression->addChild(FirstOrderTree("~~A"));
    expression->changeJustification("~E");
    std::cout << "Result of expression Intro (~~A) => A: " << expression->isValid() << endl;

    // IF Intro cannot be tested yet, as we have not figured out how to represent
    // subproofs

    // Test IF Elim
    expression = new ProofChecker("A > B");
    expression->addChild(FirstOrderTree("A"));
    expression->changeJustification(">E");
    std::cout << "Result of expression Intro (A > B) => B: " << expression->isValid() << endl;

    // Test IFF Intro
    expression = new ProofChecker("A = B");
    expression->addChild(FirstOrderTree("A > B"));
    expression->addChild(FirstOrderTree("B > A"));
    expression->changeJustification("=I");
    std::cout << "Result of expression Intro (A > B, B > A) => A = B: " << expression->isValid() << endl;

    // Test IFF Elim
    expression = new ProofChecker("A");
    expression->addChild(FirstOrderTree("A = B"));
    expression->addChild(FirstOrderTree("=E"));
    std::cout << "Result of expression Intro (A = B, B) => A: " << expression->isValid() << endl;

    // Tests for quantifiers have not yet been written, as it has not been decided
    // what the symbols for forall expression exists will be; thus, writing tests for these
    // is impossible.
}
