#include "stdafx.h"
#include "Player.h"
#include "camera2D.h"
#include "Map.h"
#include "Bullet.h"


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
	coolTimer_ = nullptr;
	aBullet_ = {false, false, false, false, false};
}

Player::~Player()
{
	if (coolTimer_)
		delete coolTimer_;
}

void Player::Initialize()
{
	coolTimer_ = new CDTimer(BULLET_COOL_TIME);
	if (coolTimer_)
		coolTimer_->StartTimer();
	for(int i = 0; i < PLAYER_BULLET_NUM; i++) {
		Bullet* p = new Bullet(BULLET_ASSET_NAME, BULLET_RENDER_SIZE);
		p->SetMoveDir(moveDir_);
		p->SetPosition(pos_);
		p->DeActivateMe();
		bullets_.push_back(p);
		GS::ObjList.push_back(p);
	}

}

int Player::GetActiveBulle()
{
	for (int i=0;i<bullets_.size();i++)
	{
		if (bullets_[i]->isActive() == false)
		{
			return i;
		}
	}
	return -1;
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

std::array<bool, PLAYER_BULLET_NUM> Player::GetActiveBulletList()
{
	std::array<bool, PLAYER_BULLET_NUM> tmp;
	for (int i = 0; i < bullets_.size(); i++)
	{
		tmp[i] = bullets_[i]->isActive();
	}
	return tmp;
}


bool Player::IsHitStaticObjects()
{
	//マップを一通り見るよ
	for (auto j = 0; j < GS::WORLD_CHIP_SIZE.y; j++)
	{
		for (auto i = 0; i < GS::WORLD_CHIP_SIZE.x; i++) {
			if (GS::MAPDATA->Get(i, j) == 1) {
				Vec2 wPos{ i * GS::CHR_RENDER_SIZE.x, j * GS::CHR_RENDER_SIZE.y };
				RectF obst{ wPos, GS::CHR_RENDER_SIZE };
				if (this->IsMyRectHit(obst))
				{
					return true;
				}
			}
		}
	}
	return false;
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
	
	isHit_ = IsHitStaticObjects();//ヒットチェッカー関数
	//if (isHit_)
	//	pos_ = tmp;//当たってたら戻す。

	Rect screenRect{ 0,0,GS::WORLD_SIZE };
	if (isHit_ || !screenRect.intersects(rect_))
	{
		pos_ = tmp;
		SetCharaRect(PLAYER_RECT_SIZE);
	}
	//画面外に出てないかチェック
	//if (pos_.x - GS::CHR_RENDER_SIZE.x / 2 <= 0)
	//	pos_.x = GS::CHR_RENDER_SIZE.x / 2;
	//if (pos_.y - GS::CHR_RENDER_SIZE.y / 2 <= 0)
	//	pos_.y = GS::CHR_RENDER_SIZE.y / 2;
	//if (pos_.x + GS::CHR_RENDER_SIZE.x / 2 > GS::WORLD_SIZE.x)
	//	pos_.x = GS::WORLD_SIZE.x - GS::CHR_RENDER_SIZE.x / 2;
	//if (pos_.y + GS::CHR_RENDER_SIZE.y / 2 > GS::WORLD_SIZE.y)
	//	pos_.y = GS::WORLD_SIZE.y - GS::CHR_RENDER_SIZE.y / 2;


	if (KeySpace.down())
	{
		if (coolTimer_->IsTimeOver()) {
			int n = GetActiveBulle();
			if (n >= 0) {
				bullets_[n]->SetPosition(pos_);
				bullets_[n]->SetMoveDir(moveDir_);
				bullets_[n]->ActivateMe();
			}
			coolTimer_->ResetTimer();
		}
	}

	//for (auto& theI : bullets_)
	//	theI->Update();
	coolTimer_->Update();
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
		//RectF renderRect = { CAMERA2D::GetScreenPosFromWorldPos(rect_.pos) , PLAYER_RECT_SIZE };
		//renderRect.drawFrame(1, 1, Palette::Red);
	}

	//for (auto& theI : bullets_)
	//{
	//	if(theI->isAlive_)
	//		theI->Draw();
	//}
		
	//ヒット検知ランプ
	//スクリーン座標でランプ位置を指定
	Vec2 rampPos{ GS::SCREEN_SIZE.x - 50, GS::SCREEN_SIZE.y - 50 };
	if (isHit_){
		Circle{ rampPos, 5 }.drawFrame(1,1, Palette::Black);
		Circle{ rampPos, 5 }.draw(Palette::Red);
	}
	else {
		Circle{ rampPos, 5 }.drawFrame(1, 1, Palette::Black);
		Circle{ rampPos, 5 }.draw(Palette::White);
	}

	rampPos = { GS::SCREEN_SIZE.x - 30, GS::SCREEN_SIZE.y - 210 };

	for (int i = 0; i < PLAYER_BULLET_NUM; i++)
	{
		Vec2 rpos = rampPos + Vec2{0, 16 * i};
		Circle{ rpos, 5 }.drawFrame(1, 1, Palette::Black);
		if(GetActiveBulletList()[i])
			Circle{ rpos, 5 }.draw(Palette::White);
		else
			Circle{ rpos, 5 }.draw(Palette::Blue);
	}
}

