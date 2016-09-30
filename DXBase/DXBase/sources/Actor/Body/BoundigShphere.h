#pragma once

#include "../../Math/Math.h"
#include "Body.h"

class BoundingSphere : public Body{
public:
	BoundingSphere(const Vector3& center, float radius);

	explicit BoundingSphere(float radius = 0.0f);

	// Body ����Čp������܂���
	virtual bool intersects(BoundingSphere & other) override;

	virtual bool intersects(Capsule & other) override;

	virtual bool intersects(Model & other) override;

	virtual void update(const Vector3 & center) override;

	virtual void debug() const override;

	BoundingSphere translate(const Vector3& position) const;

	BoundingSphere transform(const Matrix& matrix) const;

	void draw() const;

public:
	struct Component {
		// ���S���W
		Vector3	center_;
		// ���a
		float	radius_;

		Component(Vector3 center, float	radius) {
			center_ = center;
			radius_ = radius;
		}
	};

	Component component_;

	bool enabled;

};

