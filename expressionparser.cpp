#include <cctype>
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <stdlib.h>
using namespace std;

bool isOperator(char token) {
    return (token == '&' || token == '|');
}

int precedence(char currentOperator) {
    switch(currentOperator) {
        case '&':
            return 3;
        case '|':
            return 2;
        default:
            return -1;
    }
}

string read_token(string str) {
    //Output Queue
    queue<char> outQueue;
    //Operator Stack
    stack<char> opStack;
    //While There Are More Tokens:
    while(!str.empty()) {
        //Read Current Token:
        char token = str[0];
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

int main(int argc, char** argv){
    if(argc < 2){
        return EXIT_FAILURE;
    }
    string inputValue(argv[1]);
    string outputValue = read_token(inputValue);
    cout << outputValue << endl;
    //(A & B) | C 
    return EXIT_SUCCESS;
}