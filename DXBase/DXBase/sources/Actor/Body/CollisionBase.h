#pragma once

#include"BoundingBox.h"
#include"BoundingCapsule.h"
enum CollisionType
{
	BoxCol,
	CapsuleCol,
	NoneCol
};
class CollisionBase
{

public:
	//����𗘗p���Ȃ��ꍇ
	CollisionBase();
	//�l�p����𗘗p����ꍇ
	CollisionBase(const Vector2& topLeft, const Vector2& topRight, const Vector2& bottomLeft, const Vector2& bottomRight);
	//�J�v�Z������𗘗p����ꍇ
	CollisionBase(Vector2& startPoint, Vector2& endPoint, float capsuleRadius);
	//�f�o�b�O�p�̔���\��
	void draw() const;
	//�l�p����̑傫���A�`��̕ύX
	void transform(Vector2& topLeft, Vector2& topRight, Vector2& bottomLeft, Vector2& bottomRight);
	//�J�v�Z������̑傫���A�`��̕ύX
	void transoform(Vector2& startPoint, Vector2& endPoint, float capsuleRadius);
	//����̈ړ�
	void translate(Vector2 position);
	//�ΏۂƓ������Ă��邩  other:���肵��������(CollisionBase) return:���茋��(bool)
	bool intersects(CollisionBase& other);
	//�ǂ̎�ނ̓����蔻��𗘗p���Ă��邩���擾 return:����̎��(CollisionType)
	CollisionType GetType() const;
	//�l�p������擾/�l�p����ȊO�𗘗p���Ă���ꍇ�A���삵�Ȃ��l�p�����Ԃ� return:���g�̎l�p����(BoundingBox)
	BoundingBox GetBox() const;
	//�J�v�Z��������擾/�J�v�Z������ȊO�𗘗p���Ă���ꍇ�A���삵�Ȃ��J�v�Z�������Ԃ� return:���g�̃J�v�Z������(BoundingBox)
	BoundingCapsule GetCapsule() const;
	//����𗘗p���邩�ǂ�����ύX����
	void enabled(bool change);
private:
	//���p���Ă��锻��̎��
	CollisionType type_;
	//�l�p����
	BoundingBox box_;
	//�J�v�Z������
	BoundingCapsule capsule_;
};