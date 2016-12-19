#pragma once

#include <string>
#include "../../Math/Math.h"
#include "ShapeType.h"
#include"../Collision/Collision.h"
#include "IBodyPtr.h"
#include <vector>

class BoundingBox;
class BoundingCapsule;
class BoundingSegment;
class BoundingCircle;

enum CollisionType
{
	BoxCol,
	CapsuleCol,
	CircleCol,
	SegmentCol,
	NoneCol
};

class IBody{
public:
	virtual ~IBody() {}
	virtual bool intersects(const IBody& other) const = 0;
	virtual bool intersects(const BoundingBox& other) const  = 0;
	virtual bool intersects(const BoundingCapsule& other)const = 0;
	virtual bool intersects(const BoundingSegment& other)const  = 0;
	virtual bool intersects(const BoundingCircle& other)const = 0;
	virtual void update(float deltaTime) = 0;
	virtual void enabled(bool enabled) = 0;
	virtual Vector2 velocity()const = 0;
	virtual Vector2 cur_pos()const = 0;
	virtual Vector2 pre_pos()const = 0;
	virtual Matrix mat()const = 0;
	virtual float radius()const = 0;
	virtual float length()const = 0;
	virtual float height()const = 0;
	virtual float width()const = 0;
	virtual std::vector<Vector2> points()const = 0;
	virtual void draw(int spriteID, Matrix inv) const = 0;
	virtual void draw(int spriteID, int rotation, Matrix inv) const = 0;
	virtual IBodyPtr translate(const Vector2& pos)const = 0;
	virtual IBodyPtr transform(const Matrix& mat)const = 0;
};