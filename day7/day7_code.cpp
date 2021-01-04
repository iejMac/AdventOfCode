#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

std::string remove_spaces(std::string str){

	for(auto i = 0 ; i < str.size() ; i++){
		if(str[i] == ' '){
			str.erase(str.begin() + i);
			i--;
		}
	}

	return str;
}

std::vector<std::string> get_colors(std::string contents_str, bool remove_quantity){

	std::vector<std::string> contents;

	int end_last = 0;
	int end = contents_str.find(" bag");

	std::string cur_clr;

	while(end != -1){
		cur_clr = remove_spaces(contents_str.substr(end_last, end-end_last));
		if(remove_quantity)
			if ((cur_clr[0] >= 48) && (cur_clr[0] <= 57))
				cur_clr.erase(cur_clr.begin());
		contents.push_back(cur_clr);
		end_last = end+6;
		end = contents_str.find(" bag", end_last);
	}

	return contents;
}

void append_color(std::vector<std::pair<std::string, int>>& cont, std::string clr){

	int quantity;
	
	if((clr[0] >= 48) && (clr[0] <= 57)){
		quantity = clr[0] - '0';
		clr.erase(clr.begin());
	}
	else
		quantity = 0;

	for(auto contained_clr_val : cont){
		if (contained_clr_val.first == clr)
			return;
	}

	cont.push_back(std::make_pair(clr, quantity));
	return;
}

bool in_vec(std::vector<std::string> vec, std::string str){
	for(auto v_str : vec){
		if(v_str == str)
			return true;
	}
	return false;
}

bool check_shinygold_ending(std::map<std::string, std::vector<std::string>>& ct_map, std::string key, std::vector<std::string> history){

	// Check for shinygold:
	for(auto clr : ct_map[key]){
		if(clr == "shinygold")
			return true;
		else if(clr == "noother")
			return false;
		else if(in_vec(history, clr))
			return false;
	}


	for(auto clr : ct_map[key]){
		history.push_back(clr);
		bool found_shinygold = check_shinygold_ending(ct_map, clr, history);
		history.pop_back();
		if(found_shinygold)
			return found_shinygold;
		else{
			ct_map[clr] = {"noother"};
		}
	}

	return false;
}

int count_bag_contents(std::map<std::string, std::vector<std::pair<std::string, int>>> ct_map, std::string key){

	int count = 0;

	if(key == "noother")
		return 0;

	for(auto clr_quant : ct_map[key])
		count += clr_quant.second + clr_quant.second*count_bag_contents(ct_map, clr_quant.first);
	
	return count;
}

int main(){

	std::ifstream inFile;
	inFile.open("day_7_input.txt");

	std::string line;

	std::map<std::string, std::vector<std::pair<std::string, int>>> contents_map;

	while(std::getline(inFile, line)){

		std::string source_color = remove_spaces(line.substr(0, line.find("bags")-1));
		std::string contents_str = line.substr(line.find("contain")+8, line.size()-1);
		contents_str.pop_back();

		std::vector<std::string> contents = get_colors(contents_str, false);

		for(auto clr : contents){
			append_color(contents_map[source_color], clr);
		}

	}

	/*
	int shinygold_ending = 0;

	for(auto clr_vec : contents_map){
		shinygold_ending += check_shinygold_ending(contents_map, clr_vec.first, {clr_vec.first});
	}

	std::cout << shinygold_ending << std::endl;
	*/

	int shinygold_contents_count = count_bag_contents(contents_map, "shinygold");
	std::cout << shinygold_contents_count << std::endl;

	return 0;
}
