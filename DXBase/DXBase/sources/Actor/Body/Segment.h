#pragma once

#include "../../Math/Vector3.h"

class Segment{
public:
	Segment(const Vector3& start, const Vector3& end);
	Segment();

public:
	// �n�_
	Vector3	start;
	// �I�_
	Vector3	end;
};
