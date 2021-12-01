#include <iostream>
#include <fstream>

int main(){

	int expense;
	int exp_count = 0;
	std::ifstream inFile;

	inFile.open("day_1_input.txt");
	while(inFile >> expense){
		exp_count++;
	}

	inFile.close();

	int* expenses = new int[exp_count];

	inFile.open("day_1_input.txt");
	exp_count = 0;
	while(inFile >> expense){
		expenses[exp_count] = expense;
		exp_count++;
	}

	int current_expense;

	for(auto i = 0 ; i < exp_count ; i++){
		current_expense = expenses[i];
		for(auto j = i+1; j < exp_count-1; j++){
			if(expenses[j] == 2020 - current_expense){
				std::cout << current_expense << " * " << expenses[j] << " = " << current_expense * expenses[j] << std::endl;
				return 0;
			}
		}
	}


	


	return 0;
}
