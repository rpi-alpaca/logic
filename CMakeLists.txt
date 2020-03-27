cmake_minimum_required(VERSION 3.10)
project(logic)

set(CMAKE_CXX_STANDARD 14)

add_executable(logic
        expressionparser
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
        expressionparser
	LogicGate.cpp
        LogicGate.h
        LogicTest.cpp
        statement.cpp
        statement.h
        statementevaluator.cpp
        statementevaluator.h
        Tree.cpp
        Tree.h)

add_executable(expressionparser
        expressionparser.cpp
        expressionparser.h)
