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
	virtual bool intersects(BoundingSphere& other) { return false; }
	virtual bool intersects(Capsule& other) { return false; }
	virtual bool intersects(Model& other) { return false; }
	virtual bool intersects(BoundingBox& other) { return false; }
	virtual bool intersects(BoundingCapsule& other) { return false; }
	virtual void update(const Vector3& center) {}
	virtual void update(const Vector2& center) {}
	virtual void draw() const {}
	virtual void debug() const {}
};

