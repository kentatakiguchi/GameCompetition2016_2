#ifndef BOUNDING_CAPSULE_H_
#define BOUNDING_CAPSULE_H_

#include "../../Math/Math.h"
#include "Body.h"

class BoundingCapsule : public Body {
public:
	//�J�v�Z���̔�����쐬����(������s���ꍇ) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2)
<<<<<<< HEAD
	BoundingCapsule(Vector2 pos, Matrix mat, float rad, float length,bool enable);
	float getRadius() { return radius_; }
	float getLength(){ return length_; }

	virtual bool intersects(const BoundingBox & other) const override;
	virtual bool intersects(const BoundingCapsule & other) const override;
	virtual bool intersects(const BoundingSegment & other) const override;
	virtual bool intersects(const BoundingCircle & other) const override;
	virtual void draw(int spriteID, Matrix inv) const override;
	virtual void draw(int spriteID, int rotation, Matrix inv) const override;
	virtual IBodyPtr translate(const Vector2 & pos) const override;
	virtual IBodyPtr transform(const Matrix & mat) const override;
	virtual std::vector<Vector2> points()const override;
=======
	BoundingCapsule(Vector2 startPoint, Vector2 endPoint, float capsuleRadius);
	//�J�v�Z���̔�����쐬����(������s���ꍇ) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2) isEnabled:��������邩�ǂ���(bool)
	BoundingCapsule(Vector2 startPoint, Vector2 endPoint, float capsuleRadius,bool isEnabled);
	//�J�v�Z���̔�����쐬����(������s��Ȃ��ꍇ)
	explicit BoundingCapsule(float radius=-1);
	float getRadius() { return component_.radius; }
	float getLength(){
		Vector2 lengthVect = CreateVector(component_.point[0], component_.point[1]);
		return lengthVect.Length();
	}
	virtual bool intersects(BoundingSphere& other) { return false; }
	virtual bool intersects(Capsule& other) { return false; }
	virtual bool intersects(Model& other) { return false; }

	// Body ����Čp������܂���
	virtual bool intersects(BoundingBox & other) override;

	virtual bool intersects(BoundingCapsule & other) override;

	virtual bool intersects(BoundingSegment & other) override;

	virtual bool intersects(BoundingCircle & other) override;

	virtual void update(const Vector2 & center) override;
	virtual void update(const Vector3& center) {}

	virtual void debug() const override;

	BoundingCapsule translate(const Vector2& position) const;

	BoundingCapsule transform(Vector2 startPoint, Vector2 endPoint, float capsuleRadius) const;

	virtual void draw() const override;
	virtual void draw(Matrix inv) const override;
private:
	Vector2 CreateVector(const Vector2& p, const Vector2& q) {
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
	bool isIntersectOtherRayToThisLine(Vector2 a1,Vector2 a2,Vector2 a3,Vector2 a4)
	{
		Vector2 bc = CreateVector(a1, a2);
		Vector2 bp = CreateVector(a1, a3);
		Vector2 bq = CreateVector(a1, a4);
		Vector2 pb = CreateVector(a3, a1);
		Vector2 pq = CreateVector(a3, a4);
		Vector2 pc = CreateVector(a3, a2);
		float otherPoint1 =
			(bp.x*bc.y - bp.y*bc.x)*(bq.x*bc.y - bq.y*bc.x);
			//(a1.x - a2.x)
			//*(a3.y - a1.y)
			//+ (a1.y - a2.y)
			//*(a1.x - a3.x);
		float otherPoint2 =
			(pb.x*pq.y - pb.y*pq.x)*(pc.x*pq.y - pc.y*pq.x);
		//(a1.x - a2.x)
			//*(a4.y - a1.y)
			//+ (a1.y - a2.y)
			//*(a1.x - a4.x);

		if (otherPoint1<= 0&&otherPoint2<=0)
		{
			return true;
		}
		return false;
	}

	bool isIntersectOtherRayToThisLineSegment(BoundingSegment & other);
	bool isIntersectThisRayToOtherLineSegment(BoundingSegment & other);
	bool isIntersectOtherRayToThisLineCapsule(BoundingCapsule & other);
	bool isIntersectThisRayToOtherLineCapsule(BoundingCapsule & other);
	bool isIntersectOtherRayToThisLineBox(BoundingBox & other,int point1,int point2);
	bool isIntersectThisRayToOtherLineBox(BoundingBox & other,int point1,int point2);
public:
	struct Component {
		// [0]:�n�_ [1]:�I�_
		Vector2 point[2];
		//���a
		float radius;

		Component(Vector2 startPoint, Vector2 endPoint,float capsuleRadius) {
			point[0] = startPoint;
			point[1] = endPoint;
			radius = capsuleRadius;
		}
	};

	Component component_;

	bool enabled;

>>>>>>> parent of d3118c3... 判定系未完成状態、一旦プッシュ
};

#endif