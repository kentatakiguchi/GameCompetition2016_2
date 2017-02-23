#pragma once

#include "../../Base/Actor.h"
#include "../../../World/IWorld.h"
#include <vector>
//�Ղ�e�N�X�`���̂����蔻�肪����Ƃ���
class PuyoCollision : public Actor {
public:
	PuyoCollision(IWorld* world, Vector2& position,Vector2 arrayState,Vector2 &center);
	~PuyoCollision();
	virtual void onUpdate(float deltaTime) override;
	virtual void onLateUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
public:
	//�t�s�񂩂��Ă��Ȃ��|�W�V������
	void SetPos(const Vector2& pos,const Vector2& center1,const Vector2& center2) {
		position_ = pos*Matrix::Invert(inv_);
		mCenter1 = center1*Matrix::Invert(inv_);
		mCenter2 = center2*Matrix::Invert(inv_);
	}
	//�ǂ�2�����z��ɂ��邩�擾
	Vector2 GetArrayState() {
		return mArrayState;
	}
	//�|�W�V�����Z�b�g
	void VecZero() {
		mVec = Vector2::Zero;
	}
	Vector2 GetVec() {
		return mVec;
	}
private:
	//���Ɛ��̂����蔻��ƌ�_�����߂�
	bool SegmentCol(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D,Vector2 & couten,bool rightLeft);
private:
	//�{���̈ʒu�ƌ�_�̃x�N�g��
	Vector2 mVec;
	//�ŏI�I�Ȍ�_
	Vector2 mIntersection;
	//2�����z��̂ǂ���
	Vector2 mArrayState;
	//�Ԃ��Ă��Ƃ���Ă�
	Vector2 mCenter1;
	Vector2 mCenter2;
	//�Z���^�[
	Vector2 mCenter;
	//�o�l��Ԋ֌W
	Vector2 mResIntersection;
	Vector2 mVelo;
	//�X�e�[�W�Ɠ������Ă��邩
	bool mIsCol;
	//��_����
	Vector2 mIntersections[4];
	//�ŏI�I�Ȍ�_����
	std::vector<Vector2> mIntersectionsVector;
	//�v���C���[�̍��W
	Vector2 mPlayerPos1;
	Vector2 mPlayerPos2;
	//�o�������u�Ԃ͂����蔻�薳��
	float mNoColTimer;
	bool top;
	bool right;
	bool bot;
	bool left;


	bool testFlag;
};

