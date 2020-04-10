//LogicGate.cpp

#include "LogicGate.h"


void LogicGate::asciiDraw() {
    std::ios_base::fmtflags f(std::cout.flags());

	std::cout << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << "This is a asciiDraw" << std::endl;
	std::cout << std::endl;
	if (initStatements.empty())
	    std::cout << "No Statements!" << std::endl;

    std::cout << std::boolalpha;
	for (auto initStatement : initStatements) {
		std::cout << initStatement.first << " " << initStatement.second << std::endl;
	}

	std::cout << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << std::endl;
    std::cout.flags(f);
}

//Default of all statements is true;
bool LogicGate::addStatement(char addState) {
	return initStatements.insert(std::make_pair(addState, true)).second;
}

bool LogicGate::removeStatement(char removeState) {
	return initStatements.erase(removeState);
}

//Changing a state too itself isn't much of a big problem so for now will ignore
bool LogicGate::changeOnOff(char stateName, bool newSwitch) {
	std::unordered_map<char,bool>::iterator got = initStatements.find(stateName);
	if (containsState(stateName)) {
		std::cout << "Error Statement Does Not Exist" << std::endl;
		return false;	
	} 
	got->second = newSwitch;
	return true;
}

void LogicGate::clearStates() {
	initStatements.clear();
}

//For now wil
bool LogicGate::containsState(char checkState) {
	std::unordered_map<char, bool>::const_iterator got = initStatements.find(checkState);
	return (got == initStatements.end());
}

bool LogicGate::addOperator(__attribute__((unused)) char stateOne, __attribute__((unused)) char stateTwo, __attribute__((unused)) char opAdd) {
	return false;
}
