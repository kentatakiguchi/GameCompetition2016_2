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
<<<<<<< HEAD
	Body(CollisionType type = CollisionType::NoneCol, bool enable = true, Vector2 pos = Vector2(0, 0), Matrix mat = Matrix::Identity, float rad = 0, float length = 0, float width = 0, float height = 0) :
		type_(type), enabled_(enable), position_(pos), mat_(mat), radius_(rad), length_(length), width_(width), height_(height) {}
	virtual ~Body() {}
	// IBody ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual bool intersects(const IBody & other) const override { return other.intersects(*this); }
	virtual void update(float deltaTime) { previousPosition_ = position_; }
	virtual void enabled(bool enabled) { enabled_ = enabled; }
	virtual Vector2 velocity()const { return position_ - previousPosition_; }
	virtual Vector2 cur_pos()const { return position_; }
	virtual Vector2 pre_pos()const { return previousPosition_; }
	virtual Matrix mat()const { return mat_; }
	virtual float radius()const { return radius_; }
	virtual float length()const { return length_; }
	virtual float height()const { return height_; }
	virtual float width()const { return width_; }
	virtual void setSegment(const Vector2& start, const Vector2& end){ 
		position_ = (start + end) / 2;
		mat_ = Matrix::CreateRotationZ(MathHelper::ACos(Vector2::Dot(Vector2::Down, (start - end).Normalize())));
		length_ = Vector2::Distance(start, end);
	}

=======
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
>>>>>>> parent of d3118c3... åˆ¤å®šç³»æœªå®ŒæˆçŠ¶æ…‹ã€ä¸€æ—¦ãƒ—ãƒƒã‚·ãƒ¥
public:
	Vector2 position_;
	Vector2 previousPosition_;
};

