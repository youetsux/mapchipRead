﻿#pragma once
const Size SCREEN_SIZE{ 256,192 };
const Size WORLD_SIZE{ 256 * 2, 192 * 2 };
const SizeF CHR_RENDER_SIZE{ 32, 32 };
constexpr Size WORLD_CHIP_SIZE{ 16,12 }; //ちっぷがわーるどじょうにたてよこなんこずつならんでいるか

namespace CAMERA2D {
	//カメラの中心位置（ワールド座標で指定）
	Vec2 cameraPos{ SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2 };
	//カメラの原点位置（ワールド座標で指定）
	Vec2 camaraOrigin{ cameraPos - SCREEN_SIZE / 2.0 };

	RectF cameraRect{ camaraOrigin,SCREEN_SIZE };//左上がカメラ原点、幅高さがスクリーンサイズになる矩形


	void SetCameraPos(Vec2 _pos);

	Vec2 GetScreenPosFromWorldPos(Vec2 _pos);


	void UpdateCamera(); //アップデートと言いながら、マップからはみ出ないようにしているだけ

}