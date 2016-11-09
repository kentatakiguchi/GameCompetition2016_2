#ifndef BASE_BOSS_H_
#define BASE_BOSS_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Animation2D.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"
#include "../../../../Define.h"

// モーション番号(仮)
enum {
	ENEMY_IDLE = 0,
	ENEMY_WALK = 1,
	ENEMY_DISCOVERY = 2,
	ENEMY_LOST = 3,
	ENEMY_ATTACK = 4,
	ENEMY_DAMAGE = 5,
	ENEMY_DEAD = 6,
};

// 状態列挙
enum class State {
	Idel,
	//Search,
	attack,
	Damage,
	Dead
};

class BaseBoss : public Actor {
public:
	BaseBoss(IWorld* world, const Vector2&  position, const float bodyScale);
	~BaseBoss();
	void Initialize();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

protected:
	int damageResult_;		// ひるむまでのダメージ数
	int initDamageResult_;	// ひるむまでのダメージ数(初期値)
	int hp_;				// 体力
};

#endif
