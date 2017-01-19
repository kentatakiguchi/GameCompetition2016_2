#ifndef BOUNDING_SEGMENT_H_
#define BOUNDING_SEGMENT_H_

#include "../../Math/Math.h"
#include "Body.h"


class BoundingSegment : public Body {
public:
	//�l�p�̔�����쐬����(������s���ꍇ) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2)
	BoundingSegment(const Vector2& startPoint, const Vector2& endPoint);
	//�l�p�̔�����쐬����(������s�����ǂ������w�肷��ꍇ) (true�Ȃ�s���Afalse�Ȃ�s��Ȃ�) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2) isEnabled:��������邩�ǂ���(bool)
	BoundingSegment(const Vector2& startPoint, const Vector2& endPoint, bool isEnabled);
	//�l�p�̔�����쐬����(������s��Ȃ��ꍇ)
	explicit BoundingSegment();
	float getLength() {
		Vector2 lengthVect = CreateVector(component_.point[0], component_.point[1]);
		return lengthVect.Length();
	}
	virtual bool intersects( IBodyPtr & other)  override {
		return other->intersects(*this); 
	}
	//�g�p���Ȃ�
	//virtual bool intersects(BoundingSphere& other) override { return false; }
	////�g�p���Ȃ�
	//virtual bool intersects(Capsule& other) override { return false; }
	////�g�p���Ȃ�
	//virtual bool intersects(Model& other) override { return false; }
	// ���g(Box)�Ƒ���(Box)�̔��� other:���肵��������(BoundingBox) return:���茋��(bool)
	virtual bool intersects(BoundingBox & other) override;
	// ���g(Box)�Ƒ���(Capsule)�̔��� other:���肵��������(BoundingCapsule) return:���茋��(bool)
	virtual bool intersects(BoundingCapsule & other) override;
	// ���g(Box)�Ƒ���(Segment)�̔��� other:���肵��������(BoundingSegment) return:���茋��(bool)
	virtual bool intersects(BoundingSegment & other) override;
	// ���g(Box)�Ƒ���(Circle)�̔��� other:���肵��������(BoundingCircle) return:���茋��(bool)
	virtual bool intersects(BoundingCircle & other) override;
	//���g�̔���̍X�V���s��(���ݖ��g�p)
	virtual void update(const Vector2 & center) override;
	//�g�p���Ȃ�
	virtual void update(const Vector3& center) override {}
	//�g�p���Ȃ�
	virtual void debug() const override;
	//����̕\��(�f�o�b�O�p)
	virtual void draw() const override;
	virtual void draw(Matrix inv) const override;
	virtual void draw(int spriteID,Matrix inv) const override;
	virtual void draw(int spriteID, int rotation, Matrix inv)const override {
		draw(spriteID,inv);
	}

	//���g(Box)���ړ����� position:�ړ���(Vector2) return:�ړ���������(BoundingBox)
	virtual IBodyPtr translate(const Vector2& position) const;
	//���g(Box)��ό`���� topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2) return:�ό`��������(BoundingBox)
	BoundingSegment transform(const Vector2& startPoint, const Vector2& endPoint) const;
private:
	//�x�N�g���̍쐬
	Vector2 CreateVector(const Vector2& p, const Vector2& q) {
		return Vector2(q.x - p.x, q.y - p.y);
	}
	//Dot�̌v�Z
	float InnerProduct(const Vector2 &a, const Vector2 &b) {
		return (a.x*b.x + a.y*b.y);//a�Eb
	}
	//Cross�̌v�Z
	float OuterProduct(const Vector2 &a, const Vector2 &b) {
		return (a.x*b.y - a.y*b.x);//a�~b
	}
	//������2��̌v�Z
	float VectorLength2(const Vector2 &v) {
		return InnerProduct(v, v);//v�Ev=|v|^2
	}
	//���g(Box)�̒����Ƒ���(Capsule)�̐������������Ă��邩�𒲂ׂ�Apoint��Component�̕��𗘗p���� other:����̔���(BoundingCapsule) point1:���g�̂ǂ̓_���n�_�Ƃ��邩(int) point2:���g�̂ǂ̓_���I�_�Ƃ��邩(int)
	bool isIntersectOtherRayToThisLine(BoundingCapsule & other, int point1, int point2);
	//���g(Box)�̐����Ƒ���(Capsule)�̒������������Ă��邩�𒲂ׂ�Apoint��Component�̕��𗘗p���� other:����̔���(BoundingCapsule) point1:���g�̂ǂ̓_���n�_�Ƃ��邩(int) point2:���g�̂ǂ̓_���I�_�Ƃ��邩(int)
	bool isIntersectThisRayToOtherLine(BoundingCapsule & other, int point1, int point2);



public:
	//�����𐶐����邽�߂�2�_��ۑ�����

	//intersects���g�����ǂ��� true:���肷�� false:���肵�Ȃ�


};

#endif