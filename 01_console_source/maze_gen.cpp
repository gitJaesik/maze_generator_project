#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <algorithm>
#include <array>

using namespace std;

int maze_way[300][300];
bool maze_sway[300][300];
unsigned seed;

class Maze {
public:
	string chr_wall = "бс";
	string chr_empty = "бр";
	string chr_solve = "б█";
	int maze_width = 18;
	int maze_height = 10;
	bool view_solution;

	//vector<int> maze_order = { 1, 2, 4, 8 };
	//vector<vector<int>> maze_way;
	//vector<vector<int>> maze_sway;

	int maze_order[4] = { 1, 2, 4, 8 };


	bool maze_solved;

	Maze() {
		maze_solved = false;
		view_solution = true;

		memset(maze_way, 0, sizeof(maze_way));
		memset(maze_sway, false, sizeof(maze_sway));

	}

	void road_make(int y, int x) {
		if (!maze_solved && view_solution) {
			maze_sway[y][x] = true;
		}

		if (x == maze_width - 1 && y == maze_height - 1) {
			maze_solved = true;
		}
		
		//shuffle(maze_order.begin(), maze_order.end(), std::default_random_engine(seed));
		random_shuffle(&maze_order[0], &maze_order[4]);
		int oo = 0;

		int xx;
		int yy;
		bool noway;

		while (oo <= 3) {
			xx = x;
			yy = y;
			noway = true;

			switch (maze_order[oo]) {
			case 1:
				if (y < maze_height - 1) {
					yy += 1;
					noway = false;
				}
				break;
			case 2:
				if (x > 0) {
					xx -= 1;
					noway = false;
				}
				break;
			case 4:
				if (x < maze_width -1) {
					xx += 1;
					noway = false;
				}
				break;
			case 8:
				if (y > 0) {
					yy -= 1;
					noway = false;
				}
				break;
			}

			if (!noway && maze_way[yy][xx] == 0) {
				maze_way[y][x] += maze_order[oo];
				maze_way[yy][xx] += (8 / maze_order[oo]);
				road_make(yy, xx);
			}
			else {
				oo += 1;
			}
		}

		if (!maze_solved) {
			maze_sway[y][x] = false;
		}
	}

	void maze_print() {
		string pchar = "";

		for (int i = 0; i < maze_height; i++) {
			for (int j = 0; j < maze_width; j++) {
				pchar = chr_wall;

				if (maze_way[i][j] >= 8) {
					if (maze_sway[i - 1][j] && maze_sway[i][j]) {
						pchar += chr_solve;
					}
					else {
						pchar += chr_empty;
					}
				}
				else {
					pchar += chr_wall;
				}
				cout << pchar;
			}
			cout << chr_wall + "\n";

			for (int j = 0; j < maze_width; j++) {
				if (maze_way[i][j] % 4 >= 2) {
					if (maze_sway[i][j - 1] && maze_sway[i][j]) {
						pchar = chr_solve;
					}
					else {
						pchar = chr_empty;
					}
				}
				else {
					pchar = chr_wall;
				}

				maze_sway[i][j] ? pchar += chr_solve : pchar += chr_empty;

				if (i == 0 && j == 0) {
					pchar = "ss" + chr_empty;
				}

				cout << pchar;
			}
			if (i == maze_height - 1) {
				cout << "ee\n";
			}
			else {
				cout << chr_wall + "\n";
			}
		}

		//cout << chr_wall + "ee";
		for (int j = 0; j <= maze_width * 2; j++) {
			cout << chr_wall;
		}
		cout << "\n";
	}

	void maze_start() {
		road_make(0, 0);
		maze_print();
	}
};


int main() {
	// obtain a time-based seed:
	//seed = std::chrono::system_clock::now().time_since_epoch().count();
	Maze mz;
	mz.maze_start();
	return 0;
}