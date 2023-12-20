#pragma once
#include "GameChara.h"
#include <vector>
#include "CDTimer.h"

using std::vector;

namespace {
	const int EXPLOSION_CHR_SIZE{ 32 }; //がぞうさいず
	const SizeF EXPLOSION_RECT_SIZE{ EXPLOSION_CHR_SIZE, EXPLOSION_CHR_SIZE }; //当たり判定用のBBのサイズ
	const double EXPLOSION_MOVE_SPEED{ 0 }; //爆発エフェクトの動作スピード
	const double EXPLOSION_EXPLODE_TIME{ 4.0 }; //爆発の持続時間
	const int MAX_FRAME_NUM{ 9 };//アニメのコマ数
	const double ANIME_INTERVAL{ 1 / 10.0 };
}


struct ANIMATIONDESC
{
	vector<RectF> frames_;
	std::string assetName_;
	SizeF renderSize_;
	int maxFrame_;
	double intervalTime_;
	double animeDuration_;
};

class ExplosionEffect :
    public GameChara
{
	int frameNum_;//今のアニメフレームは何フレーム目？
	int MAX_FRAME_;
	CDTimer CDTimer_;
	vector<RectF> frames_;
	SizeF renderSize_;
public:
	
	ExplosionEffect(Vec2 _pos);
	~ExplosionEffect(){}
	void SetAnimationDesc(ANIMATIONDESC& _desc);
	void Draw() override;
	void Update() override;
};

