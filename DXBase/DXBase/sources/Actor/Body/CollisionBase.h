#pragma once

#include"BoundingBox.h"
#include"BoundingCapsule.h"
#include"BoundingCircle.h"
#include"BoundingSegment.h"

class CollisionBase
{

public:
	//����𗘗p���Ȃ��ꍇ
	CollisionBase();
	//�l�p����𗘗p����ꍇ
	CollisionBase(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight);
	//�J�v�Z������𗘗p����ꍇ
	CollisionBase(Vector2& startPoint, Vector2& endPoint, float capsuleRadius);
	//�~����𗘗p����ꍇ
	CollisionBase(Vector2& center, float circleRadius);
	//��������𗘗p����ꍇ
	explicit CollisionBase(Vector2& startPoint, Vector2& endPoint);
	void setPosition(Vector2 position);
	Vector2 setSegmentPoint(Vector2& position, Vector2& startPoint, Vector2& endPoint);
	void RotateCapsule(Vector2 point1, Vector2 point2, float radius);
	void RotateSegment(Vector2 point1, Vector2 point2);
	void RotateBox(int rotation);
	void RotateFreeBox(int rotation);
	//�f�o�b�O�p�̔���\��
	void draw(Matrix inv = Matrix::Identity) const;
	//�X�v���C�g��ID��n�����ŁA�Ή������X�v���C�g��\������e�����draw���Ăяo��(BOX�ȊO�͒ʏ��draw�Ɠ���)
	void draw(int spriteID, Matrix inv = Matrix::Identity) const;
	void draw(int spriteID, int rotation, Matrix inv = Matrix::Identity) const;
	//
	void update(Vector2 position);
	//�l�p����̑傫���A�`��̕ύX
	void transform(Vector2& topLeft, Vector2& topRight, Vector2& bottomLeft, Vector2& bottomRight);
	//�J�v�Z������̑傫���A�`��̕ύX
	void transform(Vector2& startPoint, Vector2& endPoint, float capsuleRadius);
	//�~����̑傫���A�`��̕ύX
	void transform(Vector2& center, float circleRadius);
	//��������̑傫���A�`���ύX
	void transform(Vector2& startPoint, Vector2& endPoint);
	//����̈ړ�(���g�̃|�W�V�������Q��)
	void MovePos(Vector2 & position);
	//����̈ړ�
	void translate(Vector2 position);
	//�ΏۂƓ������Ă��邩  other:���肵��������(CollisionBase) return:���茋��(bool)
	bool intersects(CollisionBase& other);
	//�ǂ̎�ނ̓����蔻��𗘗p���Ă��邩���擾 return:����̎��(CollisionType)
	CollisionType GetType() const;
	//�l�p������擾/�l�p����ȊO�𗘗p���Ă���ꍇ�A���삵�Ȃ��l�p�����Ԃ� return:���g�̎l�p����(BoundingBox)
	CollisionBase GetBox() const;
	//�J�v�Z��������擾/�J�v�Z������ȊO�𗘗p���Ă���ꍇ�A���삵�Ȃ��J�v�Z�������Ԃ� return:���g�̃J�v�Z������(BoundingCapsule)
	CollisionBase GetCapsule() const;
	//�~������擾/�~����ȊO�𗘗p���Ă���ꍇ�A���삵�Ȃ��~�����Ԃ� return:���g�̉~����(BoundingCircle)
	CollisionBase GetCircle() const;
	//����������擾/��������ȊO�𗘗p���Ă���ꍇ�A���삵�Ȃ����������Ԃ� return:���g�̐�������(BoundingSegment)
	CollisionBase GetSegment() const;
	float getRadius() {
		return radius_;
	}
	float getWidth() {
		return 0;
	}
	float getHeight() {
		return 0;
	}
	float getSize() {
		return 0;
	}
	Vector2 GetColliderVelocity();
	//����𗘗p���邩�ǂ�����ύX����
	void enabled(bool change);
public:
	//���p���Ă��锻��̎��
	CollisionType type_;
	//�l�p����
	BoundingBox box_;
	//�J�v�Z������
	BoundingCapsule capsule_;
	//�~����
	BoundingCircle circle_;
	//��������
	BoundingSegment segment_;

	struct component
	{
		Vector2 point[4];
		float radius;
		component()
		{
			point[0] = 0;
			point[1] = 0;
			point[2] = 0;
			point[3] = 0;
			radius = 0;
		}
		component(Vector2 one, Vector2 two, Vector2 three, Vector2 four) {
			point[0] = one;
			point[1] = two;
			point[2] = three;
			point[3] = four;
			radius = 0;
		}

	};
	component component_;
	Vector2 movePoint[4];
	Vector2 position_;
	Vector2 previousPosition_;
	Vector2 testVect[4];
	Vector2 myvect[4];
	float radius_;

	bool enabled_;
};