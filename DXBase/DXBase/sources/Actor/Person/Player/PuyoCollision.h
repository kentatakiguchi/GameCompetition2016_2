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
	void SetPos(Vector2 pos,Vector2 center) {
		position_ = pos*Matrix::Invert(inv_);
		mCenter = center;
	}
	//�ǂ�2�����z��ɂ��邩�擾
	Vector2 GetArrayState() {
		return mArrayState;
	}
	Vector2 GetVec() {
		return mVec;
	}
private:
	//���Ɛ��̂����蔻��ƌ�_�����߂�
	bool SegmentCol(Vector2 A, Vector2 B, Vector2 C, Vector2 D,Vector2 & couten,bool rightLeft);
private:
	//�{���̈ʒu�ƌ�_�̃x�N�g��
	Vector2 mVec;
	//�ŏI�I�Ȍ�_
	Vector2 mIntersection;
	//2�����z��̂ǂ���
	Vector2 mArrayState;
	//�Ղ�e�N�X�`���̒��S
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


	bool top;
	bool right;
	bool bot;
	bool left;
};

