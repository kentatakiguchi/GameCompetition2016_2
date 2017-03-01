#pragma once
#include "../../../Base/Actor.h"
#include "../../../../Animation/Enemy/EnemyAnimation2D.h"
#include "../../../../Actor/Base/ActorPtr.h"
#include <vector>

class MiniBossRepair : public Actor {
public:
	MiniBossRepair(IWorld * world, const Vector2& position,int num);
	~MiniBossRepair();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	//�������ǂ���
	void Repair(bool flag);
private:
	Animation2D mAnim;
	std::vector<Vector2>mPoss;
	//�ŏ��̏ꏊ
	Vector2 mFirstPos;
	//�u���b�N��u���ꏊ
	Vector2 mBlockToPos;
	//�u���b�N�̍��W
	Vector2 mBlockPos;
	//�A��ꏊ
	Vector2 mEndPos;
	//�⊮�֌W
	float mLerpCount;
	//�������ǂ���
	bool repairFlag;
	//�q���̌���
	bool mChildDirection;
	//�T�C�Y
	Vector2 mAnimSize;
	int mNum;
	bool mTes;
};