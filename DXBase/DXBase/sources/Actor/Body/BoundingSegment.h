#ifndef BOUNDING_SEGMENT_H_
#define BOUNDING_SEGMENT_H_

#include "../../Math/Math.h"
#include "Body.h"

class BoundingSegment : public Body {
public:
	BoundingSegment() {}
	BoundingSegment(Vector2 pos, Matrix mat,  float length, bool enable);
	//四角の判定を作成する(判定を行う場合) topLeft:左上の点(Vector2) topRight:右上の点(Vector2) bottomLeft:左下の点(Vector2) bottomRight:右下の点(Vector2)
	float getLength() {
		return length_;
	}
	// Body を介して継承されました
	virtual bool intersects(const IBody & other) const override { return other.intersects(*this); }
	virtual bool intersects(const BoundingBox & other) const override;
	virtual bool intersects(const BoundingCapsule & other) const override;
	virtual bool intersects(const BoundingSegment & other) const override;
	virtual bool intersects(const BoundingCircle & other) const override;
	virtual void draw(int spriteID, Matrix inv) const override;
	virtual void draw(int spriteID, int rotation, Matrix inv) const override;
	virtual IBodyPtr translate(const Vector2 & pos) const override;
	virtual IBodyPtr transform(const Matrix & mat) const override;
	virtual std::vector<Vector2> points()const override;

};

#endif