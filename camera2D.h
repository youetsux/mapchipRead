#pragma once


//constexpr Size WORLD_CHIP_SIZE; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか
//constexpr Size CHR_RENDER_SIZE;
//constexpr Size WORLD_SIZE;
//constexpr Size SCREEN_SIZE;


namespace CAMERA2D {
	//カメラの中心位置（ワールド座標で指定）
	extern Vec2 cameraPos;
	//カメラの原点位置（ワールド座標で指定）
	extern Vec2 camaraOrigin;

	extern RectF cameraRect;//左上がカメラ原点、幅高さがスクリーンサイズになる矩形


	void SetCameraPos(Vec2 _pos);

	Vec2 GetScreenPosFromWorldPos(Vec2 _pos);

	void UpdateCamera(); //アップデートと言いながら、マップからはみ出ないようにしているだけ
}
