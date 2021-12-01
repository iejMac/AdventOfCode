#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

int waiting_time(int min_time, int id){
	return id - min_time%id;
}


struct {
	bool operator()(std::pair<int, int> a, std::pair<int, int> b) const
	{
		return a.second < b.second;
	}
} custom_comp;



std::vector<std::pair<int, int>> parse_ids(std::string ids){
	
	std::vector<std::pair<int, int>> num_ids;
	int num_iterator = 0;
	int begin = 0;

	std::string item;

	for(auto i = 0 ; i < ids.size() ; i++){
		if (ids[i] == ','){

			item = ids.substr(begin, i-begin);
			if (item != "x"){
				num_ids.push_back(std::make_pair(num_iterator, std::stoi(item)));
				num_iterator++;
			}
			else{
				num_iterator++;
			}
			begin = i+1;
		}
	}

	return num_ids;
}

bool check_if_works(long t0, std::pair<int, int> pos_val){
	
	if ((t0 + pos_val.first) % pos_val.second == 0)
		return true;	
	return false;
}

int main(){

	std::ifstream infile;
	infile.open("day_13_input.txt");

	std::string line;

	// Waiting time = ID - min_time % ID

	int min_time;
	std::string ids;

	infile >> min_time;
	infile >> ids;

	std::vector<std::pair<int, int>> pos_id = parse_ids(ids);

	std::sort(pos_id.begin(), pos_id.end(), custom_comp);

	bool found_time = false;
	bool try_again = false;

	long m = pos_id[0].second;
	long long t0 = m - pos_id[0].first;

	int latest_found = 1;
	
	while(!found_time){

		try_again = false;

		std::cout << "T0: " << t0 << std::endl;

		for(auto v : pos_id ){
			std::cout << (t0 + v.first)%v.second << std::endl;

		}

		std::cout << "==================" << std::endl;

		for(auto i = 0 ; i < pos_id.size() ; i++){

			if (!check_if_works(t0, pos_id[i])){
				try_again = true;
				//m++;
				break;
			}
			else{
				if (i >= latest_found){
					m*= pos_id[latest_found].second;
					latest_found++;
				}
			}

		}


		if(!try_again){
			std::cout << "Found answer: " << std::endl;
			std::cout << t0 << std::endl;
			return 0;
		}

		t0 += m;
	}

	/*
	// Part 1:
	int min_waiting_time = 10000;
	int min_waiting_id;
	int cur_waiting_time;

	for(auto id : num_ids){
		
		cur_waiting_time = waiting_time(min_time, id);

		if(cur_waiting_time < min_waiting_time){
			min_waiting_time = cur_waiting_time;
			min_waiting_id = id;
		}
	}

	std::cout << min_waiting_id * min_waiting_time << std::endl;
	*/

	infile.close();

	return 0;
}
