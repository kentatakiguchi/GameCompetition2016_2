#ifndef THREE_JUMP_ATTACK_H_
#define THREE_JUMP_ATTACK_H_

#include "JumpAttack.h"

class ThreeJumpAttack : public JumpAttack {
public:
	ThreeJumpAttack();
	ThreeJumpAttack(const Vector2& position);
	// 攻撃
	void attack(float deltaTime) override;
	// 攻撃行動のリフレッシュを行います
	void Refresh() override;

private:
	int jumpCount_;			// ジャンプ回数
	int initJumpCount_;		// 初期のジャンプ回数
};

#endif
