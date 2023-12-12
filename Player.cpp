#include "stdafx.h"
#include "Player.h"
#include "camera2D.h"
#include "Map.h"
#include "GameSetting.h"

namespace GS = GameSetting;


Player::Player()
	:GameChara()
{
	pos_ = GS::SCREEN_SIZE/2;
	speed_ = PLAYER_MOVE_SPEED;
	tex_ = TextureAsset(U"PLAYER");
	SetCharaRect(PLAYER_RECT_SIZE);
	moveDir_ = { 0, 0 };
	isAlive_ = true;
	isHit_ = false;
}

void Player::Initialize()
{
}

direction Player::GetDirection()
{
	if ((KeyUp | KeyW).pressed())
	{
		return UP;
	}
	else if ((KeyLeft | KeyA).pressed())
	{
		return LEFT;
	}
	else if ((KeyDown | KeyS).pressed())
	{
		return DOWN;
	}
	else if ((KeyRight | KeyD).pressed())
	{
		return RIGHT;
	}
	else
		return NONE;
}

void Player::Update()
{   //寿命短い変数は名前も少し適当でいいよ
	//UP,LEFT,DOWN,RIGHT,NONE
	Vec2 DIRS[5]{ {0,-1},{-1,0},{0,1},{1,0},{0,0} };
	direction d = GetDirection();
	static Vec2 mdir = DIRS[NONE];
	if (d != NONE)
		mdir = DIRS[d];

	moveDir_ = mdir;
	imgDir_ = d;
	Vec2 tmp = pos_;
	pos_ = pos_ + speed_ * Scene::DeltaTime() * moveDir_;
	SetCharaRect(PLAYER_RECT_SIZE);
	isHit_ = false;
	//マップを一通り見るよ
	for (auto j = 0; j < GS::WORLD_CHIP_SIZE.y; j++)
	{
		for (auto i = 0; i < GS::WORLD_CHIP_SIZE.x; i++){
			if (GS::MAPDATA.Get(i,j) == 1) {
				Vec2 wPos{ i * GS::CHR_RENDER_SIZE.x, j * GS::CHR_RENDER_SIZE.y };
				RectF obst{ wPos, GS::CHR_RENDER_SIZE };
				if (this->IsMyRectHit(obst))
				{
					isHit_ = true;
					pos_ = tmp;
					break;
				}
			}
		}
	}
	//画面外に出てないかチェック
	if (pos_.x - GS::CHR_RENDER_SIZE.x / 2 <= 0)
		pos_.x = GS::CHR_RENDER_SIZE.x / 2;
	if (pos_.y - GS::CHR_RENDER_SIZE.y / 2 <= 0)
		pos_.y = GS::CHR_RENDER_SIZE.y / 2;
	if (pos_.x + GS::CHR_RENDER_SIZE.x / 2 > GS::WORLD_SIZE.x)
		pos_.x = GS::WORLD_SIZE.x - GS::CHR_RENDER_SIZE.x / 2;
	if (pos_.y + GS::CHR_RENDER_SIZE.y / 2 > GS::WORLD_SIZE.y)
		pos_.y = GS::WORLD_SIZE.y - GS::CHR_RENDER_SIZE.y / 2;
	SetCharaRect(PLAYER_RECT_SIZE);
}

void Player::Draw()
{
	static double imgRot = 0;
	double rotAngle[5]{ 180, 90, 0, -90, 0 };
	Vec2 renderMargin{ GS::CHR_RENDER_SIZE / 2 };
	if (imgDir_ != NONE)
		imgRot = rotAngle[imgDir_];

	if (isAlive_) {
		Vec2 renderPos = CAMERA2D::GetScreenPosFromWorldPos(pos_ - renderMargin);
		tex_.resized(PLAYER_CHR_SIZE).rotated(ToRadians(imgRot)).draw(renderPos);
		RectF renderRect = { CAMERA2D::GetScreenPosFromWorldPos(rect_.pos) , PLAYER_RECT_SIZE };
		renderRect.drawFrame(1, 1, Palette::Red);
	}

	if (isHit_)
	{
		Circle{ 230, 170, 5 }.draw(Palette::Red);
	}else
		Circle{ 230, 170, 5 }.draw(Palette::White);
}

