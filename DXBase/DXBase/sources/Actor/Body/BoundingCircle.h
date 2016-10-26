#ifndef BOUNDING_CIRCLE_H_
#define BOUNDING_CIRCLE_H_


#include "../../Math/Math.h"
#include "Body.h"

class BoundingCircle : public Body {
public:
	//�J�v�Z���̔�����쐬����(������s���ꍇ) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2)
	BoundingCircle(Vector2 center,float circleRadius);
	//�J�v�Z���̔�����쐬����(������s���ꍇ) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2) isEnabled:��������邩�ǂ���(bool)
	BoundingCircle(Vector2 center,float circleRadius, bool isEnabled);
	//�J�v�Z���̔�����쐬����(������s��Ȃ��ꍇ)
	BoundingCircle(float radius = -1);
	//�g�p���Ȃ�
	virtual bool intersects(BoundingSphere& other) { return false; }
	//�g�p���Ȃ�
	virtual bool intersects(Capsule& other) { return false; }
	//�g�p���Ȃ�
	virtual bool intersects(Model& other) { return false; }
	// ���g(Circle)�Ƒ���(Box)�̔��� other:���肵��������(BoundingBox) return:���茋��(bool)
	virtual bool intersects(BoundingBox & other) override;
	// ���g(Circle)�Ƒ���(Capsule)�̔��� other:���肵��������(BoundingCapsule) return:���茋��(bool)
	virtual bool intersects(BoundingCapsule & other) override;
	// ���g(Circle)�Ƒ���(Segment)�̔��� other:���肵��������(BoundingSegment) return:���茋��(bool)
	virtual bool intersects(BoundingSegment & other) override;
	// ���g(Circle)�Ƒ���(Circle)�̔��� other:���肵��������(BoundingCircle) return:���茋��(bool)
	virtual bool intersects(BoundingCircle & other) override;
	//�g�p���Ȃ�
	virtual void update(const Vector2 & center) override;
	//�g�p���Ȃ�
	virtual void update(const Vector3& center) {}
	//�g�p���Ȃ�
	virtual void debug() const override;
	//���g(Circle)���ړ����� position:�ړ���(Vector2) return:�ړ���������(BoundingCircle)
	BoundingCircle translate(const Vector2& position) const;
	//���g(Box)��ό`���� center:���S�_(Vector2) circleRadius:���a(float) return:�ό`��������(BoundingCircle)
	BoundingCircle transform(Vector2 center, float circleRadius) const;
	//����̕\��(�f�o�b�O�p)
	virtual void draw() const override;
private:
	Vector2 CreateVector(const Vector2& p, const Vector2& q){
		return Vector2(q.x - p.x, q.y - p.y);
	}
	float InnerProduct(const Vector2 &a, const Vector2 &b) {
		return (a.x*b.x + a.y*b.y);//a�Eb
	}
	float OuterProduct(const Vector2 &a, const Vector2 &b) {
		return (a.x*b.y - a.y*b.x);//a�~b
	}
	float VectorLength2(const Vector2 &v) {
		return InnerProduct(v, v);//v�Ev=|v|^2
	}
	bool isIntersectOtherRayToThisLineSegment(BoundingSegment & other);
	bool isIntersectThisRayToOtherLineSegment(BoundingSegment & other);
	bool isIntersectOtherRayToThisLineCapsule(BoundingCapsule & other);
	bool isIntersectThisRayToOtherLineCapsule(BoundingCapsule & other);
	bool isIntersectOtherRayToThisLineBox(BoundingBox & other, int point1, int point2);
	bool isIntersectThisRayToOtherLineBox(BoundingBox & other, int point1, int point2);
public:
	struct Component {
		// [0]:�n�_
		Vector2 point[1];
		//���a
		float radius;

		Component(Vector2 center,float capsuleRadius) {
			point[0] = center;
			radius = capsuleRadius;
		}
	};

	Component component_;

	bool enabled;

};

#endif