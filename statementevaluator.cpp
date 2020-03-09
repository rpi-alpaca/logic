
#include "statementevaluator.h"
#include <iostream>
#include <algorithm>
using namespace std;

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


/* Helper function that only receives a StatmentParser and 
   automatically retrieves the variable names on its own.

   The full implementation of printTruthTable is called within
   this function.
 */
void StatementEvaluator::printTruthTable(const StatementParser& s) const {
	printTruthTable(s, s.getVariableNames());
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
		variableTruthValues.emplace_back(variableName, false);
		if (maxStringSize < variableName.size())
			maxStringSize = variableName.size();
	}

	// In the case that the variable headers are 
	maxStringSize = (maxStringSize < 5) ? 5 : maxStringSize;

	printVariableHeaders(variableNames, maxStringSize);

	recurseDownArray(s, variableTruthValues, 0, maxStringSize);
}

/* printVariableHeaders is a private function that prints all strings in a vector formatted using iomanip
   By default, each column is of size maxStringSize */
void StatementEvaluator::printVariableHeaders(const std::vector<std::string>& variableNames, int maxStringSize) const{
	for (const auto & variableName : variableNames) {
		std::cout << std::setw(maxStringSize) << std::left << variableName << "  ";
	}
	std::cout << "|  Result" << std::endl;
}

/* recurseDownArray is a private function which accepts a StatementParser and a vector with <string, bool> pairs, 
   representing variable-truth value pairs. When called, the bool argument of these pairs should be true.

   It uses recursion to print out all possible boolean assignments, formatted with iomanip with columns of size
   maxStringSize. 
 */
void StatementEvaluator::recurseDownArray(const StatementParser& s, std::vector<std::pair<std::string, bool> >& variableTruthValues, unsigned int index, unsigned int maxStringSize) const {
	if (index == variableTruthValues.size()) {
		for (auto & variableTruthValue : variableTruthValues) {
			std::cout << std::setw(maxStringSize) << std::boolalpha << std::left << variableTruthValue.second << "  ";
		}
		std::cout << "|  " <<  evaluateStatement(s, variableTruthValues) << std::endl;
	} else {
		recurseDownArray(s, variableTruthValues, index + 1, maxStringSize);
		variableTruthValues[index].second = true;
		recurseDownArray(s, variableTruthValues, index + 1, maxStringSize);
		variableTruthValues[index].second = false;
	}
}



bool StatementEvaluator::areLogicallyEquivalent(const StatementParser& s1, const StatementParser& s2) const {
	// Set up Variable Truth Values for s1
	std::vector<std::pair<std::string, bool> > s1Variables;
	for (const auto & variableName : s1.getVariableNames()) {
		s1Variables.emplace_back(variableName, false);
	}
	sort(s1Variables.begin(), s1Variables.end(), sortByVariableName);

	// Set up Variable Truth Values for s2
	std::vector<std::pair<std::string, bool> > s2Variables;
	for (const auto & variableName : s2.getVariableNames()) {
		s2Variables.emplace_back(variableName, false);
	}
	sort(s2Variables.begin(), s2Variables.end(), sortByVariableName);

	// Find the variables that only appear in one of the equations
	std::vector<std::string> difference;
	std::vector<std::pair<std::string, bool> >::const_iterator s1_itr = s1Variables.begin();
	std::vector<std::pair<std::string, bool> >::const_iterator s2_itr = s2Variables.begin();

	while(s1_itr != s1Variables.end() || s2_itr != s2Variables.end()) {
		if(s1_itr->first == s2_itr->first) {
			++s1_itr;
			++s2_itr;
		} else if(s1_itr != s1Variables.end()) {
			difference.emplace_back(s1_itr->first);
			++s1_itr;
		} else {
			difference.emplace_back(s2_itr->first);
			++s2_itr;
		}
	}

	return areLogicallyEquivalent(s1, s2, s1Variables, s2Variables, 0, 0, difference, 0);
}

/* areLogicallyEquivalent
 * Requires: s1, s2 are non-null
 * Effects: Nothing
 * Returns: True if s1, s2 are logically equivalent. Otherwise, false.
 */
