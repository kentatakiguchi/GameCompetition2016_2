#ifndef PLURAL_WALL_ATTACK_H_
#define PLURAL_WALL_ATTACK_H_

#include "WallAttack.h"

class PluralWallAttack : public WallAttack {
public:
	PluralWallAttack();
	PluralWallAttack(const Vector2& position);
	// UŒ‚
	void attack(float deltaTime) override;
	// UŒ‚s“®‚ÌƒŠƒtƒŒƒbƒVƒ…‚ğs‚¢‚Ü‚·
	void Refresh() override;

private:
	int aCount_;			// UŒ‚‰ñ”
	int initACount_;		// ‰Šú‚ÌUŒ‚‰ñ”
	float idelTimer_;
	//int flinck
};

#endif