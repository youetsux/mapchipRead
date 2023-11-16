#include "stdafx.h"
#include "GameChara.h"

GameChara::GameChara(Vec2 _pos)//メンバイニシャライザ
	:pos_(_pos),isAlive_(false), speed_(0.0f), rect_({0,0,0,0 }),moveDir_({0,0})
{

}
GameChara::GameChara()
{
	pos_ = { 0,0 };
	isAlive_ = false;
	speed_ = 0.0f;
	rect_ = { 0,0,0,0 };
	moveDir_ = { 0,0 };
}
void GameChara::SetCharaRect(SizeF _size)
{
	Vec2 adjustVal = { _size.x / 2.0, _size.y / 2.0 };
	rect_ = { pos_ - adjustVal, _size.x, _size.y };
}
void GameChara::SetPosition(Vec2 _pos)
{
	pos_ = _pos;
}
//とりあえず空
void GameChara::Update()
{
}
//とりあえず空
void GameChara::Draw()
{
	Print << U"GC Draw";
}

bool GameChara::IsMyRectHit(RectF _rect)
{
	float wAB = rect_.w / 2.0 + _rect.w / 2.0;
	float hAB = rect_.h / 2.0 + _rect.h / 2.0;
	float distx = abs(rect_.center().x - _rect.center().x);
	float disty = abs(rect_.center().y - _rect.center().y);
	if (wAB > distx && hAB > disty)
		return true;
	else
		return false;
}
