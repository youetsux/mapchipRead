#pragma once
#include "Map.h"


namespace GLOBAL_SET {
	Size WORLD_CHIP_SIZE;
	Size CHR_RENDER_SIZE{ 32, 32 };
	Size WORLD_SIZE{ CHR_RENDER_SIZE.x * GLOBAL_SET::WORLD_CHIP_SIZE.x, CHR_RENDER_SIZE.y * GLOBAL_SET::WORLD_CHIP_SIZE.y };
	Size SCREEN_SIZE{ WORLD_SIZE / 2 };
}




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
