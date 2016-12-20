#pragma once

#include <string>
#include "../../Math/Math.h"
#include "ShapeType.h"

class BoundingSphere;
class Capsule;
class Model;
class BoundingBox;
class BoundingCapsule;
class BoundingSegment;
class BoundingCircle;
class BezierCurve;

struct BodyData {
	std::string name;
	Vector2 position;
	ShapeType type;
};

class Body
{
public:
	Body() {}
	virtual ~Body() {}
	virtual bool intersects(BoundingSphere& other) { return false; }
	virtual bool intersects(Capsule& other) { return false; }
	virtual bool intersects(Model& other) { return false; }
	virtual bool intersects(BoundingBox& other) { return false; }
	virtual bool intersects(BoundingCapsule& other) { return false; }
	virtual bool intersects(BoundingSegment& other) { return false; }
	virtual bool intersects(BoundingCircle& other) { return false; }
	virtual bool intersects(BezierCurve& other) { return false; }
	virtual void update(const Vector3& center) {}
	virtual void update(const Vector2& center) {}
	virtual void update(Vector2 position) {}
	virtual void draw() const {}
	virtual void draw(Matrix inv) const {}
	virtual void draw(int spriteID, Matrix inv) const {}
	virtual void draw(int spriteID,int rotation,Matrix inv) const {}
	virtual void debug() const {}
public:
	Vector2 position_;
	Vector2 previousPosition_;
};

