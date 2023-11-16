#pragma once
#include "GameChara.h"
#include <vector>

using std::vector;

const SizeF PLAYER_CHR_SIZE{ 32, 32 }; //がぞうさいず
const SizeF PLAYER_RECT_SIZE{ 32, 32 }; //当たり判定用のBBのサイズ
const double PLAYER_MOVE_SPEED{ PLAYER_CHR_SIZE.x * 4.5 }; //プレイヤーの動作スピード


enum direction
{
	UP, LEFT, DOWN, RIGHT, NONE
};


class Player :
    public GameChara
{
public:
	Player();
	~Player() {}//解放処理ここでやる？
	void Initialize();
	void Release();//それともここでやる？
	direction GetDirection();
	void Update() override;
	void Draw() override;
	Vec2 RenderPos;
};

