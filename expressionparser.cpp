#include <cctype>
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <stdlib.h>
using namespace std;

bool isOperator(char token) {
    return (token == '&' || token == '|' || token == '~' || token == '/' || token == '%');
}

int precedence(char currentOperator) {
    switch(currentOperator) {
        case '&':
            return 3;
        case '|':
            return 2;
        case '~':
            return 1;  
        case '/':
            return 2;
        case '%':
            return 2;
        default:
            return -1;
    }
}

string runShuntingYardAlgorithm(string str) {
    //Output Queue
    queue<char> outQueue;
    //Operator Stack
    stack<char> opStack;
    //While There Are More Tokens:
    while(!str.empty()) {
        //Read Current Token:
        char token = str[0];
        //Update Current String:
        str = str.substr(1, str.size());
        //Case 1: Atomic Statement
        if(isalpha(token)) {
            //Push it to the output queue
            outQueue.push(token);
        }
        //If the token is an operator
        if(isOperator(token)) {
            while(!opStack.empty() 
                    && (precedence(opStack.top()) >= precedence(token)) 
                    && (opStack.top() != '(')) {
                outQueue.push(opStack.top());
                opStack.pop();
            }
            opStack.push(token);   
        }
        if(!opStack.empty() && opStack.top() == '(') {
            opStack.push(token);
        }
        if(!opStack.empty() && opStack.top() == ')') {
            while(!opStack.empty() && opStack.top() != '(') {
                outQueue.push(opStack.top());
                opStack.pop();
            }
            //If the Stack Empty w/o Finding a Left Parenthesis, 
            //then there are Mismatched Parentheses.
            if(!opStack.empty() && opStack.top() == '(') {
                opStack.pop();
            }
        }
    }
    while(!opStack.empty()) {
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

//Unused Method: Needs To Be Removed Immediately.
bool calculate(string input) {
	return false; 
}

string formatInputValue(string currentInput){
    char prevOneValue = ' ';
    char prevTwoValue = ' ';
    string newFormatInput = "";
    for(int k=0; k<currentInput.size(); k++){
        char currentValue = currentInput[k];
        newFormatInput += currentValue;
        if(prevOneValue == '-' && currentValue == '>'){
            newFormatInput.pop_back();
            newFormatInput.pop_back();
            newFormatInput += '/';
        }
        if(prevTwoValue == '<' && prevOneValue == '-' && currentValue == '>'){
            newFormatInput.pop_back();
            newFormatInput.pop_back();
            newFormatInput.pop_back();
            newFormatInput += '%';
        }
        if(!isalpha(currentValue) && !isOperator(currentValue) 
            && currentValue != '<' && currentValue != '-' && currentValue != '>' 
            && currentValue != '(' && currentValue != ')' && currentValue != ' '){
            cout << currentValue << endl;
            return "";
        }
        prevTwoValue = prevOneValue;
        prevOneValue = currentValue;
    }
    //cout << "WHAT = " << newFormatInput << endl;
    return newFormatInput;
}

int main(int argc, char** argv){
    if(argc < 2){
        return EXIT_FAILURE;
    }
    string inputValue(argv[1]);
    inputValue = formatInputValue(inputValue);
    string outputValue = runShuntingYardAlgorithm(inputValue);
    cout << outputValue << endl;
    //(A & B) | C 
    return EXIT_SUCCESS;
}