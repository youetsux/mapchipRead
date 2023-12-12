#include "stdafx.h"
#include "GameSetting.h"


namespace GameSetting
{
	Size WORLD_CHIP_SIZE{ 16,12 }; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか
	Size CHR_RENDER_SIZE{ 32, 32 };
	Size WORLD_SIZE{ CHR_RENDER_SIZE.x * WORLD_CHIP_SIZE.x, CHR_RENDER_SIZE.y * WORLD_CHIP_SIZE.y };
	Size SCREEN_SIZE{ WORLD_SIZE / 2 };
	Map MAPDATA;
};
