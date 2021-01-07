#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctype.h>

/*
Idea:

1. Recursively remove "most inner" parentheses by evaluating
substrings that have no parentheses inside.

Example:
	1 + (2 * 3) + (4 * (5 + 6))
	1 + 6 + (4 * (5 + 6))
	1 + 6 + (4 * 11)
	1 + 6 + (4 * 11)
	1 + 6 + 44
	7 + 44
	51
*/

bool contains_parentheses(std::string str){
	for(int i = 0 ; i < str.size() ; i++)
		if(str[i] == '(')
			return true;
	return false;
}

long parse_simple_value(std::string simple_equation){
	int left_offset = 2;
	int right_offset = 2;
	long left_val;
	long right_val;
	long result;
	
	for(int i = 0 ; i < simple_equation.size() ; i++){
		if(simple_equation[i] == '+'){
			while(std::isdigit(simple_equation[i-left_offset]) && i-left_offset > 0)
				left_offset++;
			while(std::isdigit(simple_equation[i+right_offset]) && i+right_offset < simple_equation.size())
				right_offset++;
			
			if (i-left_offset > 0)
				left_offset--;
					
			left_val = std::stol(simple_equation.substr(i-left_offset, left_offset-2 + 1));
			right_val = std::stol(simple_equation.substr(i+2, right_offset - 2));
			
			if (simple_equation[i] == '+')
				result = left_val + right_val;
			else
				result = left_val * right_val;
			
			//simple_equation.erase(i-left_offset, left_offset-2+1 + right_offset-2 + 3);
			simple_equation.erase(i-left_offset, left_offset + right_offset);
			simple_equation.insert(i-left_offset, std::to_string(result));
			i = i - left_offset;
			left_offset = 2;
			right_offset = 2;
		}
	}
	
	for(int i = 0 ; i < simple_equation.size() ; i++){
		if(simple_equation[i] == '*'){
			while(std::isdigit(simple_equation[i-left_offset]) && i-left_offset > 0)
				left_offset++;
			while(std::isdigit(simple_equation[i+right_offset]) && i+right_offset < simple_equation.size())
				right_offset++;
			
			if (i-left_offset > 0)
				left_offset--;
					
			left_val = std::stol(simple_equation.substr(i-left_offset, left_offset-2 + 1));
			right_val = std::stol(simple_equation.substr(i+2, right_offset - 2));
			
			if (simple_equation[i] == '+')
				result = left_val + right_val;
			else
				result = left_val * right_val;
			
			//simple_equation.erase(i-left_offset, left_offset-2+1 + right_offset-2 + 3);
			simple_equation.erase(i-left_offset, left_offset + right_offset);
			simple_equation.insert(i-left_offset, std::to_string(result));
			i = i - left_offset;
			left_offset = 2;
			right_offset = 2;
		}
	}

	return std::stol(simple_equation);
}


long parse_value(std::string equation){

	if (!contains_parentheses(equation))
		return parse_simple_value(equation);
	
	std::vector<int> parenth_inds; // vector of indexes of OPEN parentheses
	int last_parenth_ind;
	long inner_value;

	for(int i = 0 ; i < equation.size() ; i++){
		if(equation[i] == '(')
			parenth_inds.push_back(i);
		else if(equation[i] == ')'){
			last_parenth_ind = parenth_inds[parenth_inds.size()-1];
			parenth_inds.pop_back();
			std::string inner_equation = equation.substr(last_parenth_ind + 1, i - last_parenth_ind - 1);
			inner_value = parse_value(inner_equation);
				
			equation.erase(last_parenth_ind, inner_equation.size()+2);
			i = last_parenth_ind;
			equation.insert(last_parenth_ind, std::to_string(inner_value));
		}
	}
	return parse_simple_value(equation);
}


int main(){

	std::ifstream infile;
	infile.open("day_18_input.txt");

	std::string line;
	
	long sum = 0;

	while(std::getline(infile, line)){
		sum += parse_value(line);
	}
	
	std::cout << sum << std::endl;

	infile.close();

	return 0;
}


