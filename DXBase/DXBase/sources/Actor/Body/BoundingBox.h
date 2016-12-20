#ifndef BOUNDING_BOX_H_
#define BOUNDING_BOX_H_


#include "../../Math/Math.h"
#include "Body.h"

class BoundingBox : public Body {
public:
	BoundingBox():
		Body(CollisionType::BoxCol, false, Vector2::Zero, Matrix::Identity, 0, 0, 0, 0)
	{}
	//�l�p�̔�����쐬����(������s���ꍇ) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2)
	BoundingBox(Vector2 pos, Matrix mat, float width, float height, bool enable);

	float getWidth() {
		return width_;
	}
	float getHeight() {
		return height_;
	}
	Vector2 getSize() {
		return Vector2(width_, height_);
	}
	Vector2 getPoint(int pointNum) {
		
	}
	// Body ����Čp������܂���
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