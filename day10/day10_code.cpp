#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

int count_diffs(std::vector<int> vec, int diff){

	int diff_count = 0;
	for(auto i = 0 ; i < vec.size()-1 ; i++){
		for(auto j = i+1; j < vec.size() ; j++){
			if(std::abs(vec[i] - vec[j]) == diff)
				diff_count++;
		}
	}

	return diff_count;
}

void traverse_jolt_tree(std::vector<int> jolts, int cur_ind, int dest_ind ,long& paths_count){

	if (cur_ind == dest_ind){
		paths_count++;
		return;
	}

	int current_joltage = jolts[cur_ind];
	int offset = 1;
	while(jolts[cur_ind + offset] - jolts[cur_ind] <= 3){

		traverse_jolt_tree(jolts, cur_ind+offset, dest_ind, paths_count);
		offset++;

	}
	return;
}


int main(){

	std::ifstream inFile;
	inFile.open("day_10_input.txt");

	int joltage;
	std::vector<int> jolts;

	while(inFile >> joltage){
		jolts.push_back(joltage);
	}

	std::sort(jolts.begin(), jolts.end());
	jolts.insert(jolts.begin(), 0);
	jolts.push_back(jolts[jolts.size()-1] + 3);

	// Part 2:
	
	long paths = 1;

	int segment_start = 0;
	int segment_end = 0;

	long segment_paths = 0;

	for( auto i = segment_end ; i < jolts.size()-1 ; i++ ){
		if(jolts[i+1] - jolts[i] == 3){
			segment_end = i;
			traverse_jolt_tree(jolts, segment_start, segment_end, segment_paths);

			paths *= segment_paths;
			//std::cout << segment_start << " " << segment_end << " : " << segment_paths << std::endl;
			segment_paths = 0;

			
			segment_start = i+1;
			segment_end = i+1;
		}
	}

	//traverse_jolt_tree(jolts, 0, paths);
	std::cout << paths << std::endl;

	/*
	// Part 1:
	int dif_1 = 0;
	int dif_3 = 0;

	jolts.insert(jolts.begin(), 0);
	jolts.push_back(jolts[jolts.size()-1] + 3);

	for(auto i = 0 ; i < jolts.size()-1 ; i++){
		if (jolts[i+1] - jolts[i] == 1)
			dif_1++;
		else if(jolts[i+1] - jolts[i] == 3)
			dif_3++;
	}

	std::cout << dif_1 * dif_3 << std::endl;
	*/






	inFile.close();

	return 0;
}
