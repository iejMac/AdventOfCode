#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

std::pair<long, long> parse_mem(std::string mem_com){
	int address;
	int value;

	int address_start = 0;

	for(auto i = 0 ; i < mem_com.size() ; i++){

		if(mem_com[i] == '['){
			address_start = i+1;
		}
		else if(mem_com[i] == ']'){
			address = std::stol(mem_com.substr(address_start, i-address_start));
		}

		else if(mem_com[i] == '='){
			value = std::stol(mem_com.substr(i+2, mem_com.size() - i -2));
			break;
		}
	}
	return std::make_pair(address, value);
}

std::string to_binary(long long x){

	std::string bin;
	
	while(x > 0){
		if(x % 2 == 1){
			bin.push_back('1');
			x--;
		}
		else
			bin.push_back('0');

		x /= 2;
	}
	
	std::reverse(bin.begin(), bin.end());
	int padding_size = 36 - bin.size();
	std::string padding(padding_size, '0');

	return padding + bin;
}

unsigned long long from_binary(std::string bin){
	
	unsigned long long x = 0;
	std::reverse(bin.begin(), bin.end());
		
	for(auto i = 0 ; i < bin.size() ; i++){
		x += (bin[i] - '0') * std::pow(2, i); 
	}
	return x;
}

std::string apply_mask(std::string val, std::string mask){

	std::string masked_val(val);

	for(auto i = 0 ; i < mask.size() ; i++){
		if(mask[i] != '0')
			masked_val[i] = mask[i];
	}

	return masked_val;
}

int X_count(std::string str){
	int count = 0;
	for(auto ch : str)
		if (ch == 'X')
			count++;
	return count;
}

void floating_addresses(std::string floating_address, std::vector<std::string>& floating_addresses_list){

	if (X_count(floating_address) == 0){
		floating_addresses_list.push_back(floating_address);
		return;
	}

	int ind = floating_address.find('X');
	if (ind != std::string::npos){
		floating_address[ind] = '0';
		floating_addresses(floating_address, floating_addresses_list);
		floating_address[ind] = '1';
		floating_addresses(floating_address, floating_addresses_list);
	}

	return;
}



int main(){

	std::ifstream infile;
	infile.open("day_14_input.txt");

	std::map<long long, unsigned long long> memory;
	std::string line;

	std::string cat;
	std::string mask;

	while(std::getline(infile, line)){
		
		cat = line.substr(0, 3);

		if (cat == "mas"){
			mask = line.substr(7, line.size() - 7);
		}
		else if (cat == "mem"){
			std::pair<long, long> ad_val = parse_mem(line);

			std::vector<std::string> address_list;
			while(!address_list.empty())
				address_list.pop_back();

			long address = ad_val.first;
			std::string bin_ad = to_binary(address);
			std::string after_mask = apply_mask(bin_ad, mask);

			floating_addresses(after_mask, address_list);

			for(auto ad : address_list){
				memory[from_binary(ad)] = ad_val.second;
			}
		}
	}

	unsigned long long sum = 0;

	for(auto address_value : memory){
		std::cout << address_value.first << ":" << address_value.second << std::endl;
		sum += address_value.second;
	}
	

	std::cout << sum << std::endl;	

	infile.close();

	return 0;
}
