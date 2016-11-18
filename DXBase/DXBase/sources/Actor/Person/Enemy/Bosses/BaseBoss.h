#ifndef BASE_BOSS_H_
#define BASE_BOSS_H_

#include "../../../Base/Actor.h"
#include "../../../../Animation/Animation2D.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"
#include "../../../../Define.h"

#include "BossManager.h"

// class BossManager;
class FloorSearchPoint;
class BossEntry;
class BossHeart;
class BossGaugeUI;

class BaseBoss : public Actor {
protected:
	// モーション番号
	enum {
		BOSS_IDLE = 0,
		BOSS_ATTACK = 1,
		BOSS_FLINCH = 2,
		BOSS_DEAD = 3,
	};
	// 攻撃行動の番号
	enum {
		ATTACK_JUMPATTACK_NUMBER = 0,
		ATTACK_WALLATTACK_NUMBER = 1,
		ATTACK_SPECIALATTACK_NUMBER = 2
	};
	// 状態列挙
	enum class State {
		Idel,
		//Search,
		Attack,
		Flinch,
		Dead
	};
	// 攻撃状態の列挙
	enum class AttackState {
		JumpAttack,
		WallAttack,
		SpeacialAttack
	};

public:
	BaseBoss(IWorld* world, const Vector2&  position, const float bodyScale);
	~BaseBoss();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

public:
	// シーンを終了させるかを返します
	bool isSceneEnd();

protected:
	// 状態の更新
	void updateState(float deltaTime);
	// 状態の変更を行います
	void changeState(State state, unsigned int motion);
	// 攻撃状態の変更を行います
	void changeAttackState(AttackState aState, unsigned int motion);
	// 待機状態
	void idel(float deltaTime);
	// 攻撃行動
	void attack(float deltaTime);
	// ひるみ状態
	void flinch(float deltaTime);
	// 死亡状態
	void deadMove(float deltaTime);

// 攻撃行動
protected:
	// ジャンプ攻撃
	void jumpAttack(float deltaTime);
	// 壁攻撃
	void wallAttack(float deltaTime);
	// スペシャルアタック
	void specialAttack(float deltaTime);

private:
	// デルタタイム(最大値1)の設定
	void setTimer(float deltaTime);
	// ボスマネージャーのステータスの設定
	void setBMStatus();
	//地面の位置に補正します
	void groundClamp(Actor& actor);

protected:
	int dp_;					// ひるむまでの耐久値
	int initDp_;				// ひるむまでの耐久値(初期値)
	int hp_;					// 体力
	int flinchCount_;			// ひるむまでの回数
	// int initHp_;				// 体力(初期値)
	float stateTimer_;			// 状態の時間
	float timer_;				// 現在の時間(最大値 1)
	float deltaTimer_;			// 現在の時間(補間)

	bool isGround_;				// 接地しているか
	bool isSceneEnd_;			// シーンを終了させるか

	std::string stateString_;	// 状態の文字列（デバッグ用）

	FloorSearchPoint* fspObj_;	// 床捜索オブジェクト
	BossEntry* entryObj_;		// ボス入口オブジェクト
	BossHeart* heartObj_;		// ボス心臓オブジェクト
	BossManager bossManager_;	// ボスマネージャー
	// 攻撃状態のコンテナ
	typedef std::vector<AttackState> AttackStateContainer;
	AttackStateContainer asContainer_;

private:
	Vector2 playerPastPosition_;
	ActorPtr player_;

	State state_;				// 状態
	AttackState attackState_;	// 攻撃状態

	BossGaugeUI* bossGaugeUI_;	// ボスの体力

	// クランプ用の位置(仮)
	const Vector2 FIELD_SIZE = Vector2(
		SCREEN_SIZE.x - CHIPSIZE - body_.GetCircle().getRadius(), 
		SCREEN_SIZE.y - CHIPSIZE - body_.GetCircle().getRadius());
};

#endif
