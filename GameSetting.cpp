#include "stdafx.h"
#include "GameSetting.h"


namespace GameSetting
{
	Size WORLD_CHIP_SIZE; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか
	Size CHR_RENDER_SIZE{ 32, 32 };
	Size WORLD_SIZE{ CHR_RENDER_SIZE.x * WORLD_CHIP_SIZE.x, CHR_RENDER_SIZE.y * WORLD_CHIP_SIZE.y };
	Size SCREEN_SIZE{ WORLD_SIZE / 2 };
	Map MAPDATA;
};

void GameSetting::InitializeGameData(std::string _fileName)
{
	MAPDATA.Load(_fileName);
	WORLD_CHIP_SIZE = MAPDATA.GetMapSize();
	WORLD_SIZE = { CHR_RENDER_SIZE.x * WORLD_CHIP_SIZE.x, CHR_RENDER_SIZE.y * WORLD_CHIP_SIZE.y };
	SCREEN_SIZE = { WORLD_SIZE / 2 };
}
