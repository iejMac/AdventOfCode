#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::pair<std::string, int> parse_instruction(std::string instr){
	std::string command = instr.substr(0, 3);
	int val = std::stoi(instr.substr(4, instr.size()-4));
	return {command, val};
}

int main(){

	std::ifstream inFile;
	inFile.open("day_8_input.txt");

	std::string line;

	std::vector<std::pair<std::string, int>> program;


	while(std::getline(inFile, line)){
		program.push_back(parse_instruction(line));
	}

	bool terminates = false;
	int fix_iterator = 0;
	int acc;

	while(!terminates){

		std::vector<bool> visited(program.size(), false);
		std::vector<std::pair<std::string, int>> program_cp(program);

		bool jmp_nop_found = false;
		while((!jmp_nop_found) && (fix_iterator < program_cp.size())){
			if (program_cp[fix_iterator].first == "jmp"){
				program_cp[fix_iterator].first = "nop";
				fix_iterator++;
				jmp_nop_found = true;
			}
			else if(program_cp[fix_iterator].first == "nop"){
				program_cp[fix_iterator].first = "jmp";
				fix_iterator++;
				jmp_nop_found = true;
			}
			else{
				fix_iterator++;
			}
		}

		acc = 0;
		int position = 0;
		terminates = true;

		// Run program:
		while((position >= 0) && (position < program_cp.size())){

			if(visited[position] == true){
				terminates = false;
				break;
			}

			std::string command = program_cp[position].first;
			int value = program_cp[position].second;
			visited[position] = true;

			if(command == "acc"){
				acc += value;
				position++;
			}
			else if(command == "jmp"){
				position += value;
			}
			else if(command == "nop"){
				position++;
			}
		}

		if(terminates){
			std::cout << "Terminated!" << std::endl;
		}
	}
	
	std::cout << acc << std::endl;

	inFile.close();

	return 0;
}
