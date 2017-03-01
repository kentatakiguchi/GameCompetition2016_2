#pragma once
#include "../Base/Actor.h"
#include "../../World/IWorld.h"
// �v���[���[
class BlockParticle : public Actor {
public:
	BlockParticle(IWorld* world, const Vector2& position);
	~BlockParticle();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;
public:
	//�󂷂��ǂ���
	void Break(bool flag);
	//�����ꂽ���ǂ���
	void RepairBlock(bool flag);
	Vector2 GetFirstPosition();
private:
	//�����ʒu
	Vector2 mPosition;
	Vector2 mVelo;
	bool mBreakFlag;
	bool mRepairFlag;
	float mAngle;
	float mAngleVelo;
	//�`�ʂ̍��W
	Vector2 mDrawPos;
};