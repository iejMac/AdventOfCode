#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

void printMap(std::vector<std::vector<int>> map){
  for(auto& row : map){
    for(auto& cell : row){
      std::cout << cell << " ";
    }
    std::cout << std::endl;
  }
  return;
}

int countDangerous(std::vector<std::vector<int>> map){
  int count = 0;
  for(auto& row : map){
    for(auto& cell : row){
      if(cell > 1)
        ++count;
    }
  }
  return count;
}

int main(){

	std::ifstream infile;
	infile.open("day_5_input.txt");

  std::string line;

  char burn;
  int x1, x2, y1, y2;
  int mx = 0;
  int my = 0;
  std::vector<std::pair<int, int>> p1;
  std::vector<std::pair<int, int>> p2;

  while(getline(infile, line)){
    std::stringstream s(line);
    s >> x1 >> burn >> y1;
    for(int i = 0 ; i < 2 ; i++)
      s >> burn; // " -> "
    s >> x2 >> burn >> y2;

    mx = x1 > mx ? x1 : mx;
    my = y1 > my ? y1 : my;
    mx = x2 > mx ? x2 : mx;
    my = y2 > my ? y2 : my;

    if((x1 == x2) || (y1 == y2) || ((std::abs(x1 - x2)) == (std::abs(y1 - y2)))){
      p1.push_back({x1, y1});
      p2.push_back({x2, y2});
    }
  }

  std::vector<std::vector<int>> map(my + 1, std::vector<int>(mx + 1, 0));

  for(int i = 0 ; i < (int)p1.size() ; i++){
    x1 = p1[i].first;
    x2 = p2[i].first;
    y1 = p1[i].second;
    y2 = p2[i].second;

    if(x1 == x2){
      if(y1 > y2){
        std::swap(y1, y2);
      }
      for(int j = y1 ; j <= y2 ; j++){
        map[j][x1]++;
      }
    } else if (y1 == y2){
      if(x1 > x2){
        std::swap(x1, x2);
      }
      for(int j = x1 ; j <= x2 ; j++){
        map[y1][j]++;
      }
    } else { // diag
      if(((y1-y2)/(x1-x2)) > 0){ 
        if(y1 > y2){
          std::swap(y1, y2);
          std::swap(x1, x2);
        }
        for(int i = 0 ; i <= std::abs(y2 - y1) ; i++){
          map[y1 + i][x1 + i]++;
        }
      } else {
        if(y1 < y2) {
          std::swap(y1, y2);
          std::swap(x1, x2);
        }
        for(int i = 0 ; i <= std::abs(y2 - y1) ; i++){
          map[y1 - i][x1 + i]++;
        }
      }
    }
  }

  std::cout << countDangerous(map) << std::endl;

	infile.close();

	return 0;
}

