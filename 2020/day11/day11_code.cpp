#include <iostream>
#include <fstream>
#include <vector>

bool check_change(std::vector<std::string> t1, std::vector<std::string> t2){
	for(auto i = 0 ; i < t1.size() ; i++){
		if (t1[i] != t2[i])
			return false;
	}
	return true;
}

std::vector<std::pair<int, int>> get_adjacent_seats(int y, int x, int y_max, int x_max, std::vector<std::string> seating){

	std::vector<std::pair<int, int>> points;
	std::vector<std::pair<int, int>> vectors = {{1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}};

	int cur_x;
	int cur_y;
	bool encountered_seat = false;
	bool flag = false;

	for(auto vec : vectors){

		flag = false;
		encountered_seat = false;
		cur_y = y;
		cur_x = x;

		while(!encountered_seat){
			cur_y += vec.first;
			cur_x += vec.second;

			if((cur_y < 0) || (cur_y > y_max)){
				flag = true;
				break;
			}

			if((cur_x < 0) || (cur_x > x_max)){
				flag = true;
				break;
			}

			if ((seating[cur_y][cur_x] == 'L') || (seating[cur_y][cur_x] == '#'))
				encountered_seat = true;
		}

		if (flag == true)
			continue;

		points.push_back(std::make_pair(cur_y, cur_x));
	}

	return points;
}


char analyze_seat(int y, int x, std::vector<std::string> seating){

	char current_state = seating[y][x];
	std::vector<std::pair<int, int>> adjacent_seats;

	int occupied = 0;
	int empty = 0;

	if (current_state == '.'){
		return '.';
	}
	else if (current_state == 'L'){

		adjacent_seats = get_adjacent_seats(y, x, seating.size()-1, seating.size()-1, seating);


		for(auto seat : adjacent_seats){
			if (seating[seat.first][seat.second] == 'L')
				empty++;
			else if (seating[seat.first][seat.second] == '#')
				occupied++;
		}

		if (occupied == 0)
			return '#';
		else
			return current_state;
	}
	else if (current_state == '#'){

		adjacent_seats = get_adjacent_seats(y, x, seating.size()-1, seating.size()-1, seating);

		for(auto seat : adjacent_seats){
			if (seating[seat.first][seat.second] == 'L')
				empty++;
			else if (seating[seat.first][seat.second] == '#')
				occupied++;
		}

		if (occupied >= 5){
			return 'L';
		}
		else{
			return current_state;
		}
	}

	return current_state;
}

std::vector<std::string> apply_rules(std::vector<std::string> seating){

	std::vector<std::string> new_seating(seating);

	for(auto i = 0 ; i < seating.size() ; i++){
		for(auto j = 0 ; j < seating.size() ; j++){
			new_seating[i][j] = analyze_seat(i, j, seating);
		}
	}
	
	return new_seating;
}



int main(){

	std::ifstream inFile;
	inFile.open("day_11_input.txt");

	std::string line;
	std::vector<std::string> seating;

	while(std::getline(inFile, line)){
		seating.push_back(line);
	}

	std::vector<std::string> new_seating = apply_rules(seating);

	while(!check_change(seating, new_seating)){
		seating = new_seating;
		new_seating = apply_rules(seating);
	}

	int occ = 0;

	for(auto row : seating){
		for (auto cell : row){
			if (cell == '#')
				occ++;
		}
	}
	
	std::cout << occ << std::endl;

	inFile.close();

	return 0;
}
