#pragma once

#include "../../Math/Math.h"
#include "Body.h"


class BoundingBox : public Body {
public:
	//�l�p�̔�����쐬����(������s���ꍇ) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2)
	BoundingBox(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight);
	//�l�p�̔�����쐬����(������s�����ǂ������w�肷��ꍇ) (true�Ȃ�s���Afalse�Ȃ�s��Ȃ�) topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2) isEnabled:��������邩�ǂ���(bool)
	BoundingBox(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight,bool isEnabled);
	//�l�p�̔�����쐬����(������s��Ȃ��ꍇ)
	explicit BoundingBox();
	//�g�p���Ȃ�
	virtual bool intersects(BoundingSphere& other) override { return false; }
	//�g�p���Ȃ�
	virtual bool intersects(Capsule& other) override { return false; }
	//�g�p���Ȃ�
	virtual bool intersects(Model& other) override { return false; }
	// ���g(Box)�Ƒ���(Box)�̔��� other:���肵��������(BoundingBox) return:���茋��(bool)
	virtual bool intersects(BoundingBox & other) override;
	// ���g(Box)�Ƒ���(Capsule)�̔��� other:���肵��������(BoundingCapsule) return:���茋��(bool)
	virtual bool intersects(BoundingCapsule & other) override;
	//���g�̔���̍X�V���s��(���ݖ��g�p)
	virtual void update(const Vector2 & center) override;
	//�g�p���Ȃ�
	virtual void update(const Vector3& center) override {}
	//�g�p���Ȃ�
	virtual void debug() const override;
	//����̕\��(�f�o�b�O�p)
	virtual void draw() const override;
	//���g(Box)���ړ����� position:�ړ���(Vector2) return:�ړ���������(BoundingBox)
	BoundingBox translate(const Vector2& position) const;
	//���g(Box)��ό`���� topLeft:����̓_(Vector2) topRight:�E��̓_(Vector2) bottomLeft:�����̓_(Vector2) bottomRight:�E���̓_(Vector2) return:�ό`��������(BoundingBox)
	BoundingBox transform(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight) const;
private:
	//���g(Box)�̒����Ƒ���(Capsule)�̐������������Ă��邩�𒲂ׂ�Apoint��Component�̕��𗘗p���� other:����̔���(BoundingCapsule) point1:���g�̂ǂ̓_���n�_�Ƃ��邩(int) point2:���g�̂ǂ̓_���I�_�Ƃ��邩(int)
	bool isIntersectOtherRayToThisLine(BoundingCapsule & other, int point1, int point2);
	//���g(Box)�̐����Ƒ���(Capsule)�̒������������Ă��邩�𒲂ׂ�Apoint��Component�̕��𗘗p���� other:����̔���(BoundingCapsule) point1:���g�̂ǂ̓_���n�_�Ƃ��邩(int) point2:���g�̂ǂ̓_���I�_�Ƃ��邩(int)
	bool isIntersectThisRayToOtherLine(BoundingCapsule & other, int point1, int point2);



public:
	struct Component {
		// [0]:���� [1]:�E�� [2]:���� [3]:�E��
		Vector2 point[4];

		Component(Vector2 topLeft, Vector2 topRight, Vector2 bottomLeft, Vector2 bottomRight) {
			point[0] = topLeft;
			point[1] = topRight;
			point[2] = bottomLeft;
			point[3] = bottomRight;

		}
	};
	//�l�p�𐶐����邽�߂�4�_��ۑ�����
	Component component_;

	//intersects���g�����ǂ��� true:���肷�� false:���肵�Ȃ�
	bool enabled;


};

