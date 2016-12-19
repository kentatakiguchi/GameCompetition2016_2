#pragma once

#include "IBody.h"

class Body : public IBody{
public:
	Body(CollisionType type = CollisionType::NoneCol, bool enable = true, Vector2 pos = Vector2(0, 0), Matrix mat = Matrix::Identity, float rad = 0, float length = 0, float width = 0, float height = 0) :
		type_(type), enabled_(enable), position_(pos), mat_(mat), radius_(rad), length_(length), width_(width), height_(height) {}
	virtual ~Body() {}
	// IBody ����Čp������܂���
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

