#pragma once

#include "../../Math/Math.h"

// �}�X�w���p�[�N���X
class Collision {
public:
	static void PushOut_Circle_Box() {}

	static bool seg_seg(const Vector2 & v1p1, const Vector2 & v1p2, const Vector2 & v2p1, const Vector2 & v2p2);
};