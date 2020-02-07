
#include "statementevaluator.h"

/* evaluateStatement
 * Requires: s is a valid StatementParser and is created correctly
 *			 variableTruthValues contains a vector of pairs where the first value is variable name and second is boolean 
 * Returns: A boolean indicating whether the statement is true given the provided variable boolean values
 */
bool StatementEvaluator::evaluateStatement(const StatementParser& s, const std::vector<std::pair<std::string, bool> >& variableTruthValues) const {
	//Creates a hash table from variable names to boolean value
	std::unordered_map<std::string, bool> variableValues;
	for (const auto & variableTruthValue : variableTruthValues) {
		variableValues[variableTruthValue.first] = variableTruthValue.second;
	}

	bool isTrue = evaluateBranch(s.head, variableValues);
	return isTrue;
}


/* printTruthTable
 * Requires: s is a valid StatementParser and is created correctly, variableNames is a vector containing all of the variable names in s
 * Effects: Prints a truth table
 * Returns: Nothing
 */
void StatementEvaluator::printTruthTable(const StatementParser& s, const std::vector<std::string>& variableNames) const {
	unsigned int maxStringSize = 0;
	std::vector<std::pair<std::string, bool> > variableTruthValues;
	for (const auto & variableName : variableNames) {
		variableTruthValues.emplace_back(variableName, true);
		if (maxStringSize < variableName.size())
			maxStringSize = variableName.size();
	}

	printVariableHeaders(variableNames, maxStringSize);

	recurseDownArray(s, variableTruthValues, 0, maxStringSize);
}


/* areLogicallyEquivalent
 * Requires: s1, s2 are non-null
 * Effects: Nothing
 * Returns: True if s1, s2 are logically equivalent. Otherwise, false.
 */
bool StatementEvaluator::areLogicallyEquivalent(const StatementParser& s1, const StatementParser& s2) const {

}

//PRIVATE: Helper function for evaluateStatement
/*bool StatementEvaluator::evaluateBranch(StatementNode* p, const std::unordered_map<std::string, bool>& variableValues) const{
	//Node is not an operation (variable)
	if(p -> opType == 'v'){
		return variableValues.find(p -> value) -> second;
	} 
	//Node is a not statement
	else if(p -> opType == '~'){
		return !evaluateBranch(p -> left, variableValues);
	}
	//Node is a non-not operation
	else{
		std::function<bool(bool,bool)> operation = functionMap.find(p -> opType) -> second;
		return operation(evaluateBranch(p -> left, variableValues), evaluateBranch(p-> right, variableValues));
	}
	return true;
}*/


//PRIVATE: Helper function for evaluateStatement
bool StatementEvaluator::evaluateBranch(StatementNode* p, const std::unordered_map<std::string, bool>& variableValues) const {
	bool notDetected = true;
	//Node is a not statement
	if (!p->negation) {
		notDetected = false;
	}

	//Node is not an operation (variable)
	if (p -> opType == 'v' && !notDetected) {
		return variableValues.find(p -> value)->second;
	} else if (p -> opType == 'v' && notDetected) {
		return !variableValues.find(p -> value)->second;
	}
	//Node is an operation
	else if (!notDetected) {
		std::function<bool(bool,bool)> operation = functionMap.find(p -> opType) -> second;
		return operation(evaluateBranch(p -> left, variableValues), evaluateBranch(p-> right, variableValues));
	} else {
		std::function<bool(bool,bool)> operation = functionMap.find(p -> opType) -> second;
		return !operation(evaluateBranch(p -> left, variableValues), evaluateBranch(p-> right, variableValues));
	}
	return true;
}


//PRIVATE: Helper function for printTruthTable
void StatementEvaluator::recurseDownArray(const StatementParser& s, std::vector<std::pair<std::string, bool> >& variableTruthValues, unsigned int index, unsigned int maxStringSize) const {
	if (index == variableTruthValues.size()) {
		for (auto & variableTruthValue : variableTruthValues) {
			std::cout << std::setw(maxStringSize) << std::boolalpha << std::left << variableTruthValue.second << " ";
		}
		std::cout << evaluateStatement(s, variableTruthValues) << std::endl;
	} else {
		recurseDownArray(s, variableTruthValues, index + 1, maxStringSize);
		variableTruthValues[index].second = false;
		recurseDownArray(s, variableTruthValues, index + 1, maxStringSize);
		variableTruthValues[index].second = true;
	}
}

//PRIVATE: Helper function that prints all strings in an array formatted using iomanip
void StatementEvaluator::printVariableHeaders(const std::vector<std::string>& variableNames, int maxStringSize) const{
	for (const auto & variableName : variableNames) {
		std::cout << std::setw(maxStringSize) << std::left << variableName << " ";
	}
	std::cout << std::endl;
}
