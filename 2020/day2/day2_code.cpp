#include <iostream>
#include <fstream>
#include <string>

int main(){

	std::ifstream inFile;
	inFile.open("day_2_input.txt");

	int correct = 0;

	std::string range;
	std::string letter;
	std::string password;

	while(inFile >> range){
		inFile >> letter;
		inFile >> password;
		
		// Get range bounds:
		int lower_bound = std::stoi(range.substr(0, range.find('-')));
		int upper_bound = std::stoi(range.substr(range.find('-')+1, range.size()));

		char bounding_letter = letter[0];

		// Part 1:
		/*
		int bound_counter = 0;

		for (auto ch : password){
			if(ch == bounding_letter)
				bound_counter++;
		}

		if ((bound_counter >= lower_bound) && (bound_counter <= upper_bound))
			correct += 1;
		*/

		// Part 2:
		if (!(password[lower_bound-1]==bounding_letter) != !(password[upper_bound-1]==bounding_letter))
			correct++;
	}

	inFile.close();

	std::cout << correct << std::endl;

	return 0;
}
