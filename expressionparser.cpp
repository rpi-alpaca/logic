#include <cctype>
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <stdlib.h>
#include "expressionparser.h"
using namespace std;

//Fill Constructur In With Any Important Fields To Be Initialized.
//As of right now, we are not making use of any Private Fields.
ExpressionParser::ExpressionParser(){

}

//Determines Whether The Current Input Character = Valid Operator.
bool ExpressionParser::isOperator(char currentOperator){
    return (currentOperator == '&' 
            || currentOperator == '|' 
            || currentOperator == '~'
            || currentOperator == '='
            || currentOperator == '>');
}

//Output The Logical Associativity For Given Operator.
//Default = 'L' Indicating Left Associativity.
char ExpressionParser::getAssociativity(char currentOperator){
    switch(currentOperator){
        case '&':
            return 'L';
        case '|':
            return 'L';
        case '=':
            return 'L';
        case '>':
            return 'L';
        case '~':
            return 'R';  
        default:
            return 'L';
    }
}

//Return The Precedence For Given Operator.
//Used By Shunting Yard Algorithm To Determine Values To Pop From Operator Stack.
//Default = -1.
int ExpressionParser::getPrecedence(char currentOperator){
    switch(currentOperator){
        case '&':
            return 2;
        case '|':
            return 1;
        case '=':
            return 0;
        case '>':
            return 0;
        case '~':
            return 4;
        default:
            return -1;
    }
}

/** Returns true if the current operator is able to be
 *  generalized and false otherwise.
 *  The AND, OR, and Biconditional are generalizable.
 */
bool ExpressionParser::getGenerality(char currentOperator){
    switch(currentOperator){
        case '&':
            return true;
        case '|':
            return true;
        case '=':
            return true;
        case '>':
            return false;
        case '~':
            return false;  
        default:
            return false;
    }
}

/** Checks if the syntax of the input string is correct
 *  Returns true if so, and false if incorrect or syntax
 *  is ambiguous
 *  Ambiguous syntax is defined as any generalized expression
 *  that could result in two different expressions given different
 *  orders of operations on the generalized operations.
 *  
 *  Ex:
 *      A|B|C is not ambiguous because A | (B | C) = (A | B) | C
 *      A>B>C is ambiguous because A > (B > C) != (A > B) > C
 *      A|B&C is ambiguous because A | (B & C) != (A | B) & C

    Ex Test Cases:
    A & ~B              is not ambiguous
    (A & ~B) > (C | D)  is not ambiguous
    (A & ~(B|C)) > ~D   is not ambiguous
    A & ~ & C           is ambiguous        "Error: Expected statement after operator but found another operator"
 */
bool ExpressionParser::isCorrectSyntax(string input, unsigned int & index) {
    if(index >= input.length()){
        return true;
    }
    if(input.size() == 0) {
        cout << "Error: Input Cannot Be Empty" << endl;
        return false;
    }
    // firstOP holds the first operator found on a line, which will be compared to all future operators
    char* firstOp = NULL;
    // general holds the generality of he first operator that is found
    bool general = false;
    // expectStatement is true when the checker will expect a statement next, denoted by an atomic statement or a '('
    // when true, the algorithm can also expect the NOT operator, to handle cases such as (A & ~B)
    // expectStatement is false when the checker will be expecting an operator next (excluding the NOT operator)
    bool expectStatement = true;

    // search through the length of the string
    while(index < input.length()) {
        // if subexpression found, recursively call this function on it
        if(input[index] == '('){
            // if the checker was expecting an operator and found a statement, throw an error
            if(!expectStatement) {
                cout << "Error: Expected operator after statement but found a statement" << endl;
                firstOp = NULL;
                return false;
            }
            // if subexpression not correct syntax, return false
            index++;
            // after finding a statement, expectStatment is changed
            expectStatement = false;
            if(!isCorrectSyntax(input, index)){
                return false;
            }
        }
        // if the current subexpression ends, return true
        else if(input[index] == ')'){
            // if the checker was expecting a statment and found a ')', throw an error
            if(expectStatement) {
                cout << "Error: Expected statement after operator but found closed parentheses" << endl;
                firstOp = NULL;
                return false;
            }
            index++;
            return true;
        }
        // if the NOT operator is found
        else if(input[index] == '~') {
            // if the checker was expecting a non-NOT operator and found a NOT, throw an error
            if(!expectStatement) {
                cout << "Error: Expected non-NOT operator after statement but found a NOT operator" << endl;
                firstOp = NULL;
                return false;
            }
            index++;
        }
        // if an operator is found that is not the NOT operator
        else if(isOperator(input[index]) && input[index] != '~'){
            // if the checker was expecting a statement and found an operator, throw an error
            if(expectStatement) {
                cout << "Error: Expected statement after operator but found another operator 4" << endl;
                firstOp = NULL;
                return false;
            }
            // after finding an operator, expectStatment is changed
            expectStatement = true;
            // if it is the first operator on this level, store it
            if(firstOp == NULL) {
                firstOp = &input[index];
                general = getGenerality(*firstOp);
            }
            // if it is not the first operator
            else {
                // if it is a different operator
                // or if the first operator is not generalizable
                if(input[index] != *firstOp || general == false) {
                    cout << "Error: Ambiguous Statement With Operators " << *firstOp << " and " << input[index] << endl;
                    firstOp = NULL;
                    return false;
                }
            }
            index++;
        }
        // else if an atomic statement is found
        else {
            // if the checker was expecting an operator and found an atomic statement, throw an error
            if(!expectStatement) {
                cout << "Error: Expected operator after statement but found atomic statment" << endl;
                firstOp = NULL;
                return false;
            }
            // after finding a statement, expectStatment is changed
            expectStatement = false;
            index++;
        }
    }

    return true;
}

