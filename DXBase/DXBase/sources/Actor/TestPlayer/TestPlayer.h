#ifndef TEST_PLAYER_H_
#define TEST_PLAYER_H_

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../../Math/Vector3.h"
// �v���[���[
class TestPlayer : public Actor {
public:
	TestPlayer(IWorld* world, const Vector3& position);
	~TestPlayer();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& other) override;

public:
	Vector2 GetVelo()
	{
		return mVelo;
	}
	Vector2 GetSpringVelo()
	{
		return veloPlus;
	}
private:
	Vector2 prePosition;						// �ړ��O�̍��W	
	Vector2 curPosition;						// �ړ���̍��W
	Vector2 mVelo;                              //�v���C���[�̑��x
	Vector2 mPositionVelo;                      //���x�p�̍��W
};

#endif
