#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int vec_lens(std::vector<std::vector<int> > vecs){
	int lens = 0;
	for(int i = 0 ; i < vecs.size() ; i++)
		lens += vecs[i].size();
	return lens;
}

int find_len_1(std::vector<std::vector<int> > vecs){
	for(int i = 0 ; i < vecs.size() ; i++){
		if(vecs[i].size() == 1)
			return i;
	}
	return -1;
}

int find_val(int val, std::vector<int> vec){
	for(int i = 0 ; i < vec.size() ; i++){
		if (vec[i] == val)
			return i;
	}
	return -1;
}

std::vector<std::pair<int, int> > parse_rule(std::string str){
	
	std::vector<std::pair<int, int> > rules;

	int ind1 = str.find(':') + 2; 
	int ind2 = str.find(" or ");

	std::string rule1 = str.substr(ind1, ind2-ind1);
	std::string rule2 = str.substr(ind2 + 4, str.size()-ind2-4);

	int div1 = rule1.find('-');
	int div2 = rule2.find('-');
	
	rules.push_back(std::make_pair(std::stoi(rule1.substr(0, div1)), std::stoi(rule1.substr(div1+1, rule1.size()-div1))));
	rules.push_back(std::make_pair(std::stoi(rule2.substr(0, div2)), std::stoi(rule2.substr(div2+1, rule2.size()-div2))));
		
	return rules;
}

std::vector<int> parse_csv(std::string str){

	str.push_back(',');

	std::vector<int> values;

	int ind1 = 0;
	int ind2 = 0;
	while (ind2 != std::string::npos){
		
		ind2 = str.find(',', ind1);
		
		if(ind2 == std::string::npos)
			break;
		
		values.push_back(std::stoi(str.substr(ind1, ind2-ind1)));
		ind1 = ind2+1;
	}
	return values;
}

bool checks_out(int num, std::vector<std::pair<int, int> > rule){
	for(int j = 0 ; j < rule.size() ; j++){
		if((num >= rule[j].first) && (num <= rule[j].second))
			return true;
	}
	return false;
}


bool checks_out_all(int num, std::vector<std::vector<std::pair<int, int> > > rules){
	for(int i = 0 ; i < rules.size() ; i++)
		if(checks_out(num, rules[i]))
			return true;
	return false;
}

int main(){

	std::ifstream infile;
	infile.open("day_16_input.txt");

	std::string line;
	bool writing_rules = true;
	
	std::vector<std::vector<std::pair<int, int> > >rules;

	std::vector<int> my_ticket;
	std::vector<std::vector<int> > other_tickets;

	while(std::getline(infile, line)){

		if(line.size() == 0)
			writing_rules = false;
		
		if (writing_rules == true){
			rules.push_back(parse_rule(line));
		}
		else{
			if(line == "your ticket:"){
				std::getline(infile, line);
				my_ticket = parse_csv(line);
			}
			else if(line == "nearby tickets:"){
				while(std::getline(infile, line)){
					other_tickets.push_back(parse_csv(line));
				}
			}
		}
	}

	// int ticket_scanning_error = 0;
	
	for(int i = 0 ; i < other_tickets.size() ; i++){
		for(int j = 0 ; j < other_tickets[i].size() ; j++){
			if(!checks_out_all(other_tickets[i][j], rules)){
				other_tickets.erase(other_tickets.begin() + i);
				i--;
				break;
			}
		}
	}

	std::vector<int> possible_categories;
	for(auto i = 0 ; i < rules.size() ; i++)
		possible_categories.push_back(i);
	std::vector<std::vector<int> > can_be(rules.size(), possible_categories);

	for(int i = 0 ; i < other_tickets.size() ; i++){
		for(int j = 0 ; j < other_tickets[i].size() ; j++){
			for(int k = 0 ; k < can_be[j].size() ; k++){
				if(!checks_out(other_tickets[i][j], rules[can_be[j][k]])){
					can_be[j].erase(can_be[j].begin() + k);
					k--;
				}
			}
		}
	}

	int ind = -1;
	int val = 0;

	int found_val = -1;

	// index = index in ticket ; value = index in menu
	std::vector<int> cat_org(rules.size(), -1);

	while(vec_lens(can_be) > 0){

		ind = find_len_1(can_be);
		val = can_be[ind][0];

		cat_org[ind] = val;
		
		// Make it 0 len so find_len_1 doesnt pick it up
		can_be[ind].erase(can_be[ind].begin());

		for(int i = 0 ; i < can_be.size() ; i++){

			found_val = find_val(val, can_be[i]);
			if(found_val != -1){
				can_be[i].erase(can_be[i].begin() + found_val);
			}
		}	
	
	}

	long mul = 1;

	for(auto i = 0 ; i < cat_org.size() ; i++){
		if(cat_org[i] < 6){
			mul *= my_ticket[i];
		}
	}

	std::cout << mul << std::endl;

	infile.close();

	return 0;
}

