#ifndef TEST_PLAYER_H_
#define TEST_PLAYER_H_

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../../Math/Vector3.h"
// プレーヤー
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
	Vector2 prePosition;						// 移動前の座標	
	Vector2 curPosition;						// 移動後の座標
	Vector2 mVelo;                              //プレイヤーの速度
	Vector2 mPositionVelo;                      //速度用の座標
};

#endif
