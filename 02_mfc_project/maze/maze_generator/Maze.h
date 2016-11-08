#pragma once
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

class Maze
{
public:
	Maze();
	~Maze();
private:
	int mazeWidth;
	int mazeHeight;
	bool bIsWidthEven;
	bool bIsHeightEven;
	pair<int, int> mazeStart;
	pair<int, int> mazeEnd;
	string mazeFileName;
public:
	string chr_wall;
	string chr_empty;
	int maze_order[4];
	int maze_way[256][256];
	void setMazeFileName(string filename);
	int setStart(int y, int x);
	int setEnd(int y, int x);
	void setMazeWidth(int value);
	void setMazeHeight(int value);
	void road_make(int y, int x);
	void maze_vertical_info_print(int y, bool bEvenCase, string& str);
	void maze_horize_info_print(int y, bool bEvenCase, string& str);
	void maze_print();
	void maze_start();
};

