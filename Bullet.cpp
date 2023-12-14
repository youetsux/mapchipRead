#include "stdafx.h"
#include "Bullet.h"
#include "camera2D.h"
#include "GameSetting.h"



namespace {
	const double DEF_BULLET_SPEED{ 300 };
}



Bullet::Bullet(String _AssetName, SizeF _size)
	:GameChara(),isHit_(false),assetName_(_AssetName),size_(_size)
{
	pos_ = {-10, -10};
	speed_ = DEF_BULLET_SPEED;
	tex_ = TextureAsset(assetName_);
	SetCharaRect(size_);
	moveDir_ = { 0, 0 };
	isAlive_ = true;
}

void Bullet::Initialize()
{
}

void Bullet::Release()
{
}


void Bullet::Update()
{
	if (isAlive_) {
		pos_ = pos_ + speed_ * Scene::DeltaTime() * moveDir_;
		SetCharaRect(size_);
		isHit_ = false;
	}
}

void Bullet::Draw()
{
	if (isAlive_) {
		Vec2 renderPos = CAMERA2D::GetScreenPosFromWorldPos(pos_);
		tex_.resized(size_).rotated(0).drawAt(renderPos);
		RectF renderRect = { CAMERA2D::GetScreenPosFromWorldPos(rect_.pos) , size_ };
		renderRect.drawFrame(1, 1, Palette::Red);
	}
}
