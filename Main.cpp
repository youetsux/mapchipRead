# include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include <array>
#include "Player.h"
#include "camera2D.h"
#include "Map.h"
#include "GameSetting.h"

namespace GS = GameSetting;

void Main()
{

	GS::InitializeGameData("mapdata.csv");
	
	TextureAsset::Register(U"PLAYER", U"SpaceShips\\C-10.png");
	TextureAsset::Register(U"MAPCHIP", U"bg.png");
	TextureAsset::Register(U"PBULLET", U"SpaceShips\\RedBullet.png");
	TextureAsset::Register(U"EXPLOSION", U"explosion.png");


	Window::Resize(GS::SCREEN_SIZE);


	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	Texture mapchip = TextureAsset(U"MAPCHIP");

	//GameSetting::MAPDATA.Load("mapdata.csv");

	std::array<RectF, 4> mapRects{
		RectF(0 * GS::CHR_RENDER_SIZE.x,0 * GS::CHR_RENDER_SIZE.y,GS::CHR_RENDER_SIZE),
		RectF(6 * GS::CHR_RENDER_SIZE.x,6 * GS::CHR_RENDER_SIZE.y,GS::CHR_RENDER_SIZE),
		RectF(2 * GS::CHR_RENDER_SIZE.x,6 * GS::CHR_RENDER_SIZE.y,GS::CHR_RENDER_SIZE),
		RectF(7 * GS::CHR_RENDER_SIZE.x,3 * GS::CHR_RENDER_SIZE.y,GS::CHR_RENDER_SIZE)
	};

	
	Player* player = new Player;
	player->Initialize();
	GS::ObjList.push_front(player);

	while (System::Update())
	{
		//const double MoveSpeed = 256/10.0;

		for (auto j = 0; j < GS::WORLD_CHIP_SIZE.y; j++)
		{
			for (auto i = 0; i < GS::WORLD_CHIP_SIZE.x; i++)
			{
				//配列になってるオブジェクトのワールド座標
				Vec2 wPos{ i * GS::CHR_RENDER_SIZE.x, j * GS::CHR_RENDER_SIZE.y };
				//スクリーン座標に変換
				Vec2 scrPos = CAMERA2D::GetScreenPosFromWorldPos(wPos);
				mapchip(mapRects[GS::MAPDATA->Get(i, j)]).draw(scrPos);
			}
		}

		for (auto& theI : GS::ObjList)
		{
			theI->Update();
		}

		//player->Update();
		CAMERA2D::SetCameraPos(player->GetPosition());
		CAMERA2D::UpdateCamera();
		//player->Draw();
		for (auto& theI : GS::ObjList)
		{
			theI->Draw();
		}
	}
}


