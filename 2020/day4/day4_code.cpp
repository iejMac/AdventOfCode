#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

bool passport_valid(std::map<std::string, std::string> inf){

	// byr:
	if(inf["byr"] == "")
		return false;
	int byr_val = std::stoi(inf["byr"]);
	if ((byr_val > 2002) || (byr_val < 1920))
		return false;
	
	// iyr:
	if(inf["iyr"] == "")
		return false;
	int iyr_val = std::stoi(inf["iyr"]);
	if ((iyr_val < 2010) || (iyr_val > 2020))
		return false;
		
	// eyr:
	if(inf["eyr"] == "")
		return false;
	int eyr_val = std::stoi(inf["eyr"]);
	if ((eyr_val < 2020) || (eyr_val > 2030))
		return false;

	//hgt:
	if(inf["hgt"] == "")
		return false;

	std::string hgt_val_s = inf["hgt"].substr(0, inf["hgt"].size()-2);
	std::string hgt_cat = inf["hgt"].substr(inf["hgt"].size()-2, inf["hgt"].size()-1);

	if((hgt_val_s.size() == 0) || (hgt_cat.size() == 0))
		return false;
	
	int hgt_val = std::stoi(hgt_val_s);

	if(hgt_cat == "cm"){
		if((hgt_val > 193) || (hgt_val < 150))
			return false;
	}

	else if(hgt_cat == "in"){
		if((hgt_val > 76) || (hgt_val < 59))
			return false;
	}


	//hcl:
	
	if(inf["hcl"] == "")
		return false;

	if(inf["hcl"][0] != '#')
		return false;

	if(inf["hcl"].size() != 7)
		return false;

	for(auto i = 1 ; i < 7 ; i++){
		int cur = inf["hcl"][i];

		if(((cur < 48) || ((cur > 57)&&(cur < 97))) || (((cur > 57)&&(cur < 97)) || (cur > 102)))
			return false;
	}

	//ecl:
	std::vector<std::string> valid_ecl = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
	if(std::find(valid_ecl.begin(), valid_ecl.end(), inf["ecl"]) == valid_ecl.end())
		return false;

	//pid:
	if(inf["pid"].size() != 9)
		return false;
	
	for(auto i = 0 ; i < 9 ; i++){
		int cur = inf["pid"][i];
		if((cur < 48) || (cur > 57))
			return false;
	}


	return true;
}


int main(){

	std::ifstream inFile;
	inFile.open("day_4_input.txt");

	std::string line;

	std::string cur_passport;

	int valid = 0;

	while(std::getline(inFile, line)){

		cur_passport.append(line + ' ');
		
		if(line.size() == 0){

			std::map<std::string, std::string> info;
			std::string category;
			std::string val;

			for(auto i = 0 ; i < cur_passport.size()-3 ; i++){

				category = "";
				val = "";

				category.push_back(cur_passport[i]);
				category.push_back(cur_passport[i+1]);
				category.push_back(cur_passport[i+2]);

				// 4 Because of skipping ":"
				i+=4;
				
				while(cur_passport[i] != ' '){
					val.push_back(cur_passport[i]);
					i++;
				}

				info[category] = val;
			}

			valid += passport_valid(info);

			cur_passport = "";

		}


	}

	if (cur_passport.size() > 0){

		std::map<std::string, std::string> info;
		std::string category;
		std::string val;

		for(auto i = 0 ; i < cur_passport.size()-3 ; i++){

			category = "";
			val = "";

			category.push_back(cur_passport[i]);
			category.push_back(cur_passport[i+1]);
			category.push_back(cur_passport[i+2]);

			i+=4;
			while(cur_passport[i] != ' '){
				val.push_back(cur_passport[i]);
				i++;
			}

			info[category] = val;
		}

		valid += passport_valid(info);

		cur_passport = "";
	}

	std::cout << valid << std::endl;

	inFile.close();


	return 0;
}
