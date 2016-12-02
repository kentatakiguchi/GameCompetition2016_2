#ifndef DYSON_ATTACK_H_
#define DYSON_ATTACK_H_

#include "BossAttack.h"

class IWorld;
class Tornado;

// 吸い込み攻撃
class DysonAttack : public BossAttack {
public:
	DysonAttack();
	DysonAttack(IWorld* world, const Vector2& position);
	// 攻撃
	void attack(float deltaTime) override;
	// 攻撃行動のリフレッシュを行います
	void Refresh() override;

private:
	IWorld* world_;			// ワールド

	Tornado* tornadoObj_;	// 竜巻オブジェクト
};

#endif