// Simply Removes ' ' From Logical Expressions. Then calls to check the syntax of the statement.
string ExpressionParser::formatInputValue(string currentInput){
    string tempInput = "";
    for(char currentChar : currentInput){
        if(currentChar != ' '){
            tempInput += currentChar;
        }
    }
    // Calls isCorrectSyntax on the entire statement and returns an error if
    // the syntax is wrong or ambiguous
    unsigned int testIndex = 0;
    if(!isCorrectSyntax(tempInput, testIndex)) {
        cout << tempInput << endl;
        return "ERROR";
    }
    return tempInput;
    // char prevOneValue = ' ';
    // char prevTwoValue = ' ';
    // string newFormatInput = "";
    // for(int k=0; k<currentInput.size(); k++){
    //     char currentValue = currentInput[k];
    //     newFormatInput += currentValue;
    //     if(prevOneValue == '-' && currentValue == '>'){
    //         newFormatInput.pop_back();
    //         newFormatInput.pop_back();
    //         newFormatInput += '/';
    //     }
    //     if(prevTwoValue == '<' && prevOneValue == '-' && currentValue == '>'){
    //         newFormatInput.pop_back();
    //         newFormatInput.pop_back();
    //         newFormatInput.pop_back();
    //         newFormatInput += '%';
    //     }
    //     if(!isalpha(currentValue) && !isOperator(currentValue) 
    //         && currentValue != '<' && currentValue != '-' && currentValue != '>' 
    //         && currentValue != '(' && currentValue != ')' && currentValue != ' '){
    //         cout << currentValue << endl;
    //         return "";
    //     }
    //     prevTwoValue = prevOneValue;
    //     prevOneValue = currentValue;
    // }    
    // return newFormatInput;
}

//Below is the Implementation of the Well-Known Shunting Yard Algorithm.
//This Algorithm is described more in detail on the Wiki Pages of the ALPACA-LOGIC Branch.
//Simply, = O(n) Expression Parser For A Given String => Reverse Polish Notation.
string ExpressionParser::runShuntingYardAlgorithm(string inputExpression){
    //Main Output Queue:
    queue<char> outQueue;
    //Main Operator Stack:
    stack<char> opStack;
    //Formats Input String By Removing Any Spaces.
    inputExpression = formatInputValue(inputExpression);
    if(inputExpression == "ERROR"){
        return "ERROR";
    }
    //Constants For Associativity Values:
    char leftValue = 'L';
    char rightValue = 'R';
    //Constants For Paranthesis Values:
    char leftP = '(';
    char rightP = ')';
    //While There Are More Tokens:
    for(char token: inputExpression){
        //Case 1: Valid Operator.
        if(isOperator(token)){
            while(!opStack.empty() 
                && isOperator(opStack.top())
                && ((getAssociativity(token) == leftValue && getPrecedence(opStack.top()) >= getPrecedence(token))
                    || (getAssociativity(token) ==  rightValue && getPrecedence(opStack.top()) > getPrecedence(token)))) {
                outQueue.push(opStack.top());
                opStack.pop();
            }
            opStack.push(token);   
        }
        //Case 2: Left Paranthesis '('
        else if(token == leftP){
            opStack.push(token);
        }
        //Case 3: Right Paranthesis ')'
        else if(token == rightP) {
            while(!opStack.empty() && opStack.top() != leftP){
                outQueue.push(opStack.top());
                opStack.pop();
            }
            //Error Check For Mismatched Paranthesis:
            //If Stack = Empty w/o Finding a Left Parenthesis, 
            //then there are Mismatched Parentheses => Invalid Expression.
            //"ERROR" = Communication to Client = Tree.cpp To Construct Tree.
            if(opStack.empty()){
                cout << "Error: Mismatched Parentheses." << endl;
                return "ERROR";
            }
            if(opStack.top() == '('){
                opStack.pop();
            }
        }
        else{
            //Error Check For Non-Operator + Non-Alpha Characters:
            //(e.g., Numerical Values, ...)
            if(!isalpha(token)){
                cout << "Error: Invalid Operator." << endl;
                return "ERROR";
            }
            //Append Current Value To Main Output Queue.
            outQueue.push(token);
        }
    }
    //Push Any Remaining Operators Onto Output Queue:
    while(!opStack.empty()){
        //Error Check For Mismatched Paranthesis:
        if(opStack.top() == '(' || opStack.top() == ')'){
            cout << "Error: Mismatched Parentheses." << endl;
            return "ERROR";
        }
        outQueue.push(opStack.top());
        opStack.pop();
    }
    //Format/Set Output Result String By Obtaining All Values From Output Queue.
    string resultValue = "";
    while(!outQueue.empty()) {
        resultValue += outQueue.front();
        outQueue.pop();
    }
    //Return Reverse Polish Notation of Input Expression.
    return resultValue;
}
