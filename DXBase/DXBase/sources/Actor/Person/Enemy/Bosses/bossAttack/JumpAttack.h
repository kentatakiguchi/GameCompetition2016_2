#ifndef JUMP_ATTACK_H_
#define JUMP_ATTACK_H_

#include "BossAttack.h"

class JumpAttack : public BossAttack {
public:
	JumpAttack();
	JumpAttack(const Vector2& position);	
	// 攻撃
	virtual void attack(float deltaTime) override;
	// ジャンプ
	void jump(float deltaTime);
	// 移動した位置を取得します
	Vector2 getMovePosition() override;
	// 攻撃行動のリフレッシュを行います
	virtual void Refresh() override;

protected:
	float speed_;			// 速度
	float degrees_;			// 角度
	float jumpPower_;		// ジャンプ力
	float recastTimer_;		// 再行動するまでの時間
	float initRecastTimer_;	// 再行動するまでの時間(初期値)
	bool isJumpEnd_;		// ジャンプが終了したか
};

#endif
