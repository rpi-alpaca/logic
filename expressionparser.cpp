#include <cctype>
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <stdlib.h>
#include "expressionparser.h"
using namespace std;

ExpressionParser::ExpressionParser(){
    output = "";
}

bool ExpressionParser::isOperator(char currentOperator){
    return (currentOperator == '&' 
            || currentOperator == '|' 
            || currentOperator == '~'
            || currentOperator == '='
            || currentOperator == '>');
}

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

bool ExpressionParser::isBoolean(char currentOperator){
    return (currentOperator == 'T' || currentOperator == 'F');
}

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

string ExpressionParser::formatInputValue(string currentInput){
    string tempInput = "";
    for(char currentChar : currentInput){
        if(currentChar != ' '){
            tempInput += currentChar;
        }
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

string ExpressionParser::runShuntingYardAlgorithm(string inputExpression){
    //Output Queue
    queue<char> outQueue;
    //Operator Stack
    stack<char> opStack;
    //While There Are More Tokens:
    inputExpression = formatInputValue(inputExpression);
    char leftValue = 'L';
    char rightValue = 'R';
    char leftP = '(';
    char rightP = ')';
    for(char token: inputExpression){
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
        else if(token == leftP){
            opStack.push(token);
        }
        else if(token == rightP) {
            while(!opStack.empty() && opStack.top() != leftP){
                outQueue.push(opStack.top());
                opStack.pop();
            }
            //If the Stack Empty w/o Finding a Left Parenthesis, 
            //then there are Mismatched Parentheses.
            if(opStack.empty()){
                cout << "Error: Mismatched Parentheses" << endl;
                return "ERROR";
            }
            if(opStack.top() == '('){
                opStack.pop();
            }
        }
        else{
            if(!isalpha(token)){
                cout << "Error: Invalid Operator" << endl;
                return "ERROR";
            }
            outQueue.push(token);
        }
    }
    while(!opStack.empty()){
        if(opStack.top() == '(' || opStack.top() == ')'){
            cout << "Error: Mismatched Parentheses" << endl;
            return "ERROR";
        }
        outQueue.push(opStack.top());
        opStack.pop();
    }
    string resultValue = "";
    while(!outQueue.empty()) {
        resultValue += outQueue.front();
        outQueue.pop();
    }
    return resultValue;
}

// int main(int argc, char** argv){
//     if(argc < 2){
//         return EXIT_FAILURE;
//     }
//     string inputValue(argv[1]);
//     inputValue = formatInputValue(inputValue);
//     string outputValue = runShuntingYardAlgorithm(inputValue);
//     cout << outputValue << endl;
//     //(A & B) | C 
//     return EXIT_SUCCESS;
// }