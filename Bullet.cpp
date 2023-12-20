#include "stdafx.h"
#include "Bullet.h"
#include "camera2D.h"
#include "GameSetting.h"
#include "ExplosionEffect.h"


namespace GS = GameSetting;

namespace {
	const double DEF_BULLET_SPEED{ 300 };
	ANIMATIONDESC desc{
		{{EXPLOSION_RECT_SIZE.x * 0,EXPLOSION_RECT_SIZE.y * 0,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 1,EXPLOSION_RECT_SIZE.y * 0,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 2,EXPLOSION_RECT_SIZE.y * 0,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 0,EXPLOSION_RECT_SIZE.y * 1,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 1,EXPLOSION_RECT_SIZE.y * 1,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 2,EXPLOSION_RECT_SIZE.y * 1,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 0,EXPLOSION_RECT_SIZE.y * 2,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 1,EXPLOSION_RECT_SIZE.y * 2,EXPLOSION_RECT_SIZE},
			{EXPLOSION_RECT_SIZE.x * 2,EXPLOSION_RECT_SIZE.y * 2,EXPLOSION_RECT_SIZE}},
		"EXPLOSION",
		{32, 32},
		 9,
		2,
		4.0
	};
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
	worldRect_ = (RectF)GameSetting::WORLD_SIZE;
}

void Bullet::Initialize()
{
}

void Bullet::Release()
{
}

bool Bullet::IsHitStaticObjects()
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


void Bullet::Update()
{
	if (isAlive_) {
		pos_ = pos_ + speed_ * Scene::DeltaTime() * moveDir_;
		SetCharaRect(size_);
		isHit_ = false;
		if (!rect_.intersects(worldRect_))
		{
			pos_ = { -10,-10 };
			DeActivateMe();
		}
		if (IsHitStaticObjects()) {
			DeActivateMe();
			ExplosionEffect* p = new ExplosionEffect(pos_);
			p->SetAnimationDesc(desc);
			GS::ObjList.push_front(p);
		}
			

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
