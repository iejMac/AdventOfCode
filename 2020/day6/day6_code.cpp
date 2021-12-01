#include <iostream>
#include <fstream>
#include <vector>

int count_distinct(std::string cur_groups){

	for(auto i = 0 ; i < cur_groups.size() ; i++){
		char unique = cur_groups[i];

		for(auto j = i+1 ; j < cur_groups.size() ; j++){
			if (cur_groups[j] == unique){
				cur_groups.erase(cur_groups.begin() + j);
				j--;
			}

		}

	}

	return cur_groups.size();
}

int count_all(std::vector<std::string> ans){

	std::string cur_ans = ans[0];
	ans.pop_back();

	for(auto an : ans){

		for(auto i = 0 ; i < cur_ans.size() ; i++){
			bool in = false;
			for(auto ch: an){
				if(ch == cur_ans[i])
					in = true;
			}

			if(!in){
				cur_ans.erase(cur_ans.begin()+i);
				i--;
			}
		}
	}

	return cur_ans.size();
}


int main(){

	std::ifstream inFile;
	inFile.open("day_6_input.txt");

	std::string line;

	int group_distinct = 0;

	std::vector<std::string> gr_answers;

	while(std::getline(inFile, line)){

		gr_answers.push_back(line);

		if (line.size() == 0){
			group_distinct += count_all(gr_answers);
			gr_answers = {};
		}




	}

	if(gr_answers.size() > 0){
		group_distinct += count_all(gr_answers);
		gr_answers = {};
	}


	inFile.close();	

	std::cout << "Answer: " << group_distinct << std::endl;


	return 0;
}
