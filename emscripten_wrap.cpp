#include "statementevaluator.h"
#include "LogicGate.h"
#include "expressionparser.h"
#include "Tree.h"
#include <iostream>
#include <string>
#include <sstream>

#include <emscripten/bind.h>

using namespace emscripten;


std::string Logic(std::string input) {
    StatementParser testStatement(input);

    std::stringstream stream;
    testStatement.print(stream);

    return stream.str();
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("Logic", &Logic);
}