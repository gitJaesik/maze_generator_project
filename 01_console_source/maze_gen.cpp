#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <algorithm>
#include <array>
#include <fstream>

using namespace std;

int maze_way[300][300];

class Maze {
private:
	int mazeWidth;
	int mazeHeight;
	bool bIsWidthEven;
	bool bIsHeightEven;

	pair<int, int> mazeStart;
	pair<int, int> mazeEnd;
	string mazeFileName;
	
public:
	string chr_wall = "#";
	string chr_empty = " ";
	string chr_solve = ".";

	int maze_order[4] = { 1, 2, 4, 8 };

	Maze() {
		bIsWidthEven = false;
		bIsHeightEven = false;

		memset(maze_way, 0, sizeof(maze_way));

		// 초기화
		mazeWidth = 18;
		mazeHeight = 10;

		mazeStart.first = 0;
		mazeStart.second = 0;
		mazeEnd.first = 0;
		mazeEnd.second = 0;

		mazeFileName = "ouput.txt";
	}

	void setMazeFileName(string filename) {
		mazeFileName = filename;
	}

	int setStart(int y, int x) {
		if (y < mazeHeight && y >= 0 && x < mazeWidth && x >= 0) {
			mazeStart.first = y;
			mazeStart.second = x;

			return 1;
		}
		else {
			cout << "input right number" << endl;
			return 0;
		}
	}

	int setEnd(int y, int x) {
		if (y < mazeHeight && y >= 0 && x < mazeWidth && x >= 0) {
			mazeEnd.first = y;
			mazeEnd.second = x;
			return 1;
		}
		else {
			cout << "input right number" << endl;
			return 0;
		}
	}

	void setMazeWidth(int value) {
		if (value % 2 == 0) {
			mazeWidth = value / 2 - 1;
			bIsWidthEven = true;
		}
		else {
			mazeWidth = value / 2;
		}
	}

	void setMazeHeight(int value) {
		if (value % 2 == 0) {
			mazeHeight = value / 2 - 1;
			bIsHeightEven = true;
		}
		else {
			mazeHeight = value / 2;
		}
	}

	void road_make(int y, int x) {

		random_shuffle(&maze_order[0], &maze_order[4]);
		int orderIndex = 0;

		int xx;
		int yy;
		bool noway;

		while (orderIndex <= 3) {
			xx = x;
			yy = y;
			noway = true;

			switch (maze_order[orderIndex]) {
			case 1:
				if (y < mazeHeight - 1) {
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
				if (x < mazeWidth - 1) {
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

			// 이동할 방향의 미로가 이미 다른 방향으로 뚫려있는지 확인
			if (!noway && maze_way[yy][xx] == 0) {
				maze_way[y][x] += maze_order[orderIndex];
				maze_way[yy][xx] += (8 / maze_order[orderIndex]);
				road_make(yy, xx);
			}
			else {
				orderIndex += 1;
			}
		}
	}

	void maze_vertical_info_print(int y, bool bEvenCase, string& str) {
		string pchar = "";
		for (int j = 0; j < mazeWidth; j++) {
			pchar = chr_wall;

			if (maze_way[y][j] >= 8) {
				pchar += chr_empty;
			}
			else {
				pchar += chr_wall;
			}
			cout << pchar;
			str.append(pchar);
		}
		
		// Even이면 마지막 한 줄을 추가하기
		if (bEvenCase == true) {
			cout << pchar[1];
			str.append(pchar.substr(1));
		}
	}

	void maze_horize_info_print(int y, bool bEvenCase, string& str) {
		string pchar = "";
		for (int j = 0; j < mazeWidth; j++) {
			if (maze_way[y][j] % 4 >= 2) {
				pchar = chr_empty;
			}
			else {
				pchar = chr_wall;
			}

			pchar += chr_empty;

			if (y == mazeStart.first && j == mazeStart.second) {
				pchar = "S" + chr_empty;
			}

			cout << pchar;
			str.append(pchar);
		}

		// Even이면 마지막 한 줄을 추가하기
		if (bEvenCase == true) {
			cout << pchar[1];
			str.append(pchar.substr(1));
		}
	}

	void maze_print() {

		string allString = "";

		string pchar = "";

		for (int i = 0; i < mazeHeight; i++) {
			
			maze_vertical_info_print(i, bIsWidthEven, allString);

			cout << chr_wall + "\n";
			allString.append(chr_wall + "\n");

			maze_horize_info_print(i, bIsWidthEven, allString);

			// 마지막 위치
			if (bIsHeightEven == false && i == mazeHeight - 1) {
				cout << "G\n";
				allString.append("G\n");
			}
			else {
				cout << chr_wall + "\n";
				allString.append(chr_wall + "\n");
			}

			if (bIsHeightEven == true && i == mazeHeight - 1) {
				maze_horize_info_print(i, bIsWidthEven, allString);

				// 마지막 위치
				if (i == mazeHeight - 1) {
					cout << "G\n";
					allString.append("G\n");
				}
				else {
					cout << chr_wall + "\n";
					allString.append(chr_wall + "\n");
				}
			}

		}

		for (int j = 0; j <= mazeWidth * 2 + (bIsWidthEven == true ? 1 : 0) ; j++) {
			cout << chr_wall;
			allString.append(chr_wall);
		}
		cout << "\n";
		allString.append("\n");

		ofstream out(mazeFileName);
		out << allString;
		out.close();
	}

	void maze_start() {
		road_make(mazeStart.first, mazeStart.end);
		maze_print();
	}
};


int main() {
	Maze mz;
	mz.setMazeHeight(10);
	mz.setMazeWidth(10);
	mz.setStart(1, 0);
	//mz.setMazeFileName("C:\\Users\\Phee\\Documents\\Visual Studio 2015\\Projects\\pnp\\output.txt");
	mz.setMazeFileName("output.txt");
	mz.maze_start();
	return 0;
}
