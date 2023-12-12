# include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include <array>
#include "Player.h"
#include "camera2D.h"
#include "Map.h"


namespace GLOBAL_SET {
	Map CHR_MAP;
	extern Size WORLD_CHIP_SIZE; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか
	extern Size WORLD_SIZE;
	extern Size CHR_RENDER_SIZE;
}

using namespace GLOBAL_SET;

void Main()
{
	TextureAsset::Register(U"PLAYER", U"SpaceShips\\C-10.png");
	Window::Resize(SCREEN_SIZE);
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	TextureAsset::Register(U"MAPCHIP", U"bg.png");

	Texture mapchip = TextureAsset(U"MAPCHIP");

	
	CHR_MAP.Load("mapdata.csv");

	std::array<RectF, 4> mapRects{
		RectF(0 * CHR_RENDER_SIZE.x,0 * CHR_RENDER_SIZE.y,CHR_RENDER_SIZE),
		RectF(6 * CHR_RENDER_SIZE.x,6 * CHR_RENDER_SIZE.y,CHR_RENDER_SIZE),
		RectF(2 * CHR_RENDER_SIZE.x,6 * CHR_RENDER_SIZE.y,CHR_RENDER_SIZE),
		RectF(7 * CHR_RENDER_SIZE.x,3 * CHR_RENDER_SIZE.y,CHR_RENDER_SIZE)
	};

	Player* player = new Player;

	while (System::Update())
	{
		//const double MoveSpeed = 256/10.0;
		
		for (auto j = 0; j < WORLD_CHIP_SIZE.y; j++)
		{
			for (auto i = 0; i < WORLD_CHIP_SIZE.x; i++)
			{
				//配列になってるオブジェクトのワールド座標
				Vec2 wPos{ i * CHR_RENDER_SIZE.x, j * CHR_RENDER_SIZE.y };
				//スクリーン座標に変換
				Vec2 scrPos = CAMERA2D::GetScreenPosFromWorldPos(wPos);

				mapchip(mapRects[CHR_MAP.Get(i,j)]).draw(scrPos);
			}
		}
		player->Update();
		CAMERA2D::SetCameraPos(player->GetPosition());
		CAMERA2D::UpdateCamera();
		player->Draw();
	}
}


