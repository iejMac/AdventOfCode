#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

bool in_between(int val, int b1, int b2){
	if ((val >= b1) && (val <= b2))
		return true;
	return false;
}

void rotate_left_90(int& x, int& y){
	int new_x = -1 * y;
	int new_y = x;

	x = new_x;
	y = new_y;
	return;
}

void rotate_right_90(int& x, int& y){
	int new_x = y;
	int new_y = -1 * x;

	x = new_x;
	y = new_y;
		
	return;
}


int main(){
	
	std::ifstream infile;
	infile.open("day_12_input.txt");

	std::string line;

	char instruction;
	int value;

	int ang = 0; // in degrees according to unit circle

	int x = 0; //east-west
	int y = 0; //north-south

	int way_x = 10;
	int way_y = 1;

	// east and north are positive

	while(std::getline(infile, line)){

		instruction = line[0];
		value = std::stoi(line.substr(1, line.size()));

		if (instruction == 'N')
			way_y += value;
		else if (instruction == 'S')
			way_y -= value;
		else if (instruction == 'E')
			way_x += value;
		else if (instruction == 'W')
			way_x -= value;

		else if (instruction == 'F'){
			x += way_x * value;
			y += way_y * value;
		}

		else if (instruction == 'L'){
			if (value == 90){
				rotate_left_90(way_x, way_y);
			}
			else if (value == 180){
				way_y *= -1;
				way_x *= -1;
			}
			else if (value == 270){
				rotate_right_90(way_x, way_y);
			}
		}

		else if (instruction == 'R'){
			if (value == 90)
				rotate_right_90(way_x, way_y);
			else if (value == 180){
				way_y *= -1;
				way_x *= -1;
			}
			else if (value == 270)
				rotate_left_90(way_x, way_y);
		}
	}

	std::cout << std::abs(x) + std::abs(y) << std::endl;

	infile.close();


	return 0;
}
