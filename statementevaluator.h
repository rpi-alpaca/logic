
#ifndef _STATEMENT_EVALUATOR_H_
#define _STATEMENT_EVALUATOR_H_

#include "Tree.h"
#include <functional>
#include <unordered_map>
#include <vector>
#include <iomanip>

/* This class contains functions to print and evaluate a StatementParser that is passed in. 
   The only member data of the class includes a hash table to find a corresponding operator quickly
   although this is largely unnecessary. 

   evaluateStatement evaluates the value of the StatementParser for a list of pairs of <variable_name, boolean>.
   printTruthTable prints the evaluation of the StatementParser for every possible boolean assignment to its variables.
*/

class StatementEvaluator {
	public:
		bool evaluateStatement(const StatementParser& s, const std::vector<std::pair<std::string, bool> >& variableTruthValues) const;
		void printTruthTable(const StatementParser& s) const;
		void printTruthTable(const StatementParser& s, const std::vector<std::string>& variableNames) const;
		bool areLogicallyEquivalent(const StatementParser& s1, const StatementParser& s2) const;
		bool areLogicallyEquivalent(const StatementParser& s1, const StatementParser& s2, 
	std::vector<std::pair<std::string, bool> >& s1Variables, std::vector<std::pair<std::string, bool> >& s2Variables, 
	unsigned int s1Index, unsigned int s2Index, const vector<string>& difference, unsigned int dIndex) const;

	private:
		// Mapping of operation characters to the corresponding functions.
		std::unordered_map<char, std::function<bool (bool, bool)> > functionMap = {
			{'|', [](bool p, bool q) {return p || q;}},
			{'&', [](bool p, bool q) {return p && q;}},
			{'@', [](bool p, bool q) {return p xor q;}}
		};

		bool evaluateBranch(StatementNode* p, const std::unordered_map<std::string, bool>& variableValues) const;
		void recurseDownArray(const StatementParser& s, std::vector<std::pair<std::string, bool> >& variableTruthValues, unsigned int index, unsigned int maxStringSize) const;
		void printVariableHeaders(const std::vector<std::string>& variableNames, int maxStringSize) const;
};

#endif
