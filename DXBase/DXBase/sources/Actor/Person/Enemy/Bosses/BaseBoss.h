#ifndef BASE_BOSS_H_
#define BASE_BOSS_H_

#include "../../../Base/Actor.h"
#include "../../../../World/IWorld.h"
#include "../../../../Math/Math.h"
#include "../../../../Define.h"
#include "../../../../Animation/Enemy/EnemyAnimation2D.h"
#include "BossAnimationNumber.h"
#include "BossManager.h"

class FloorSearchPoint;
class BossEntry;
class BossHeart;
class BossGaugeUI;

// ボスクラス
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
		BattleIdel,
		Idel,
		Attack,
		Damage,
		Flinch,
		Piyori,
		Boko,
		Dead
	};
	// 攻撃状態の列挙
	enum class AttackState {
		JumpAttack,
		WallAttack,
		SpeacialAttack
	};

public:
	BaseBoss(
		IWorld* world,
		const Vector2&  position,
		const float bodyScale = 128.0f);// * 2 / 2.0f);
	~BaseBoss();
	virtual void onUpdate(float deltaTime) override;
	virtual void onEnd();
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

public:
	// シーンを終了させるかを返します
	bool isSceneEnd();
	// 目的地に移動します
	void movePosition(float deltaTime);
	// 目的の位置を設定します
	void setMovePosition(const Vector2& position, const float speed);
	// 目的の位置に到達したかを返します (目的の位置, 速度)
	bool isMovePosition();
	// 戦闘を開始するかを返します
	void setIsBattle(bool isBattle);

protected:
	// 状態の更新
	void updateState(float deltaTime);
	// 状態の変更を行います
	void changeState(State state, int num);
	// 攻撃状態の変更を行います
	void changeAttackState(AttackState aState, int num);
	// 戦闘待機状態
	void battleIdel(float deltaTime);
	// 待機状態
	virtual void idel(float deltaTime);
	// 攻撃行動
	void attack(float deltaTime);
	// ダメージ状態
	void damage(float deltaTime);
	// 怯み状態
	void flinch(float deltaTime);
	// ぴより状態 // ぴよりー＞ロック解除
	void piyori(float deltaTime);
	// ぼこり状態
	void boko(float deltaTime);
	// 死亡状態
	void deadMove(float deltaTime);
	// ぴより行動
	void piyoriMove(float deltaTime);

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
	// 指定した値のダメージ量を加算します
	void damage(
		const int damage,
		const Vector2& position, 
		const float scale = 1.0f);
	//地面の位置に補正します
	void groundClamp(Actor& actor);
	// アニメーションの追加
	void addAnimation();
	// ぴより状態の設定を行います
	void setPiyori();

protected:
	int dp_;						// 耐久値
	int hp_;						// 体力
	unsigned int attackCount_;		// 攻撃行動するカウント
	int flinchCount_;				// ひるむまでの回数
	int piyoriCount_;				// ぴよる回数
	int bokoCreateCount_;			// ボコエフェクト生成回数
	float stateTimer_;				// 状態の時間
	float timer_;					// 現在の時間(最大値 1)
	float deltaTimer_;				// 現在の時間(補間)
	float damageTimer_;				// 次に被弾までの時間
	float angle_;					// 角度(時計周り)
	float effectCreateTimer_;		// エフェクト生成時間(間隔)
	bool isGround_;					// 接地しているか
	bool isBottomHit_;				// 壁の下側に当たったか
	//bool isHit_;					// プレイヤー本体に当たるか
	bool isAttackHit_;				// プレイヤーの攻撃に当たるか
	bool isSceneEnd_;				// シーンを終了させるか
	bool isBattle_;					// 戦闘を行うか
	bool isEffectCreate_;			// エフェクトを生成するか
	int handle_;					// デバッグハンドル
	FloorSearchPoint* wspObj_;		// 壁捜索オブジェクト
	BossEntry* entryObj_;			// ボス入口オブジェクト
	BossManager bossManager_;		// ボスマネージャー
	// 攻撃状態のコンテナ
	typedef std::vector<AttackState> AttackStateContainer;
	AttackStateContainer asContainer_;
	// 攻撃モーションコンテナ
	typedef std::vector<int> BossAnimationContainer;
	BossAnimationContainer asAnimations_;

private:
	Vector2 playerPastPosition_;	// プレイヤーの過去の位置
	Vector2 direction_;				// 方向
	ActorPtr player_;
	State state_;					// 状態
	AttackState attackState_;		// 攻撃状態
	int animeNum_;
	EnemyAnimation2D animation_;	// アニメーション
	BossGaugeUI* bossGaugeUI_;		// ボスの体力

	float top_, bottom_, right_, left_;	// 判定用

	Vector2 movePos_;
	float moveSpeed_;
	// クランプ用の位置(仮)
	const Vector2 FIELD_SIZE = Vector2(
		SCREEN_SIZE.x - CHIPSIZE - body_.GetCircle().getRadius(), 
		SCREEN_SIZE.y - CHIPSIZE - body_.GetCircle().getRadius());
	// 体力のロックコンテナ
	typedef std::vector<int> LockHpContainer;
	LockHpContainer lockHps_;
	// スターエフェクト用コンテナ
	typedef std::list<ActorPtr> StarContainer;
	StarContainer stars_;
};

#endif
