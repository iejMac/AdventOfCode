#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class Grid{
	public:
		std::vector<std::vector<std::vector<std::vector<int> > > >grid;
		std::pair<int, int> x_bounds;
		std::pair<int, int> y_bounds;
		std::pair<int, int> z_bounds;
		std::pair<int, int> w_bounds;

		Grid(std::vector<std::vector<std::vector<std::vector<int> > > >cp_grid){
			std::vector<std::vector<std::vector<std::vector<int> > > >cp(cp_grid);
			grid = cp;
		}

		Grid(std::vector<std::string> inp, int num_cycles){

			x_bounds = std::make_pair(-1*inp[0].size()/2 - num_cycles, inp[0].size()/2 + num_cycles);
			y_bounds = std::make_pair(-1*inp[0].size()/2 - num_cycles, inp[0].size()/2 + num_cycles);
			z_bounds = std::make_pair(-1 - num_cycles - 2, 1 + num_cycles + 2);
			w_bounds = std::make_pair(-1 - num_cycles - 2, 1 + num_cycles + 2);
			
			std::vector<int> init_line(x_bounds.second - x_bounds.first, 0);
			std::vector<std::vector<int> > init_plane(y_bounds.second - y_bounds.first, init_line);
			std::vector<std::vector<std::vector<int> > >init_grid(z_bounds.second - z_bounds.first, init_plane);
			std::vector<std::vector<std::vector<std::vector<int> > > > init_hypergrid(w_bounds.second - w_bounds.first, init_grid);
			grid = init_hypergrid;
		}

		void initialize_plane(std::vector<std::string> init){
			int w_dim = 0 - w_bounds.first - 1;
			int z_dim = 0 - z_bounds.first - 1;
			int y_init = (grid[0].size() - init.size())/2;
			int x_init = (grid[0][0].size() - init[0].size())/2;

			for(int i = 0 ; i < init.size() ; i++){
				for(int j = 0 ; j < init[0].size() ; j++){
					if(init[i][j] == '#')
						grid[w_dim][z_dim][y_init+i][x_init+j] = 1;
					else
						grid[w_dim][z_dim][y_init+i][x_init+j] = 0;
				}	
			}
		}

		int apply_rule(int x, int y, int z, int w){

			int x_0 = fmax(0, x-1);
			int x_n = fmin(x+1, grid[0][0][0].size()-1);

			int y_0 = fmax(0, y-1);
			int y_n = fmin(y+1, grid[0][0].size()-1);

			int z_0 = fmax(0, z-1);
			int z_n = fmin(z+1, grid[0].size()-1);

			int w_0 = fmax(0, w-1);
			int w_n = fmin(w+1, grid.size()-1);

			int active_count = 0;
			for(int m = w_0 ; m <= w_n ; m++){
				for(int i = z_0 ; i <= z_n ; i++){
					for(int j = y_0 ; j <= y_n ; j++){
						for(int k = x_0 ; k <= x_n ; k++){
							if((k == x) && (j == y) && (i == z) && (m == w)) // cell doesnt contribute to its own nbrhood
								continue;
							active_count += grid[m][i][j][k];
						}
					}
				}		
			}

			if((grid[w][z][y][x] == 0) && (active_count == 3))	
				return 1; 
			if((grid[w][z][y][x] == 1) && ((active_count == 2) || (active_count == 3)))
				return 1;

			return 0;
		}

		void update_grid(){
			std::vector<std::vector<std::vector<std::vector<int> > > >copy(grid);
			for(int m = 0 ; m < grid.size() ; m++){
				for(int i = 0 ; i < grid[0].size() ; i++){
					for(int j = 0 ; j < grid[0][0].size() ; j++){
						for(int k = 0 ; k < grid[0][0][0].size() ; k++){
							copy[m][i][j][k] = apply_rule(k, j, i, m);
						}
					}
				}
			}
			grid = copy;
		}
		
		int count_active(){
			int count = 0;
			for(int m = 0 ; m < grid.size() ; m++){
				for(int i = 0 ; i < grid[0].size() ; i++){
					for(int j = 0 ; j < grid[0][0].size() ; j++){
						for(int k = 0 ; k < grid[0][0][0].size() ; k++){
							count += grid[m][i][j][k];
						}
					}
				}
			}
			return count;	
		}
};

int main(){

	std::ifstream infile;
	infile.open("day_17_input.txt");
	std::string line;

	std::vector<std::string> inp;

	while(std::getline(infile, line))
		inp.push_back(line);
	

	int num_cycles = 6;
	Grid grid(inp, num_cycles);
	grid.initialize_plane(inp);

	for(int i = 0 ; i < num_cycles ; i++)
		grid.update_grid();

	int ans = grid.count_active();

	std::cout << ans << std::endl;
	infile.close();

	return 0;
}

