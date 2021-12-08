#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void printOpts(std::vector<std::vector<int>> opts){
  for(auto& row : opts){
    for(auto& col : row){
      std::cout << col << " ";
    }
    std::cout << std::endl;
  }
}

char getDigit(std::string comb, std::vector<std::vector<int>> opts){
  return 'a';
}

void customVecXOR(std::vector<int>& bin1, std::vector<int>& bin2){
  for(int i = 0 ; i < (int)bin1.size() ; i++){
    if(bin1[i] && bin2[i]){
      bin1[i] = 0;
      bin2[i] = 0;
    }
  }
}

void figureOut(std::vector<std::vector<int>>& opts){
  for(int i = 0 ; i < (int)opts.size() ; i++){
    for(int j = i+1 ; j < (int)opts.size() - 1 ; j++){
      customVecXOR(opts[i], opts[j]);
    }
  }
}

int main(){

	std::ifstream infile;
	infile.open("test.txt");

  char burn;
  std::string line, word;

  /*
    inds:
    0 1 2 3 4 5 6
    a b c d e f g
  
    pos:
    0
   1 2
    3
   4 5
    6
  */

  while(getline(infile, line)){
    std::vector<std::vector<int>> opts(7, std::vector<int>(7, 1)); // initially anything can be anywhere
    std::stringstream s(line);
    // Figure out
    for(int i = 0 ; i < 10 ; i++){
      s >> word;
      if(word.size() == 2){ // 1
        for(int j = 0 ; j < 7 ; j++){
          if((j == 2) || (j == 5)){
            continue;
          }
          for(int k = 0 ; k < (int)word.size() ; k++){
            opts[j][word[k] - 'a'] = 0;
          }
        }
      } else if (word.size() == 3) { // 7
        for(int j = 0 ; j < 7 ; j++){
          if((j == 0) || (j == 2) || (j == 5)){
            continue;
          }
          for(int k = 0 ; k < (int)word.size() ; k++){
            opts[j][word[k] - 'a'] = 0;
          }
        }
      } else if (word.size() == 4) { // 4
        for(int j = 0 ; j < 7 ; j++){
          if((j == 1) || (j == 2) || (j == 3) || (j == 5)){
            continue;
          }
          for(int k = 0 ; k < (int)word.size() ; k++){
            opts[j][word[k] - 'a'] = 0;
          }
        }
      }
    }

    printOpts(opts);

    return 0;
    s >> burn; // burn |

    std::string num;

    // Get output
    for(int i = 0 ; i < 4 ; i++){
      num = "";
      s >> word;
      if(word.size() == 2){
        num += '2';
      } else if (word.size () == 3){
        num += '7';
      } else if (word.size () == 4){
        num += '4';
      } else if (word.size () == 8){
        num += '8';
      } else {
        num += getDigit(word, opts);
      }
    }

    std::cout << num << std::endl;
  }

	infile.close();

	return 0;
}

