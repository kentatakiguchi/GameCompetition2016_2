#ifndef BOUNDING_BOX_H_
#define BOUNDING_BOX_H_


#include "../../Math/Math.h"
#include "Body.h"


class BoundingBox : public Body {
public:
	//�l�p�̔�����쐬����(������s���ꍇ) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2)
	BoundingBox(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight);
	//�l�p�̔�����쐬����(������s�����ǂ������w�肷��ꍇ) (true�Ȃ�s���Afalse�Ȃ�s��Ȃ�) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2) isEnabled:��������邩�ǂ���(bool)
	BoundingBox(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight,bool isEnabled);
	//�l�p�̔�����쐬����(������s��Ȃ��ꍇ)
	BoundingBox();

	float getWidth() {
		Vector2 lengthVectWidth1 = Vector2((component_.point[0].x + component_.point[2].x) / 2, (component_.point[0].y + component_.point[2].y) / 2);
		Vector2 lengthVectWidth2 = Vector2((component_.point[1].x + component_.point[3].x) / 2, (component_.point[1].y + component_.point[3].y) / 2);
		Vector2 lengthVectMain = CreateVector(lengthVectWidth1, lengthVectWidth2);
		return lengthVectMain.Length();
	}
	float getHeight() {
		Vector2 lengthVectHeight1 = Vector2((component_.point[0].x+component_.point[1].x)/2, (component_.point[0].y + component_.point[1].y) / 2);
		Vector2 lengthVectHeight2 = Vector2((component_.point[2].x + component_.point[3].x) / 2, (component_.point[2].y + component_.point[3].y) / 2);
		Vector2 lengthVectMain = CreateVector(lengthVectHeight1,lengthVectHeight2);
		return lengthVectMain.Length();
	}
	Vector2 getSize() {
		return Vector2(getWidth(), getHeight());
	}
	virtual bool intersects( IBodyPtr & other)  override { 
		return other->intersects(*this);
		//return intersects(other);
	}//other��Body�ɂȂ��Ă���
	//�g�p���Ȃ�
	//virtual bool intersects(BoundingSphere& other) override{ return false; }
	////�g�p���Ȃ�
	//virtual bool intersects(Capsule& other) override { return false; }
	////�g�p���Ȃ�
	//virtual bool intersects(Model& other) override { return false; }
	// ���g(Box)�Ƒ���(Box)�̔��� other:���肵��������(BoundingBox) return:���茋��(bool)
	virtual bool intersects(BoundingBox & other) override;
	// ���g(Box)�Ƒ���(Capsule)�̔��� other:���肵��������(BoundingCapsule) return:���茋��(bool)
	virtual bool intersects(BoundingCapsule & other) override;
	virtual bool intersects(BoundingSegment & other) override;
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
	virtual void draw(int spriteID, Matrix inv) const override;
	virtual void draw(int spriteID, Matrix inv,int width,int height) const override;
	virtual void draw(int spriteID,int rotation, Matrix inv) const override;
	BoundingBox movePos(Vector2& position) {
		return BoundingBox();
	}
	//���g(Box)���ړ����� position:�ړ���(Vector2) return:�ړ���������(BoundingBox)
	virtual IBodyPtr translate(const Vector2& position) const;
	//���g(Box)��ό`���� topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2) return:�ό`��������(BoundingBox)
	BoundingBox transform(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight) const;
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

	//���g(Box)�̒����Ƒ���(Capsule)�̐������������Ă��邩�𒲂ׂ�Apoint��Component�̕��𗘗p���� other:����̔���(BoundingCapsule) point1:���g�̂ǂ̓_���n�_�Ƃ��邩(int) point2:���g�̂ǂ̓_���I�_�Ƃ��邩(int)
	bool isIntersectOtherRayToThisLine(BoundingCapsule & other, int point1, int point2);
	//���g(Box)�̐����Ƒ���(Capsule)�̒������������Ă��邩�𒲂ׂ�Apoint��Component�̕��𗘗p���� other:����̔���(BoundingCapsule) point1:���g�̂ǂ̓_���n�_�Ƃ��邩(int) point2:���g�̂ǂ̓_���I�_�Ƃ��邩(int)
	bool isIntersectThisRayToOtherLine(BoundingCapsule & other, int point1, int point2);



public:

	//intersects���g�����ǂ��� true:���肷�� false:���肵�Ȃ�



};

#endif