#ifndef BOUNDING_SEGMENT_H_
#define BOUNDING_SEGMENT_H_

#include "../../Math/Math.h"
#include "Body.h"

class BoundingSegment : public Body {
public:
	BoundingSegment() {}
	BoundingSegment(Vector2 pos, Matrix mat,  float length, bool enable);
	//�l�p�̔�����쐬����(������s���ꍇ) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2)
	float getLength() {
		return length_;
	}
	// Body ����Čp������܂���
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