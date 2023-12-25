#include "stdafx.h"
#include "GameChara.h"
#include "GameSetting.h"


namespace GameSetting
{
	Size WORLD_CHIP_SIZE; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか
	Size CHR_RENDER_SIZE{ 32, 32 };
	Size WORLD_SIZE{ CHR_RENDER_SIZE.x * WORLD_CHIP_SIZE.x, CHR_RENDER_SIZE.y * WORLD_CHIP_SIZE.y };
	Size SCREEN_SIZE{ WORLD_SIZE / 2 };
	Map *MAPDATA = nullptr;
	std::vector<GameChara*> ObjList;
	std::vector<GameChara*> AddObjList;
	std::vector<GameChara*> delObjList;
	void AddUpdateList(GameChara* _obj);
	bool LIST_UPDATE_FLAG{false};
	void EraseObjects();

};


void GameSetting::EraseObjects()
{
	for (auto&& it = ObjList.begin();it!=ObjList.end();) {
		// 条件一致した要素を削除する
		if ((*it)->IsEraseMe()) {
			GameChara* gp = (*it);
			it = ObjList.erase(it);
			delObjList.push_back(gp);
			//if(gp)
			//	delete gp;
			continue;
		}
		// 要素削除をしない場合に、イテレータを進める
		else {
			++it;
		}
	}
}

void  GameSetting::AddUpdateList(GameChara* _obj)
{
	AddObjList.push_back(_obj);
	LIST_UPDATE_FLAG = true;
}

void GameSetting::InitializeGameData(std::string _fileName)
{
	MAPDATA = new Map;
	MAPDATA->Load(_fileName);
	WORLD_CHIP_SIZE = MAPDATA->GetMapSize();
	WORLD_SIZE = { CHR_RENDER_SIZE.x * WORLD_CHIP_SIZE.x, CHR_RENDER_SIZE.y * WORLD_CHIP_SIZE.y };
	SCREEN_SIZE = { WORLD_SIZE / 2 };
	LIST_UPDATE_FLAG = false;
}


