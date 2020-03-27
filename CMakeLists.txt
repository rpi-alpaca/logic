cmake_minimum_required(VERSION 3.10)
project(logic)

set(CMAKE_CXX_STANDARD 14)

set(expressionparser_files
        expressionparser.cpp
        expressionparser.h)

add_executable(logic
        ${expressionparser_files}
        LogicGate.cpp
        LogicGate.h
        main.cpp
        statement.cpp
        statement.h
        statementevaluator.cpp
        statementevaluator.h
        Tree.cpp
        Tree.h)

add_executable(logic-test
        ${expressionparser_files}
        LogicTest.cpp
        LogicGate.cpp
        LogicGate.h
        main.cpp
        statement.cpp
        statement.h
        statementevaluator.cpp
        statementevaluator.h
        Tree.cpp
        Tree.h)
