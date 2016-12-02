#ifndef DYSON_ATTACK_H_
#define DYSON_ATTACK_H_

#include "BossAttack.h"

// ‹z‚¢‚İUŒ‚
class DysonAttack : public BossAttack {
public:
	DysonAttack();
	DysonAttack(const Vector2& position);
	// UŒ‚
	void attack(float deltaTime) override;
	// UŒ‚s“®‚ÌƒŠƒtƒŒƒbƒVƒ…‚ğs‚¢‚Ü‚·
	void Refresh() override;
};

#endif
