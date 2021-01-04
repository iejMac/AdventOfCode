#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

int main(){

	std::ifstream inFile;
	inFile.open("day_5_input.txt");

	std::string line;

	int row_count = 128;
	int col_count = 8;
	std::vector<int> ids;

	while(std::getline(inFile, line)){

		std::string row_instructions = line.substr(0, 7);
		std::string col_instructions = line.substr(7, 10);

		int row_lb = 0;
		int row_ub = row_count;
		int col_lb = 0;
		int col_ub = col_count;

		int range;

		for(auto i = 0 ; i < row_instructions.size() ; i++){

			range = row_ub - row_lb;

			if(row_instructions[i] == 'B'){
				row_lb = row_lb + range/2.0;
			}
			else{
				row_ub = row_ub - range/2.0;
			}
		}

		row_ub--;

		for(auto i = 0 ; i < col_instructions.size() ; i++){

			range = col_ub - col_lb;

			if(col_instructions[i] == 'R'){
				col_lb = col_lb + range/2.0;
			}
			else{
				col_ub = col_ub - range/2.0;
			}
		}

		col_ub--;

		std::pair<int, int> seat = {row_lb, col_lb};
		int seat_id = seat.first*8 + seat.second;

		ids.push_back(seat_id);
	}

	std::sort(ids.begin(), ids.end());

	for(auto i = 0 ; i < ids.size()-1 ; i++){
		if(ids[i]+1 != ids[i+1]){
			std::cout <<  ids[i] << " " << ids[i+1] << std::endl;
		}
	}




	return 0;
}
