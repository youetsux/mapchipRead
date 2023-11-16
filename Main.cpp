# include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include <array>
#include "Player.h"
#include "camera2D.h"



const SizeF CHR_RENDER_SIZE{ 32, 32 };
constexpr Size WORLD_CHIP_SIZE{ 16,12 }; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか

void Main()
{
	TextureAsset::Register(U"PLAYER", U"SpaceShips\\C-10.png");
	Window::Resize(SCREEN_SIZE);
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	std::array< std::array<int, WORLD_CHIP_SIZE.x>, WORLD_CHIP_SIZE.y>
		CHR_MAP
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

	TextureAsset::Register(U"MAPCHIP", U"bg.png");

	Texture mapchip = TextureAsset(U"MAPCHIP");

	std::array<RectF, 4> mapRects{
		RectF(0 * CHR_RENDER_SIZE.x,0 * CHR_RENDER_SIZE.y,CHR_RENDER_SIZE),
		RectF(6 * CHR_RENDER_SIZE.x,6 * CHR_RENDER_SIZE.y,CHR_RENDER_SIZE),
		RectF(2 * CHR_RENDER_SIZE.x,6 * CHR_RENDER_SIZE.y,CHR_RENDER_SIZE),
		RectF(7 * CHR_RENDER_SIZE.x,3 * CHR_RENDER_SIZE.y,CHR_RENDER_SIZE)
	};

	Player* player = new Player;

	while (System::Update())
	{
		const double MoveSpeed = 256/10.0;
		//using namespace CAMERA2D;
		//if (KeyUp.pressed())
		//{
		//	//SetCameraPos({ SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2 });
		//	CAMERA2D::SetCameraPos(CAMERA2D::cameraPos + MoveSpeed * Vec2{ 0, -1 }*Scene::DeltaTime());
		//}
		//if (KeyRight.pressed())
		//{
		//	//SetCameraPos({ SCREEN_SIZE.x + SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2 });
		//	CAMERA2D::SetCameraPos(CAMERA2D::cameraPos + MoveSpeed * Vec2{ 1, 0 }*Scene::DeltaTime());
		//}
		//if (KeyLeft.pressed())
		//{
		//	//SetCameraPos({ SCREEN_SIZE.x / 2, SCREEN_SIZE.y +SCREEN_SIZE.y / 2 });
		//	CAMERA2D::SetCameraPos(CAMERA2D::cameraPos + MoveSpeed * Vec2{ -1, 0 }*Scene::DeltaTime());
		//}
		//if (KeyDown.pressed())
		//{
		//	//SetCameraPos({ SCREEN_SIZE.x + SCREEN_SIZE.x / 2, SCREEN_SIZE.y + SCREEN_SIZE.y / 2 });
		//	CAMERA2D::SetCameraPos(CAMERA2D::cameraPos + MoveSpeed * Vec2{ 0, 1 }*Scene::DeltaTime());
		//}
		player->Update();
		CAMERA2D::SetCameraPos(player->GetPosition());
		CAMERA2D::UpdateCamera();

		for (auto j = 0; j < WORLD_CHIP_SIZE.y; j++)
		{
			for (auto i = 0; i < WORLD_CHIP_SIZE.x; i++)
			{
				//配列になってるオブジェクトのワールド座標
				Vec2 wPos{ i * CHR_RENDER_SIZE.x, j * CHR_RENDER_SIZE.y };
				//スクリーン座標に変換
				Vec2 scrPos = CAMERA2D::GetScreenPosFromWorldPos(wPos);

				mapchip(mapRects[CHR_MAP[j][i]]).draw(scrPos);
			}
		}

		player->Draw();
	}
}


