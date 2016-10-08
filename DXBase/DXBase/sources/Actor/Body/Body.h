#pragma once

#include <string>
#include "../../Math/Math.h"
#include "ShapeType.h"

class BoundingBox;
class BoundingCapsule;

struct BodyData {
	std::string name;
	Vector2 position;
	ShapeType type;
};

class Body
{
public:
	virtual ~Body() {}
	virtual bool intersects(BoundingBox& other) = 0;
	virtual bool intersects(BoundingCapsule& other) = 0;
	virtual void update(const Vector2& center) = 0;
	virtual void debug() const = 0;
};

