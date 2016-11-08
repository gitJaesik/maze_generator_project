#include "stdafx.h"
#include "MazeFinder.h"


CMazeFinder::CMazeFinder()
	: otherSolveNum(0)
	, mazeWidth(0)
	, mazeHeight(0)
	, m_stackCount(0)
	, m_bDfsBreak(false)
{
	shortestPathDepth = -1;

	mazeStart.x = -1;
	mazeStart.y = -1;
	mazeEnd.x = -1;
	mazeEnd.y = -1;

	memset(maze, 0, sizeof(maze));
}


CMazeFinder::~CMazeFinder()
{
}


void CMazeFinder::setFilePath(string filepath)
{
	strFilePath = filepath;
}


int CMazeFinder::findMaze()
{
	ifstream input(strFilePath);
	string line;
	int i = 0;
	int j = 0;

	while (getline(input, line)) {
		//cout << line + "\n";
		j = 0;
		while (j < line.length()) {
			if (line[j] == '#') {
				maze[i][j] = 1;
			}
			else if (line[j] == 'S') {
				mazeStart.y = i;
				mazeStart.x = j;
				maze[i][j] = 0;
			}
			else if (line[j] == 'G') {
				mazeEnd.y = i;
				mazeEnd.x = j;
				maze[i][j] = 0;
			}
			else {
				maze[i][j] = 0;
			}
			j++;
		}

		i++;
	}

	mazeWidth = j;
	mazeHeight = i;

	memset(check, false, sizeof(check));

	queue<pair<pair<int, int>, int>> q;

	q.push(make_pair(make_pair(mazeStart.y, mazeStart.x), 0));
	check[mazeStart.y][mazeStart.x] = true;
	shortestPaths[mazeStart.y][mazeStart.x].y = -1;
	shortestPaths[mazeStart.y][mazeStart.x].x = -1;

	while (!q.empty()) {
		pair<pair<int, int>, int> p = q.front();
		q.pop();

		int y = p.first.first;
		int x = p.first.second;
		int depth = p.second;

		if (y == mazeEnd.y && x == mazeEnd.x) {
			shortestPathDepth = depth;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int yy = y + dy[i];
			int xx = x + dx[i];
			if (yy >= 0 && yy < mazeHeight && xx >= 0 && xx < mazeWidth) {
				if (maze[yy][xx] == 0 && check[yy][xx] == false) {
					q.push(make_pair(make_pair(yy, xx), depth + 1));
					check[yy][xx] = true;
					shortestPaths[yy][xx].y = y;
					shortestPaths[yy][xx].x = x;
				}
			}
		}
	}

	// 없는 경우 return -1
	if (shortestPathDepth == -1)
		return -1;

	// 그림 적용하기

	Point SolvePoint = shortestPaths[mazeEnd.y][mazeEnd.x];

	while (SolvePoint.x != -1 || SolvePoint.y != -1)
	{
		maze[SolvePoint.y][SolvePoint.x] = 2;
		SolvePoint = shortestPaths[SolvePoint.y][SolvePoint.x];
	}


	memset(check, false, sizeof(check));
	check[mazeStart.y][mazeStart.x] = true;
	// dfs로 다른 solve pahts 찾기

	m_stackCount = 0;
	m_bDfsBreak = false;
	otherSolveNum = getOtherSolvePaths(mazeStart.y, mazeStart.x, 0);

	return 0;

}

string CMazeFinder::mazeGraph()
{
	//maze
	string strGraph;
	for (int i = 0; i < mazeHeight; i++) {
		for (int j = 0; j < mazeWidth; j++) {
			if (maze[i][j] == 1) {
				strGraph.append("#");
			}
			else if (maze[i][j] == 0) {
				strGraph.append(" ");
			}
			else if (maze[i][j] == 2) {
				strGraph.append("*");
			}
		}
		strGraph.append("\n");
	}

	strGraph.append("\n");

	return strGraph;
}


int CMazeFinder::getOtherSolvePaths(int y, int x, int depth)
{
	if (answers.size() >= 10) {
		return 0;
	}

	if (m_bDfsBreak == true) {
		return 0;
	}

	if (m_stackCount >= 700) {
		m_bDfsBreak = true;
	}

	if (y == mazeEnd.y && x == mazeEnd.x) {
		answers.push_back(depth);
		return 1;
	}

	int ret = 0;

	// dfs로 완전 탐색 실행
	for (int i = 0; i < 4; i++) {
		int yy = y + dy[i];
		int xx = x + dx[i];
		if (yy >= 0 && yy < mazeHeight && xx >= 0 && xx < mazeWidth) {
			if ((maze[yy][xx] == 0 || maze[yy][xx] == 2) && check[yy][xx] == false) {
				check[yy][xx] = true;
				m_stackCount += 1;
				ret += getOtherSolvePaths(yy, xx, depth + 1);
				m_stackCount -= 1;
				check[yy][xx] = false;
			}
		}
	}

	return ret;
}


vector<int> CMazeFinder::getOtherPaths()
{
	return answers;
}
