#include "FirstOrderTree.h"
#include <iostream>
#include <string>
// test print

// test print trees


int main(int argc, char* argv[]){
    FirstOrderTree andOrs = new FirstOrderTree("(A) & (B)");
    andOrs.print();
    andOrs.printTree();
}