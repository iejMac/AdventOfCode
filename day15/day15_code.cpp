#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

std::vector<int> parse_input(std::string inp){
	
	int ind = 0;
	int found = 0;

	std::vector<int> nums;

	while(found != std::string::npos){
		found = inp.find(',', ind);
		if(found == std::string::npos)
			break;

		nums.push_back(std::stoi(inp.substr(ind, found-ind)));
		ind = found+1;
	}
	return nums;
}

int main(){

	std::ifstream infile;
	infile.open("day_15_input.txt");

	std::string inp;
	infile >> inp;
	std::vector<int> start_sequence = parse_input(inp);
	std::map<int, int> most_recent;
	
	// 0 reserved for new ones;
	for(int i = 0 ; i < start_sequence.size()-1 ; i++)
		most_recent[start_sequence[i]] = i+1;	
		
	int last = start_sequence[start_sequence.size() - 1];
	int temp;
	
	for(int i = start_sequence.size()+1; i <= 30000000 ; i++){
		std::cout << i << std::endl;
		
		if(most_recent[last] == 0){
			most_recent[last] = i-1;
			last = 0;
		}
		else{
			temp = most_recent[last];
			most_recent[last] = i-1;
			last = i - 1 - temp;
		}
	}
	
	std::cout << last << std::endl;	
	

	infile.close();

	return 0;
}

