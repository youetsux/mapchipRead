#include "stdafx.h"
#include "Map.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using std::ifstream;

Map::Map()
{
	mapArray = std::vector< std::vector<int>>
	{ {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1},
		{1,0,0,0,2,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,3,3,2,0,0,0,0,0,2,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,3,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,2,0,0,0,0,0,0,0,0,3,0,1,1},
		{1,0,0,0,0,0,0,1,1,0,0,0,2,0,0,1},
		{1,0,2,0,0,2,0,1,1,2,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	} };

}

Map::~Map()
{
}

void Map::Load(string _fileName)
{
	vector<string> rData;
	//fs::path crrDir = fs::current_path();
	ifstream ifs(_fileName);
	if (ifs.fail())
	{
		System::MessageBoxOK(U"マップファイルが読めません");
		exit(1);
	}
	//ファイル読もう

}
