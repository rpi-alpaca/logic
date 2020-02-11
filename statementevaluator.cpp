
#include "statementevaluator.h"

/* evaluateStatement accepts a StatementParser (which represents a logical statement) and a vector of 
   <variablename, boolean> values. The vector of pairs represents the boolean values assigned to each 
   variable.

   The function creates a hash table using the vector passed in and calls evaluateBranch to evaluate the statement
   with those values. 
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


/* printTruthTable accepts a StatementParser (logical statement) and a vector containing all the variable names
   in that StatementParser.

   It prints out a truth table containing the evaluation of the statement for all possible boolean assignments
   for the variables.
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

//PRIVATE: Helper function that prints all strings in an array formatted using iomanip
void StatementEvaluator::printVariableHeaders(const std::vector<std::string>& variableNames, int maxStringSize) const{
	for (const auto & variableName : variableNames) {
		std::cout << std::setw(maxStringSize) << std::left << variableName << " ";
	}
	std::cout << std::endl;
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


/* areLogicallyEquivalent
 * Requires: s1, s2 are non-null
 * Effects: Nothing
 * Returns: True if s1, s2 are logically equivalent. Otherwise, false.
 */
bool StatementEvaluator::areLogicallyEquivalent(const StatementParser& s1, const StatementParser& s2) const {

}


/* evaluateBranch is a private function that takes a node to the head of a StatementParser and evaluates the
   statement for the variable-boolean assignment inside of variableValues. 
 */
bool StatementEvaluator::evaluateBranch(StatementNode* p, const std::unordered_map<std::string, bool>& variableValues) const {
	bool notDetected = true;
	//Node is a not statement: Negates the value that would have been returned
	if (!p->negation) {
		notDetected = false;
	}

	//Node is not an operation (variable): returns the value of that variable (found in variableValues)
	if (p -> opType == 'v' && !notDetected) {
		return variableValues.find(p -> value)->second;
	} else if (p -> opType == 'v' && notDetected) {
		return !variableValues.find(p -> value)->second;
	}

	//Node is an operation: Looks for the appropriate operation in functionMap and recurses.
	else if (!notDetected) {
		std::function<bool(bool,bool)> operation = functionMap.find(p -> opType) -> second;
		return operation(evaluateBranch(p -> left, variableValues), evaluateBranch(p-> right, variableValues));
	} else {
		std::function<bool(bool,bool)> operation = functionMap.find(p -> opType) -> second;
		return !operation(evaluateBranch(p -> left, variableValues), evaluateBranch(p-> right, variableValues));
	}

	//DEFAULT return value: Shouldn't reach here.
	return true;
}
