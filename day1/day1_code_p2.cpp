#include <iostream>
#include <fstream>
#include <algorithm>

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

	std::sort(expenses, expenses+exp_count);
	// Now sorted in ascending order
	
	int cur_sum = 0;

	for(auto i = 0 ; i < exp_count-2; i++){
		
		if(expenses[i] + expenses[i+1] + expenses[i+2] > 2020)
			break;

		for(auto j = i+i ; j < exp_count-1; j++){

			if (expenses[i] + expenses[j] + expenses[j+1] > 2020)
				break;

			for (auto k = j+1 ; k < exp_count ; k++){
				cur_sum = expenses[i] + expenses[j] + expenses[k];
				if(cur_sum == 2020){
					std::cout << expenses[i] << " " << expenses[j] << " " << expenses[k] << " " << expenses[i]*expenses[j]*expenses[k] << std::endl;
				}
				else if(cur_sum > 2020)
					break;
			}
		}
	}
	


	return 0;
}
