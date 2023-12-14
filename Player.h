#pragma once
#include "GameChara.h"
#include <vector>
#include "camera2D.h"
#include "GameSetting.h"
#include "CDTimer.h"


using std::vector;
namespace GS = GameSetting;
namespace {
	const SizeF PLAYER_CHR_SIZE{ 32, 32 }; //がぞうさいず
	const SizeF PLAYER_RECT_SIZE{ 32, 32 }; //当たり判定用のBBのサイズ
	const double PLAYER_MOVE_SPEED{ PLAYER_CHR_SIZE.x * 4.5 }; //プレイヤーの動作スピード
	const int PLAYER_BULLET_NUM{ 5 };
	const Size BULLET_RENDER_SIZE{ 16,16 };
	const String BULLET_ASSET_NAME{ U"PBULLET" };
	const double BULLET_COOL_TIME{ 0.3 };
}



enum direction
{
	UP, LEFT, DOWN, RIGHT, NONE
};

class Bullet;

class Player :
    public GameChara
{
	direction imgDir_;//画像の向き
	bool IsHitStaticObjects();
	bool isHit_;
	vector<Bullet*> bullets_;
	CDTimer *coolTimer_;
	int GetActiveBulle();
	std::array<bool,5> aBullet_;
public:
	Player();
	~Player();//解放処理ここでやる？
	void Initialize();
	void Release();//それともここでやる？
	direction GetDirection();
	std::array<bool, 5> GetActiveBulletList();
	void Update() override;
	void Draw() override;
};

