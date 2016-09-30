#pragma once

#include "../../Math/Vector3.h"
#include "Segment.h"

class Capsule {
public:
	Capsule(const Segment& segment, float radius);
	Capsule();
	void draw() const;

public:
	Segment segment_;
	float radius_;
};