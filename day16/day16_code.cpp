#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

bool checks_out(int num, std::vector<std::pair<int, int> > rules){
	for(int i = 0 ; i < rules.size() ; i++){
		if((num >= rules[i].first) && (num <= rules[i].second))
			return true;
	}
	return false;
}

int main(){

	std::ifstream infile;
	infile.open("day_16_input.txt");

	std::string line;
	bool writing_rules = true;
	
	std::vector<std::pair<int, int> > rules;
	std::vector<std::pair<int, int> > cur_rules;

	std::vector<int> my_ticket;
	std::vector<std::vector<int> > other_tickets;

	while(std::getline(infile, line)){

		if(line.size() == 0)
			writing_rules = false;
		
		if (writing_rules == true){
			cur_rules = parse_rule(line);
			for(int i = 0 ; i < cur_rules.size() ; i++)
				rules.push_back(cur_rules[i]);
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
			if(!checks_out(other_tickets[i][j], rules)){
				other_tickets.erase(other_tickets.begin() + i);
				i--;
				break;
			}
		}
	}

	std::vector<int> check_cols;
	for(int i = 0 ; i < other_tickets[0].size() ; i++){
		check_cols.push_back(i);
	}

	std::cout << check_cols.size() << std::endl;
	
	std::vector<std::pair<int, int> > relevant_rules;
	for(int i = 0 ; i < 12 ; i++)
		relevant_rules.push_back(rules[i]);

	for(int i = 0 ; i < other_tickets.size() ; i++){
		for(int j = 0 ; j < check_cols.size() ; j++){
			if(!checks_out(other_tickets[i][check_cols[j]], relevant_rules)){
				check_cols.erase(check_cols.begin() + j);
				j--;
			}
		}		
	}
	std::cout << check_cols.size() << std::endl;

	infile.close();

	return 0;
}

