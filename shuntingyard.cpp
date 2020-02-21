#include <iostream>
#include <map>
#include <string>

std::string shuntingParser(std::string inputState){
	std::map<char, std::string> operators;
	operators['&'] = "and";
	operators['|'] = "or";
	operators['>'] = "conditional";
	operators['='] = "biconditional";
	operators['~'] = "neg";
	operators['('] = "open";
	operators[')'] = "closed";
	std::string output = "";
	unsigned int index = 0;
	while(index < inputState.size()){
		if(inputState[index] != ' '){
			char current = inputState[index];
			// std::cout << current <<std::endl;
			if(operators.find(current) != operators.end()){
				std::cout<< operators[current] <<std::endl;
				std::string oper = operators[current];
				if("open".equals(oper)){
					std::cout<<operators[current]<<std::endl;
				}
				// else if(operators[current].equals("closed")){

				// }
				// else{
				// 	std::cout<< "operator: " << current << std::endl;
				// }
			}
			else{
				std::cout<< "variable or parentheses: " << current << std::endl;
			}
		}
		index++;
	} 
	return inputState;
}

int main(int argc, char* argv[]) {
	std::cout << "Testing Shunting Yard" << std::endl;

	std::string inputState;
	std::cout << "Input a logic statement:" << std::endl;
	std::getline(std::cin, inputState);

	std::cout<< shuntingParser(inputState) <<std::endl;

	return 0;
}