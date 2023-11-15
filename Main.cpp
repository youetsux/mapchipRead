# include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include <array>

const Size SCREEN_SIZE{ 256,192 };
const Size WORLD_SIZE{ 256 * 2, 192 * 2 };
const SizeF CHR_RENDER_SIZE{ 32, 32 };
constexpr Size WORLD_CHIP_SIZE{ 16,12 }; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか


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
		for (auto j = 0; j < WORLD_CHIP_SIZE.y; j++)
		{
			for (auto i = 0; i < WORLD_CHIP_SIZE.x; i++)
			{
				Vec2 wPos{ i * CHR_RENDER_SIZE.x, j * CHR_RENDER_SIZE.y };
				mapchip(mapRects[CHR_MAP[j][i]]).draw(wPos);
			}
		}
	}
}


