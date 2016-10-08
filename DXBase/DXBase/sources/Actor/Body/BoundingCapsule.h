#pragma once

#include "../../Math/Math.h"
#include "Body.h"

class BoundingCapsule : public Body {
public:
	BoundingCapsule(Vector2 startPoint, Vector2 endPoint, float capsuleRadius);

	explicit BoundingCapsule(float radius=0);

	// Body を介して継承されました
	virtual bool intersects(BoundingBox & other) override;

	virtual bool intersects(BoundingCapsule & other) override;

	virtual void update(const Vector2 & center) override;

	virtual void debug() const override;

	BoundingCapsule translate(const Vector2& position) const;

	BoundingCapsule transform(Vector2 startPoint, Vector2 endPoint, float capsuleRadius) const;

	void draw() const;
private:
	bool isIntersectOtherRayToThisLineCapsule(BoundingCapsule & other);
	bool isIntersectThisRayToOtherLineCapsule(BoundingCapsule & other);
	bool isIntersectOtherRayToThisLineBox(BoundingBox & other,int point1,int point2);
	bool isIntersectThisRayToOtherLineBox(BoundingBox & other,int point1,int point2);
public:
	struct Component {
		// [0]:始点 [1]:終点
		Vector2 point[2];
		float radius;

		Component(Vector2 startPoint, Vector2 endPoint,float capsuleRadius) {
			point[0] = startPoint;
			point[1] = endPoint;
			radius = capsuleRadius;
		}
	};

	Component component_;

	bool enabled;

};

