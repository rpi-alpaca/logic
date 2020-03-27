#ifndef _PROOFCHECKER_H_
#define _PROOFCHECKER_H_

#include <iostream>
#include <list>
#include <string>
#include "FirstOrderTree.h"

class ProofChecker {
public:
	ProofChecker();
	ProofChecker(std::string mainStatement);

	void changeJustification(std::string just);
	void addChild(const FirstOrderTree& child);

	bool isValid() const;
private:
	FirstOrderTree mainStatement;
	std::list<FirstOrderTree*> childStatements;
	std::string justification;
}

#endif
