#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int getScore(std::vector<std::vector<int>> board, int last_called){
  int unmarked_sum = 0;
  for(int i = 0 ; i < board.size() ; i++){
    for(int j = 0 ; j < board[0].size() ; j++) {
      if(board[i][j] > 0)
        unmarked_sum += board[i][j] - 1; // correct for +1 earlier
    }
  }
  return unmarked_sum * (last_called - 1);
}

void printBoard(std::vector<std::vector<int>>& board){
  for(auto& row : board){
    for(auto& num : row){
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  return;
}

bool hasWon(std::vector<std::vector<int>> board){
  bool row_good = true;
  bool col_good = true;
  for(int i = 0 ; i < board.size() ; i++){
    for(int j = 0 ; j < board[0].size() ; j++) {
      if(row_good){
        if(board[i][j] > 0)
          row_good = false;
      }
      if(col_good){
        if(board[j][i] > 0)
          col_good = false;
      }
    }
    if(row_good || col_good)
      return true;
    row_good=true;
    col_good=true;
  }
  return false; 
}

void markBoard(std::vector<std::vector<int>>& board, int num){
  for(int i = 0 ; i < (int)board.size() ; ++i){
    for(int j = 0 ; j < (int)board[0].size() ; ++j){
      if(board[i][j] == num){
        board[i][j] *= -1;
      }
    }
  }
  return;
}

int main(){

  /*
  ===================
    Parsing code begins
  ===================
  */

	std::ifstream infile;
	infile.open("day_4_input.txt");

  std::string line;
  std::string fline;
  std::vector<std::vector<std::vector<int>>> boards;

  getline(infile, fline);

  while(getline(infile, line)){
    if(line == ""){
      boards.push_back({});
      boards[boards.size() - 1].push_back({});
      continue;
    }

    std::stringstream s(line); // board nums
    int num;
    while(s >> num){
      boards[boards.size() - 1][boards[boards.size() - 1].size() - 1].push_back(num + 1); // +1 for our -1 marking
    }
    boards[boards.size() - 1].push_back({});
  }

  for(auto& board : boards){
    board.erase(board.begin() + board.size() - 1); //remove last empty row
  }

  /*
  ===================
    Parsing code ends
  ===================
  */

  int tok;
  char burn_comma;
  std::stringstream tokens(fline);

  int won_after;
  std::vector<std::vector<int>> last_winner;

  while(tokens >> tok){
    ++tok; // +1 again for our -1 marking
    for(int i = 0 ; i < (int)boards.size() ; i++){
      markBoard(boards[i], tok);
      if(hasWon(boards[i])){
        won_after = tok;
        last_winner = std::vector<std::vector<int>>(boards[i]);
        boards.erase(boards.begin() + i);
        i--;
      }
    }
    tokens >> burn_comma;
  }
 
  printBoard(last_winner);
  std::cout << getScore(last_winner, won_after) << std::endl;
  
	infile.close();

	return 0;
}