bool StatementEvaluator::areLogicallyEquivalent(const StatementParser& s1, const StatementParser& s2, 
	std::vector<std::pair<std::string, bool> >& s1Variables, std::vector<std::pair<std::string, bool> >& s2Variables, 
	unsigned int s1Index, unsigned int s2Index, const vector<string>& difference, unsigned int dIndex) const {
	
	// Both statments have variables left to set
	if(s1Index < s1Variables.size() && s2Index < s2Variables.size() && s1Variables[s1Index].first == s2Variables[s2Index].first){
		bool outcome_1 = areLogicallyEquivalent(s1, s2, s1Variables, s2Variables, s1Index + 1, s2Index + 1, difference, dIndex);
		s1Variables[s1Index].second = true;
		s2Variables[s2Index].second = true;
		if(!outcome_1) {
			return false;
		}

		bool outcome_2 = areLogicallyEquivalent(s1, s2, s1Variables, s2Variables, s1Index + 1, s2Index + 1, difference, dIndex);
		s1Variables[s1Index].second = false;
		s2Variables[s2Index].second = false;
		return outcome_2;
	} 

	// s1 still has variables left to set
	else if(s1Index < s1Variables.size() && dIndex < difference.size() && s1Variables[s1Index].first == difference[dIndex]) {
		bool outcome_1 = areLogicallyEquivalent(s1, s2, s1Variables, s2Variables, s1Index + 1, s2Index, difference, dIndex + 1);
		s1Variables[s1Index].second = true;
		if(!outcome_1) {
			return false;
		}

		bool outcome_2 = areLogicallyEquivalent(s1, s2, s1Variables, s2Variables, s1Index + 1, s2Index, difference, dIndex + 1);
		s1Variables[s1Index].second = false;
		return outcome_2;
	}

	// s2 still has variables left to set
	else if(s2Index < s2Variables.size() && dIndex < difference.size() && s2Variables[s2Index].first == difference[dIndex]) {
		bool outcome_1 = areLogicallyEquivalent(s1, s2, s1Variables, s2Variables, s1Index, s2Index + 1, difference, dIndex + 1);
		s2Variables[s2Index].second = true;
		if(!outcome_1) {
			return false;
		}

		bool outcome_2 = areLogicallyEquivalent(s1, s2, s1Variables, s2Variables, s1Index, s2Index + 1, difference, dIndex + 1);
		s2Variables[s2Index].second = false;
		return outcome_2;
	}

	// All variables have been set
	else {
		return evaluateStatement(s1, s1Variables) == evaluateStatement(s2, s2Variables);
	}
}



/* evaluateBranch is a private function that takes a node to the head of a StatementParser and evaluates the
   statement for the variable-boolean assignment inside of variableValues. 
 */
bool StatementEvaluator::evaluateBranch(StatementNode* p, const std::unordered_map<std::string, bool>& variableValues) const {
	bool notDetected = true;
	// Node is a not statement: Negates the value that would have been returned
	if (!p->negation) {
		notDetected = false;
	}

	// Node is not an operation (variable): returns the value of that variable (found in variableValues)
	if (p -> opType == 'v' && !notDetected) {
		return variableValues.find(p -> value)->second;
	} else if (p -> opType == 'v' && notDetected) {
		return !variableValues.find(p -> value)->second;
	}

	// Node is an operation: Looks for the appropriate operation in functionMap and recurses.
	else if (!notDetected) {
		// unordered_map<char, std::function<bool (bool, bool)>>::const_iterator itr = functionMap.find(p -> opType);
		// if(itr == functionMap.end()){
		// 	cout << "Not Found" << functionMap.size() <<p -> opType << endl;
		// 	return false;
		// }
		std::function<bool(bool,bool)> operation = functionMap.find(p -> opType) -> second;
		return operation(evaluateBranch(p->left, variableValues), evaluateBranch(p-> right, variableValues));
	} else {
		std::function<bool(bool,bool)> operation = functionMap.find(p -> opType) -> second;
		return !operation(evaluateBranch(p -> left, variableValues), evaluateBranch(p-> right, variableValues));
	}

	// DEFAULT return value: Shouldn't reach here.
	return true;
}
