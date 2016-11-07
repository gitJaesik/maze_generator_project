#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <cstring>
#include <string>
#include <queue>
#include <vector>

using namespace std;

int maze[256][256];
bool check[256][256];

int main() {

	ifstream input("maze2.txt");
	//stringstream strStream;
	//strStream << input.rdbuf();
	//string str;
	//str = strStream.str();

	//cout << str << endl;
	string line;
	int i = 0;
	int j = 0;

	pair<int, int> start, end;
	int width, height;

	while (getline(input, line)) {
		cout << line + "\n";
		j = 0;
		while (j < line.length()) {
			if (line[j] == '#') {
				maze[i][j] = 1;
			}
			else if (line[j] == 'S') {
				start.first = i;
				start.second = j;
			}
			else if (line[j] == 'G') {
				end.first = i;
				end.second = j;
			}
			else {
				maze[i][j] = 0;
			}
			j++;
		}

		i++;
	}

	width = j;
	height = i;

	memset(check, false, sizeof(check));

	int dx[4] = { 0, 0, -1, 1 };
	int dy[4] = { 1, -1, 0, 0 };

	queue<pair<pair<int, int>, int>> q;

	q.push(make_pair(start, 0));
	check[start.first][start.second] = true;

	while (!q.empty()) {
		pair<pair<int, int>, int> p = q.front();
		q.pop();

		int y = p.first.first;
		int x = p.first.second;
		int depth = p.second;

		if (y == end.first && x == end.second) {
			cout << depth << "\n";
			break;
		}

		for (int i = 0; i < 4; i++) {
			int yy = y + dy[i];
			int xx = x + dx[i];
			if (yy >= 0 && yy < height && xx >= 0 && xx < width) {
				if (maze[yy][xx] == 0 && check[yy][xx] == false) {
					q.push(make_pair(make_pair(yy, xx), depth + 1));
					check[yy][xx] = true;
				}
			}
		}

	}

	return 0;
}
