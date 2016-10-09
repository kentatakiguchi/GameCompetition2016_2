#pragma once

#include "../../Math/Math.h"
#include "Body.h"


class BoundingBox : public Body {
public:
	BoundingBox(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight);

	explicit BoundingBox();

	virtual bool intersects(BoundingSphere& other) override { return false; }
	virtual bool intersects(Capsule& other) override { return false; }
	virtual bool intersects(Model& other) override { return false; }

	// Body を介して継承されました
	virtual bool intersects(BoundingBox & other) override;
	
	virtual bool intersects(BoundingCapsule & other) override;

	virtual void update(const Vector2 & center) override;
	virtual void update(const Vector3& center) override {}

	virtual void debug() const override;

	BoundingBox translate(const Vector2& position) const;

	BoundingBox transform(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight) const;

	bool isIntersectOtherRayToThisLine(BoundingCapsule & other, int point1, int point2);
	bool isIntersectThisRayToOtherLine(BoundingCapsule & other, int point1, int point2);


	void draw() const;

public:
	struct Component {
		// [0]:左上 [1]:右上 [2]:左下 [3]:右下
		Vector2 point[4];

		Component(Vector2 topLeft, Vector2 topRight, Vector2 bottomLeft, Vector2 bottomRight) {
			point[0] = topLeft;
			point[1] = topRight;
			point[2] = bottomLeft;
			point[3] = bottomRight;

		}
	};

	Component component_;

	bool enabled;

};

