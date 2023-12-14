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

class ExplosionEffect :
    public GameChara
{
	int frameNum;//今のアニメフレームは何フレーム目？
	CDTimer CDTimer_;
	vector<RectF> frames_;
public:
	ExplosionEffect(Vec2 _pos);
	~ExplosionEffect(){}
	void Draw() override;
	void Update() override;
};

