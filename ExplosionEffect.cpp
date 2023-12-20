#include "stdafx.h"
#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect(Vec2 _pos)
	:GameChara(_pos)
{
}

void ExplosionEffect::SetAnimationDesc(ANIMATIONDESC& _desc)
{
	frames_ = _desc.frames_;
	MAX_FRAME_ = _desc.maxFrame_;
	pos_ = pos_;
	speed_ = 0;
	String UassetName = Unicode::Widen(_desc.assetName_);
	tex_ = TextureAsset(UassetName);
	SetCharaRect(_desc.renderSize_);
	moveDir_ = { 1, 0 };
	isAlive_ = true;
}

void ExplosionEffect::Draw()
{
	if (isAlive_) {
		tex_(frames_[MAX_FRAME_]).resized(EXPLOSION_RECT_SIZE).drawAt(pos_);
		//rect_.drawFrame(1, 1, Palette::Red);
	}
}

void ExplosionEffect::Update()
{
	if (CDTimer_.IsTimeOver()) {
		frameNum_ = (frameNum_ + 1);
		{
			if (frameNum_ >= MAX_FRAME_) {
				frameNum_ = 0;
				DeActivateMe();
			}
		}
		CDTimer_.ResetTimer();
	}
	else
		CDTimer_.Update();
}



//もともとあったやつ
//frames_ = { {EXPLOSION_RECT_SIZE.x * 0,EXPLOSION_RECT_SIZE.y * 0,EXPLOSION_RECT_SIZE},
//	{EXPLOSION_RECT_SIZE.x * 1,EXPLOSION_RECT_SIZE.y * 0,EXPLOSION_RECT_SIZE},
//	{EXPLOSION_RECT_SIZE.x * 2,EXPLOSION_RECT_SIZE.y * 0,EXPLOSION_RECT_SIZE},
//	{EXPLOSION_RECT_SIZE.x * 0,EXPLOSION_RECT_SIZE.y * 1,EXPLOSION_RECT_SIZE},
//	{EXPLOSION_RECT_SIZE.x * 1,EXPLOSION_RECT_SIZE.y * 1,EXPLOSION_RECT_SIZE},
//	{EXPLOSION_RECT_SIZE.x * 2,EXPLOSION_RECT_SIZE.y * 1,EXPLOSION_RECT_SIZE},
//	{EXPLOSION_RECT_SIZE.x * 0,EXPLOSION_RECT_SIZE.y * 2,EXPLOSION_RECT_SIZE},
//	{EXPLOSION_RECT_SIZE.x * 1,EXPLOSION_RECT_SIZE.y * 2,EXPLOSION_RECT_SIZE},
//	{EXPLOSION_RECT_SIZE.x * 2,EXPLOSION_RECT_SIZE.y * 2,EXPLOSION_RECT_SIZE} };
//frameNum = 0;
//pos_ = _pos;
//speed_ = 0;
//tex_ = TextureAsset(U"EXPLOSION");
//SetCharaRect(EXPLOSION_RECT_SIZE);
//moveDir_ = { 1, 0 };
//isAlive_ = true;
