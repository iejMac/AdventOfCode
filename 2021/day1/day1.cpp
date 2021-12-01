#include <vector>
#include <fstream>
#include <iostream>

int main(){
	std::ifstream infile;
	infile.open("day_1_input.txt");

  int depth;
  std::vector<int> depths;

  while(infile >> depth){
    depths.push_back(depth);
  }
	infile.close();

  int count = 0;
  int old_sum = depths[0] + depths[1] + depths[2];
  for(int i = 3 ; i < (int)depths.size() ; i++){
    int sum = depths[i] + depths[i-1] + depths[i-2];
    count += (sum > old_sum);
    old_sum = sum;
  }

  std::cout << count << std::endl;
	return 0;
}
