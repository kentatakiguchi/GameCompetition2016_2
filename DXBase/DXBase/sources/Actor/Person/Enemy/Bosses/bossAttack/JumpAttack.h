#ifndef JUMP_ATTACK_H_
#define JUMP_ATTACK_H_

#include "BossAttack.h"

// ジャンプ攻撃クラス
class JumpAttack : public BossAttack {
public:
	JumpAttack();
	JumpAttack(IWorld* world, const Vector2& position);
	// 攻撃
	virtual void attack(float deltaTime) override;
	// ジャンプ攻撃
	void jump(float deltaTime);
	//// 移動した位置を取得します
	//Vector2 getMovePosition() override;
	// 攻撃行動のリフレッシュを行います
	virtual void Refresh() override;

protected:
	float speed_;			// 速度
	float degrees_;			// 角度
	float jumpPower_;		// ジャンプ力
	float initJumpPower_;	// ジャンプ力(初期化)
	float recastTimer_;		// 再行動するまでの時間
	float initRecastTimer_;	// 再行動するまでの時間(初期値)
	bool isJump_;			// ジャンプをしたか
	bool isFirstJump_;		// 最初のジャンプか
	bool isJumpEnd_;		// ジャンプ攻撃が終了したか
	bool isIdel_;			// ジャンプ後の待機状態か

private:
	Vector2 prevPlayerDistance_;
};

#endif
