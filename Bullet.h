#pragma once
#include "GameChara.h"


class Bullet :
    public GameChara
{

	enum direction
	{
		UP, LEFT, DOWN, RIGHT, NONE
	};

	direction imgDir_;//画像の向き
	bool isHit_;
	String assetName_;
	SizeF size_;
	double coolTime_;
	RectF worldRect_;//世界座標の境界
	bool IsHitStaticObjects();
public:
	Bullet(String _AssetName, SizeF _size);
	~Bullet() {}//解放処理ここでやる？
	void Initialize();
	void Release();//それともここでやる？
	void Update() override;
	void Draw() override;
};

