#include <iostream>
#include <fstream>
#include <vector>

void updateStates(std::vector<long long>& states){
  long long num_0 = states[0];
  for(int i = 0 ; i < (int)states.size() ; i++){
    states[i] = states[i+1]; // move everything down one
  }
  states[6] += num_0;
  states[8] = num_0;
  return; 
}

long long numFish(std::vector<long long>& states){
  long long res = 0;
  for(long long& count : states){
    res += count;
  }
  return res;
}

int main(){

	std::ifstream infile;
	infile.open("day_6_input.txt");

  int num;
  char burn;
  std::vector<long long> st(9, 0);

  while(infile >> num){
    infile >> burn; // burn comma
    st[num] += 1;
  }
	infile.close();

  int days = 256;

  for(int i = 0 ; i < days ; i++){
    updateStates(st); 
  }

  std::cout << numFish(st) << std::endl;

	return 0;
}

