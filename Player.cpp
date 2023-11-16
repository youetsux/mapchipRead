#include "stdafx.h"
#include "Player.h"
#include "camera2D.h"


Player::Player()
	:GameChara()
{
	pos_ = Scene::Center();
	speed_ = PLAYER_MOVE_SPEED;
	tex_ = TextureAsset(U"PLAYER");
	SetCharaRect(PLAYER_RECT_SIZE);
	moveDir_ = { 0, 0 };
	isAlive_ = true;
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
	if(d!= NONE)
		mdir= DIRS[d];
	
	moveDir_ = mdir;
	imgDir_ = d;
	pos_ = pos_ + speed_ * Scene::DeltaTime() * moveDir_;
	SetCharaRect(PLAYER_RECT_SIZE);
	
}

void Player::Draw()
{
	static double imgRot = 0;
	double rotAngle[5]{ 180, 90, 0, -90, 0 };
	if(imgDir_ != NONE)
		imgRot = rotAngle[imgDir_];

	if (isAlive_) {
		Vec2 renderPos = CAMERA2D::GetScreenPosFromWorldPos(pos_);
		tex_.resized(PLAYER_CHR_SIZE).rotated(ToRadians(imgRot)).drawAt(renderPos);
		RectF renderRect = { CAMERA2D::GetScreenPosFromWorldPos(rect_.pos) , PLAYER_RECT_SIZE };
		renderRect.drawFrame(1, 1, Palette::Red);
	}
}

