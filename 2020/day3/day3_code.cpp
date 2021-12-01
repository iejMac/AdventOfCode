#include <iostream>
#include <vector>
#include <fstream>

int main(){

	std::ifstream inFile;
	inFile.open("day_3_input.txt");


	std::vector<std::string> tree_map;	
	std::string line;

	std::vector<int> slopes_x = {1, 3, 5, 7, 1};
	std::vector<int> slopes_y = {1, 1, 1, 1, 2};
	std::vector<int> tree_counts;

	while(std::getline(inFile, line)){
		tree_map.push_back(line);
	}

	for(auto j = 0 ; j <slopes_x.size() ; j++){

		int slope_x = slopes_x[j];
		int slope_y = slopes_y[j];
		
		int pos_x = 0;
		int pos_y = 0;

		int tree_count = 0;

		while(pos_y < tree_map.size()){

			if(tree_map[pos_y][pos_x] == '#')
				tree_count++;

			pos_x = (pos_x + slope_x) % tree_map[0].size();
			pos_y = pos_y + slope_y;
		}

		tree_counts.push_back(tree_count);
	}

	long mul = 1;

	for(auto num : tree_counts){
		mul *= num;
	}

	std::cout << mul << std::endl;

	return 0;
}
