﻿#pragma once
#include "Map.h"


//画面の大きさやキャラクタサイズ、マップデータなど
//ゲームのセッティングをつかさどるクラス
namespace GameSetting
{
	extern Size WORLD_CHIP_SIZE; //ワールド上のチップ数WxH(個）
	extern Size CHR_RENDER_SIZE; //キャラクタのレンダーサイズWxH(pix)
	extern Size WORLD_SIZE; //ワールドのサイズWxH(pix)
	extern Size SCREEN_SIZE;//スクリーンサイズWxH(pix)
	extern Map MAPDATA;

	void InitializeGameData(std::string _fileName);
};
