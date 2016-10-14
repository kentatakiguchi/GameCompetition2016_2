#pragma once

#include "../../Math/Math.h"
#include "Body.h"

class BoundingCapsule : public Body {
public:
	//カプセルの判定を作成する(判定を行う場合) topLeft:左上の点(Vector2) topRight:右上の点(Vector2) bottomLeft:左下の点(Vector2) bottomRight:右下の点(Vector2)
	BoundingCapsule(Vector2 startPoint, Vector2 endPoint, float capsuleRadius);
	//カプセルの判定を作成する(判定を行う場合) topLeft:左上の点(Vector2) topRight:右上の点(Vector2) bottomLeft:左下の点(Vector2) bottomRight:右下の点(Vector2) isEnabled:判定をするかどうか(bool)
	BoundingCapsule(Vector2 startPoint, Vector2 endPoint, float capsuleRadius,bool isEnabled);
	//カプセルの判定を作成する(判定を行わない場合)
	explicit BoundingCapsule(float radius=-1);
	virtual bool intersects(BoundingSphere& other) { return false; }
	virtual bool intersects(Capsule& other) { return false; }
	virtual bool intersects(Model& other) { return false; }

	// Body を介して継承されました
	virtual bool intersects(BoundingBox & other) override;

	virtual bool intersects(BoundingCapsule & other) override;

	virtual void update(const Vector2 & center) override;
	virtual void update(const Vector3& center) {}

	virtual void debug() const override;

	BoundingCapsule translate(const Vector2& position) const;

	BoundingCapsule transform(Vector2 startPoint, Vector2 endPoint, float capsuleRadius) const;

	virtual void draw() const override;
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

