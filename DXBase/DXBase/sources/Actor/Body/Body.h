#pragma once

#include "IBody.h"

class Body : public IBody{
public:
	Body(CollisionType type = CollisionType::NoneCol, bool enable = true, Vector2 pos = Vector2(0, 0), Matrix mat = Matrix::Identity, float rad = 0, float length = 0, float width = 0, float height = 0) :
		type_(type), enabled_(enable), position_(pos), mat_(mat), radius_(rad), length_(length), width_(width), height_(height) {}
	virtual ~Body() {}
	// IBody ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
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
public:
	CollisionType type_;

	Vector2 position_;
	Vector2 previousPosition_;

	Matrix mat_;
	float radius_;
	float length_;
	float width_;
	float height_;
	bool enabled_;
};

