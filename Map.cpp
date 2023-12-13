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
#if 0
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
	for (int i = 0; i < rData.size(); i++)
	{
		stringstream oss(rData[i]);//1行をストリームとして流す
		string tmp;//作業用変数 string->int変換用
		std::vector<int> vtmp; //変換したintの値をひたすら入れる配列
		//tmpはtemporary作業領域のことです
		while (getline(oss, tmp, ','))
		{
			stringstream iss(tmp);
			int ntmp;//整数変換用tmp
			iss >> ntmp;
			vtmp.push_back(ntmp);
		}
		mapArray.push_back(vtmp);
	}
#if 0
	Size s;
	s.x = mapArray[0].size();
	s.y = mapArray.size();
	std::cout << "MAPSIZE:(" << s.x << ", " << s.y << ")" << std::endl;
#endif
	ifs.close();
}

Size Map::GetMapSize()
{
	Size s;
	s.x = mapArray[0].size();
	s.y = mapArray.size();
	return s;
}
