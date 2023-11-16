#include "stdafx.h"
#include "Player.h"


Player::Player()
	:GameChara()
{
	pos_ = Scene::Center()/2;
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
	//UP,RIGHT,LEFT,DOWN,RIGHT,NONE
	Vec2 DIRS[5]{ {0,-1},{1,0},{0,1},{1,0},{0,0} };
	direction d = GetDirection();
	Vec2 mdir = DIRS[NONE];
	switch (d)
	{
	case UP:
		mdir = DIRS[UP];
		break;
	case LEFT:
		mdir = DIRS[LEFT];
		break;
	case RIGHT:
		mdir = DIRS[RIGHT];
		break;
	case DOWN:
		mdir = DIRS[DOWN];
		break;
	default:
		mdir = DIRS[NONE];
		break;
	}

	moveDir_ = mdir;
	pos_ = pos_ + speed_ * Scene::DeltaTime() * moveDir_;
	SetCharaRect(PLAYER_RECT_SIZE);
}

void Player::Draw()
{
	if (isAlive_) {
		tex_.resized(PLAYER_CHR_SIZE).drawAt(pos_);
		rect_.drawFrame(1, 1, Palette::Red);
	}
}

