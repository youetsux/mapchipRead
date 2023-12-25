#pragma once


class GameChara
{
public:
	Vec2 pos_;    //場所
	bool isAlive_; //生死
	Texture tex_;  //キャラクタの画像
	double speed_; //移動スピード
	RectF rect_;   //バウンディングボックス
	Vec2 moveDir_; //移動方向
	bool isErasable;//消していいかどうか

public:
	GameChara(Vec2 _pos);  //コンストラクタのオーバーロード
	GameChara();
	virtual ~GameChara(){}

	void SetAlive(bool _alive) { isAlive_ = _alive; }
	void SetSpeed(double _speed) { speed_ = _speed; }
	void SetMoveDir(Vec2 _movedir) { moveDir_ = _movedir; }
	void SetCharaRect(SizeF _size);
	void SetPosition(Vec2 _pos);
	Vec2 GetPosition() { return pos_; }
	RectF GetCharaRect() { return rect_; }//これを追加
	bool isActive() { return isAlive_; }//isAliveがtrueかどうか
	void DeActivateMe() { isAlive_ = false; }
	void ActivateMe() { isAlive_ = true; }
	bool IsMyRectHit(RectF _rect);
	void EraseMe() { isErasable = true; }
	bool IsEraseMe() { return(isErasable); }
	virtual void Update();
	virtual void Draw();
};

