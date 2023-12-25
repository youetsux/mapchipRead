#pragma once
#include "Map.h"

class GameChara;


//画面の大きさやキャラクタサイズ、マップデータなど
//ゲームのセッティングをつかさどるクラス
namespace GameSetting
{
	//enum direction;

	extern Size WORLD_CHIP_SIZE; //ワールド上のチップ数WxH(個）
	extern Size CHR_RENDER_SIZE; //キャラクタのレンダーサイズWxH(pix)
	extern Size WORLD_SIZE; //ワールドのサイズWxH(pix)
	extern Size SCREEN_SIZE;//スクリーンサイズWxH(pix)
	extern Map *MAPDATA;
	extern std::vector<GameChara*> ObjList;
	extern std::vector<GameChara*> AddObjList;
	extern std::vector<GameChara*> delObjList;
	extern void AddUpdateList(GameChara* _obj);
	extern bool LIST_UPDATE_FLAG;
	extern void EraseObjects();
	void InitializeGameData(std::string _fileName);
};

