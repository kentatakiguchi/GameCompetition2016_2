#pragma once

#include "../../Math/Vector3.h"

class Ray {
public:
	// コンストラクタ
	Ray(const Vector3& position, const Vector3& direction);
	// デフォルトコンストラクタ
	Ray();
public:
	// 座標
	Vector3 position;
	// 方向
	Vector3 direction;
};