#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cmath>

std::pair<int, int> bit_counts(std::vector<std::string>& bins, int pos){
  int one_count = 0;
  for(int i = 0 ; i < (int)bins.size() ; i++){
    one_count += (bins[i][pos] == '1');
  }
  return std::make_pair(bins.size() - one_count, one_count);
}

int string2bin(std::string bin){
  int num = 0;
  reverse(bin.begin(), bin.end());
  for(int i = 0 ; i < (int)bin.size() ; i++){
    num += (bin[i] == '1') * pow(2, i);
  }
  return num;
}

int main(){

	std::ifstream infile;
	infile.open("day_3_input.txt");

  std::vector<std::string> co2_bins;
  std::vector<std::string> ox_bins;

  std::string bin;
  while(infile >> bin){
    co2_bins.push_back(bin);
    ox_bins.push_back(bin);
  }

  int pos = 0;
  while(co2_bins.size() > 1){
    std::pair<int, int> zero_one = bit_counts(co2_bins, pos);
    char mode = zero_one.first > zero_one.second ? '0' : '1';
    for(int i = 0 ; i < (int)co2_bins.size() ; i++){
      if(co2_bins[i][pos] == mode){
        co2_bins.erase(co2_bins.begin() + i);
        --i;
      }
    }
    ++pos;
  }


  pos = 0;
  while(ox_bins.size() > 1){
    std::pair<int, int> zero_one = bit_counts(ox_bins, pos);
    char mode = zero_one.first <= zero_one.second ? '0' : '1';
    for(int i = 0 ; i < (int)ox_bins.size() ; i++){
      if(ox_bins[i][pos] == mode){
        ox_bins.erase(ox_bins.begin() + i);
        --i;
      }
    }
    ++pos;
  }

  std::cout << string2bin(co2_bins[0]) << std::endl;
  std::cout << string2bin(ox_bins[0]) << std::endl;

  std::cout << string2bin(co2_bins[0]) * string2bin(ox_bins[0]) << std::endl;





	infile.close();

	return 0;
}

