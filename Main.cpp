# include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include <array>

const Size SCREEN_SIZE{ 256,192 };
const Size WORLD_SIZE{ 256 * 2, 192 * 2 };
const SizeF CHR_RENDER_SIZE{ 32, 32 };
constexpr Size WORLD_CHIP_SIZE{ 16,12 }; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか

	namespace CAMERA2D {
		//カメラの中心位置（ワールド座標で指定）
		Vec2 cameraPos{ SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2 };
		//カメラの原点位置（ワールド座標で指定）
		Vec2 camaraOrigin{ cameraPos - SCREEN_SIZE / 2.0 };

		RectF cameraRect{ camaraOrigin,SCREEN_SIZE };//左上がカメラ原点、幅高さがスクリーンサイズになる矩形


		void SetCameraPos(Vec2 _pos)
		{
			cameraPos = _pos;
			camaraOrigin = { cameraPos - SCREEN_SIZE / 2.0 };
			cameraRect = { camaraOrigin,SCREEN_SIZE };
		}
		Vec2 GetScreenPosFromWorldPos(Vec2 _pos)
		{
			return { _pos - camaraOrigin };
		}

		void UpdateCamera() //アップデートと言いながら、マップからはみ出ないようにしているだけ
		{
			if (cameraRect.x <= 0.0f)
				SetCameraPos({ SCREEN_SIZE.x / 2.0f , cameraPos.y });

			if (cameraRect.y <= 0.0f)
				SetCameraPos({ cameraPos.x , SCREEN_SIZE.y / 2.0f });

			if (cameraRect.x + cameraRect.w >= WORLD_SIZE.x)
				SetCameraPos({ WORLD_SIZE.x - SCREEN_SIZE.x / 2 , cameraPos.y });

			if (cameraRect.y + cameraRect.h >= WORLD_SIZE.y)
				SetCameraPos({ cameraPos.x , WORLD_SIZE.y - SCREEN_SIZE.y / 2.0f });
		}
	}

void Main()
{
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

	while (System::Update())
	{
		const double MoveSpeed = 256/10.0;
		//using namespace CAMERA2D;
		if (KeyUp.pressed())
		{
			//SetCameraPos({ SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2 });
			CAMERA2D::SetCameraPos(CAMERA2D::cameraPos + MoveSpeed * Vec2{ 0, -1 }*Scene::DeltaTime());
		}
		if (KeyRight.pressed())
		{
			//SetCameraPos({ SCREEN_SIZE.x + SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2 });
			CAMERA2D::SetCameraPos(CAMERA2D::cameraPos + MoveSpeed * Vec2{ 1, 0 }*Scene::DeltaTime());
		}
		if (KeyLeft.pressed())
		{
			//SetCameraPos({ SCREEN_SIZE.x / 2, SCREEN_SIZE.y +SCREEN_SIZE.y / 2 });
			CAMERA2D::SetCameraPos(CAMERA2D::cameraPos + MoveSpeed * Vec2{ -1, 0 }*Scene::DeltaTime());
		}
		if (KeyDown.pressed())
		{
			//SetCameraPos({ SCREEN_SIZE.x + SCREEN_SIZE.x / 2, SCREEN_SIZE.y + SCREEN_SIZE.y / 2 });
			CAMERA2D::SetCameraPos(CAMERA2D::cameraPos + MoveSpeed * Vec2{ 0, 1 }*Scene::DeltaTime());
		}
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
	}
}


