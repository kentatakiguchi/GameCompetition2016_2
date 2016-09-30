#pragma once

#include "../../Math/Vector3.h"

class Segment{
public:
	Segment(const Vector3& start, const Vector3& end);
	Segment();

public:
	// 始点
	Vector3	start;
	// 終点
	Vector3	end;
};
