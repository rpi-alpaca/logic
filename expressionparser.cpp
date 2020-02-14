#include <cctype>
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <stdlib.h>
using namespace std;

bool isOperator(char token) {
    return token == '&'
           || token == '|'
           || token == '@'
           || token == '('
           || token == ')';
}

int precedence(char op) {
    switch (op) {
        case '(':
        case ')':
            return 0;
        case '&':
            return 3;
        case '|':
        case '@':
            return 2;
        default:
            return -1; // temp
    }
}

std::string read_token(std::string str) {
    // Output Queue
    std::queue<char> outQ;
    // Operator Stack
    std::stack<char> opS;
    // While there are more tokens to be read
    while (!str.empty()) {
        // Read the token
        char token = str[0];
        str = str.substr(1, str.size());
        // If the token is an atomic statement
        if (std::isalpha(token)) {
            // Push it to the output queue
            outQ.push(token);
        }
        // If the token is an operator
        if (isOperator(token)) {
            if(opS.empty()){
                opS.push(token);
            }
            else{
                while ((precedence(opS.top()) >= precedence(token)) && (opS.top() != '(')) {
                    outQ.push(opS.top());
                    opS.pop();
                    opS.push(token);
                }   
            }
        }
        if (opS.top() == '(') {
            opS.push(token);
        }
        if (opS.top() == ')') {
            while (opS.top() != '(') {
                outQ.push(opS.top());
                opS.pop();
            }
            /* if the stack runs out without finding a left paren, then there are mismatched parentheses. */
            if (opS.top() == '(') {
                opS.pop();
            }
        }
    }
    while (!opS.empty()) {
        outQ.push(opS.top());
        opS.pop();
    }
    std::string outS;
    while (!outQ.empty()) {
        outS += outQ.front();
        outQ.pop();
    }
    return outS; //temp
}

bool calculate(std::string input) {
	return false; //temp;
}

int main(int argc, char** argv){
    if(argc < 1){
        return EXIT_FAILURE;
    }
    cout << read_token("(A & B) | C") << endl;
    return EXIT_SUCCESS;
}