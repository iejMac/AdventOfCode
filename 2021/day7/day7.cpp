#include <iostream>
#include <vector>
#include <fstream>

int main(){
	std::ifstream infile;
	infile.open("day_7_input.txt");

  int pos;
  int max_pos = 0;
  char burn;
  std::vector<int> positions;
  while(infile >> pos){
    infile >> burn;
    positions.push_back(pos);

    if(pos > max_pos){
      max_pos = pos;
    }
  }
	infile.close();

  long long cur_sum;
  long long min_sum = 100000000000;
  int min_pos = 0;
  int steps;
  
  for(int i = 0 ; i < max_pos ; i++){
    cur_sum = 0;  
    for(auto& cpos : positions){
      //cur_sum += std::abs(cpos - i);
      steps = std::abs(cpos - i);
      cur_sum += (steps * (steps + 1)) / 2;
      if(cur_sum > min_sum)
        break;
    }

    if(cur_sum < min_sum){
      min_sum = cur_sum;
      min_pos = i;
    }
  }

  std::cout << min_sum <<std::endl;

	return 0;
}

