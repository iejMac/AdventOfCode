#include <iostream>
#include <fstream>
#include <string>

int main(){

	std::ifstream infile;
	infile.open("day_2_input.txt");

  int val;
  std::string command;

  int hor = 0;
  int depth = 0;
  int aim = 0;

  while(infile >> command){
    infile >> val;

    if(command == "forward"){
      hor += val;
      depth += aim * val;
    } else if (command == "up") {
      aim -= val;
    } else if (command == "down") {
      aim += val;
    }

  }
	infile.close();

  std::cout << hor * depth << std::endl;

	return 0;
}

