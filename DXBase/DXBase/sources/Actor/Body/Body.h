#pragma once

#include <string>
#include "../../Math/Math.h"
#include "ShapeType.h"

class BoundingSphere;
class Capsule;
class Model;
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
	virtual bool intersects(BoundingSphere& other) = 0;
	virtual bool intersects(Capsule& other) = 0;
	virtual bool intersects(Model& other) = 0;
	virtual bool intersects(BoundingBox& other) = 0;
	virtual bool intersects(BoundingCapsule& other) = 0;
	virtual void update(const Vector3& center) = 0;
	virtual void update(const Vector2& center) = 0;
	virtual void debug() const = 0;
};

