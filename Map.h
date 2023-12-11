#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;
constexpr Size WORLD_CHIP_SIZE{ 16,12 }; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか


class Map
{
	vector<vector<int>> mapArray;
public:
	Map();
	~Map();
	void Load(string _fileName);
	int Get(int x, int y) { return mapArray[y][x]; }
	int Get(Point p) { return mapArray[p.y][p.x]; }
};

