#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>

bool check_sums(std::vector<long> nums, long new_num){

	std::sort(nums.begin(), nums.end());

	for(auto i = 0 ; i < nums.size()-1 ; i++ ){
		for(auto j = i+1 ; j < nums.size() ; j++){
			if(nums[i] + nums[j] == new_num)
				return true;
			else if (nums[i] + nums[j] > new_num)
				break;
		}
	}

	return false;	
}

int custom_append(std::vector<long>& nums, long new_num){

	if(nums.size() < 25){
		nums.push_back(new_num);
		return 0;
	}

	if(check_sums(nums, new_num)){
		nums.erase(nums.begin());
		nums.push_back(new_num);
		return 0;
	}
	else{
		return new_num;
	}
}

long vec_sum(std::vector<long> vec, int x1, int x2){
	long sum = 0;
	for(auto i = x1 ; i <= x2 ; i++){
		sum += vec[i];
	}
	return sum;
}



int main(){

	std::ifstream inFile;
	inFile.open("day_9_input.txt");

	std::string num;
	long number;
	long target = 14360655;

	std::vector<long> feed;
	std::vector<long> numbers;

	while(std::getline(inFile, num)){

		number = std::stol(num);

		feed.push_back(number);
		//int result = custom_append(numbers, number);
		
	}

	int x1 = 0;
	int x2 = 1;

	while(true){

		long v_sum = vec_sum(feed, x1, x2);

		if (v_sum < target){
			x2++;
		}
		else if (v_sum > target){
			x1++;
		}
		else{

			long max = 0;
			long min = target;

			for(auto i = x1; i <= x2 ; i++){
				if (feed[i] < min)
					min = feed[i];
				if (feed[i] > max)
					max = feed[i];
			}

			std::cout << min + max << std::endl;



			return 0;
		}
		


	}







	inFile.close();

	return 0;
}
