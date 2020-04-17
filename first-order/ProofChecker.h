#ifndef _PROOFCHECKER_H_
#define _PROOFCHECKER_H_

#include <iostream>
#include <list>
#include <string>
#include "FirstOrderTree.h"
using namespace std;

class ProofChecker {
public:
	ProofChecker();
	ProofChecker(const string& mainStatementString);

	void changeJustification(const string& just);
	void changeMainStatement(const string& mainStatementString);
	void addChild(const FirstOrderTree& child);

	bool isValid() const;
	
private:
	FirstOrderTree* mainStatement;
	std::list<FirstOrderTree*> childStatements;
	std::string justification;
};

#endif
