#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include "gdiplustypes.h"

using namespace std;

#pragma once
class CMazeFinder
{
public:
	CMazeFinder();
	~CMazeFinder();
	int maze[256][256];
	bool check[256][256];
private:
	string strFilePath;
public:
	void setFilePath(string filepath);
	int findMaze();
	string mazeGraph();

	struct Point {
		int x, y;
		Point() { x = 0; y = 0; }
		Point(int x, int y) :x(x), y(y) {}
	};

	Point shortestPaths[256][256];

	vector<int> answers;

	int shortestPathDepth;

	int getOtherSolvePaths(int y, int x, int depth);
	int otherSolveNum;
	Point mazeStart;
	Point mazeEnd;

	int dx[4] = { 0, 0, -1, 1 };
	int dy[4] = { 1, -1, 0, 0 };
	int mazeWidth;
	int mazeHeight;
	int m_stackCount;
	bool m_bDfsBreak;
	vector<int> getOtherPaths();
};

