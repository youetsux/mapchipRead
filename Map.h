#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class Map
{
	vector<vector<int>> mapArray;
	Texture tex_;
public:
	Map();
	~Map();
	void SetTexture(String _assetName) { tex_ = TextureAsset(_assetName); }
	void Load(string _fileName);
	int Get(int x, int y) { return mapArray[y][x]; }
	int Get(Point p) { return mapArray[p.y][p.x]; }
	Size GetMapSize();
	void Draw();
};

