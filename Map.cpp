#include "stdafx.h"
#include "Map.h"
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;
using std::ifstream;
using std::stringstream;

Map::Map()
{
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
	string tmp;
#if 1
	Console.open();
#endif
	//読み込み
	while (getline(ifs, tmp))
	{
		rData.push_back(tmp);
	}
#if 0
	for (auto& theI : rData)
		std::cout << theI << std::endl;
#endif
	//stringからintに直して配列に入れ直し
	//取って入れて出す！
	for (auto& theI : rData)
	{
		stringstream oss(theI);
		string tmp;
		std::vector<int> vtmp;
		while (std::getline(oss, tmp, ','))
		{
			stringstream iss(tmp);
			int n;
			iss >> n;
			vtmp.push_back(n);
		}
		mapArray.push_back(vtmp);
	}
	
#if 1
	for (auto& theI : mapArray) {
		for (auto& n : theI)
			std::cout << n << " ";
		std::cout << std::endl;
	}
	Size s;
	s.x = mapArray[0].size();
	s.y = mapArray.size();
	std::cout << "MAPSIZE:(" << s.x << ", " << s.y << ")" << std::endl;
#endif
}

Size Map::GetMapSize()
{
	Size s;
	s.x = mapArray[0].size();
	s.y = mapArray.size();
	return s;
}
