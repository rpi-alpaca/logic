#include <cctype>
#include <string>
#include <queue>
#include <stack>
#include <iostream>
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
    std::queue<char> outQ;
    std::stack<char> opS;
    while (!str.empty()) {
        char token = str[0];
        str = str.substr(1, str.size());
        if (std::isalpha(token)) {
            outQ.push(token);
        }
        if (isOperator(token)) {
            while ((precedence(opS.top()) >= precedence(token)) && (opS.top() != '(')) {
                outQ.push(opS.top());
                opS.pop();
                opS.push(token);
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
    if(argc < 2){
        return EXIT_FAILURE;
    }
    cout << read_token("(A & B) | C") << endl;
    return EXIT_SUCCESS;
}