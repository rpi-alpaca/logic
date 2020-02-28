#include "FirstOrderTree.h"
#include <iostream>
#include <string>
// test print

// test print trees


int main(int argc, char* argv[]){
    FirstOrderTree andExpr("(A) & (B)");
    andExpr.print();
    std::cout << "\n\n";
    andExpr.printTree();
    std::cout << "\n\n";
    std::cout << "\n\n";

    FirstOrderTree orExpr("(A) | (B)");
    orExpr.print();
    std::cout << "\n\n";
    orExpr.printTree();
    std::cout << "\n\n";
    std::cout << "\n\n";

    FirstOrderTree notExpr("~(A)");
    notExpr.print();
    std::cout << "\n\n";
    notExpr.printTree();
    std::cout << "\n\n";
    std::cout << "\n\n";

    FirstOrderTree andOrExpr("((A) & (B)) | (C)");
    andOrExpr.print();
    std::cout << "\n\n";
    andOrExpr.printTree();
    std::cout << "\n\n";
    std::cout << "\n\n";

    FirstOrderTree andOrNotExpr("~(((A) & (B)) | (C))");
    andOrNotExpr.print();
    std::cout << "\n\n";
    andOrNotExpr.printTree();
    std::cout << "\n\n";
    std::cout << "\n\n";

    FirstOrderTree implicExpr("(A) > (B)");
    implicExpr.print();
    std::cout << "\n\n";
    implicExpr.printTree();
    std::cout << "\n\n";
    std::cout << "\n\n";

    FirstOrderTree advImplicExpr("((A) & (B)) > (C)");
    advImplicExpr.print();
    std::cout << "\n\n";
    advImplicExpr.printTree();
    std::cout << "\n\n";
    std::cout << "\n\n";

    FirstOrderTree biconExpr("(A) = (B)");
    biconExpr.print();
    std::cout << "\n\n";
    biconExpr.printTree();
    std::cout << "\n\n";
    std::cout << "\n\n";

    FirstOrderTree advBiconExpr("((A) & (B)) = (C)");
    advBiconExpr.print();
    std::cout << "\n\n";
    advBiconExpr.printTree();

}