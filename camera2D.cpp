#include "camera2D.h"

namespace CAMERA2D {
	//カメラの中心位置（ワールド座標で指定）
	Vec2 cameraPos{ SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2 };
	//カメラの原点位置（ワールド座標で指定）
	Vec2 camaraOrigin{ cameraPos - SCREEN_SIZE / 2.0 };
	RectF cameraRect{ camaraOrigin,SCREEN_SIZE };//左上がカメラ原点、幅高さがスクリーンサイズになる矩形

	void SetCameraPos(Vec2 _pos)
	{
		cameraPos = _pos;
		camaraOrigin = { cameraPos - SCREEN_SIZE / 2.0 };
		cameraRect = { camaraOrigin,SCREEN_SIZE };
	}

	Vec2 GetScreenPosFromWorldPos(Vec2 _pos)
	{
		return { _pos - camaraOrigin };
	}

	void UpdateCamera() //アップデートと言いながら、マップからはみ出ないようにしているだけ
	{
		if (cameraRect.x <= 0.0f)
			SetCameraPos({ SCREEN_SIZE.x / 2.0f , cameraPos.y });

		if (cameraRect.y <= 0.0f)
			SetCameraPos({ cameraPos.x , SCREEN_SIZE.y / 2.0f });

		if (cameraRect.x + cameraRect.w >= WORLD_SIZE.x)
			SetCameraPos({ WORLD_SIZE.x - SCREEN_SIZE.x / 2 , cameraPos.y });

		if (cameraRect.y + cameraRect.h >= WORLD_SIZE.y)
			SetCameraPos({ cameraPos.x , WORLD_SIZE.y - SCREEN_SIZE.y / 2.0f });
	}
}
