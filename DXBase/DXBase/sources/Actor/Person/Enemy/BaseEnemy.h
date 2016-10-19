#ifndef BASE_ENEMY_H_
#define BASE_ENEMY_H_

#include "../../Base/Actor.h"
#include "../../../Animation/Animation2D.h"
#include "../../../World/IWorld.h"
#include "../../../Math/Math.h"
#include "EnemyManager.h"
#include <vector>

// モーション番号(仮)
enum {
	ENEMY_IDLE = 0,
	ENEMY_WALK = 1,
	ENEMY_DISCOVERY = 2,
	ENEMY_ATTACK = 3,
	ENEMY_DAMAGE = 4,
	ENEMY_DEAD = 5
};

// 状態列挙
enum class State {
	Idel,
	Search,
	Discovery,
	Chase,
	/*PlayerShortDistance,
	PlayerCenterDistance,
	PlayerLongDistance,*/
	Attack,
	Damage,
	Dead,
	Return
};

//// 死亡状態列挙(特定状態の死亡などに対応　現在使用しない)
//enum class DeadState {
//	KnockBackDead,
//	BlowAwayDead,
//	TornadoDead
//};

class BaseEnemy : public Actor {
public:
	BaseEnemy(IWorld* world, const Vector3&  position, const float bodyScale);
	~BaseEnemy();
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onCollide(Actor& actor) override;
	virtual void onMessage(EventMessage event, void*) override;

protected:
	// 待機状態です
	void idle();
	// 索敵移動です
	void search();
	// プレイヤーを発見した時の行動です
	void discovery();
	// プレイヤーの追跡行動です
	virtual void chase();
	//// プレイヤーとの距離が短いときの行動です
	//virtual void shortDistanceAttack();
	//// プレイヤーとの距離が中間の行動です
	//virtual void centerDistanceAttack();
	//// プレイヤーとの距離が長いときの行動です
	//virtual void longDistanceAttack();
	// 攻撃行動です
	virtual void Attack();
	// 被弾行動です
	void damageMove();
	// 死亡行動です
	void deadMove();
	// 状態の変更を行います
	void changeState(State state, unsigned int motion);
	//// 敵の死亡状態の変更を行います
	//void changeDeadState(EnemyDeadState state);
	// プレイヤーを捜索します
	void findPlayer();
	//// プレイヤーの追跡を中止する距離の加算です
	//void AddPlayerChaseStopDistance(float distance);

protected:
	// 索敵時の行動です
	virtual void searchMove();
	// 追跡時の行動です
	virtual void chaseMove();

public:
	// 敵が飲み込まれた時のスケールポイントを返します
	float getSP();
	// 敵の大きさを返します
	int getScale();

private:
	// 状態の更新を行います
	void updateState(float deltaTime);

protected:
	// メンバ変数
	int hp_;						// 体力
	int ap_;						// アタックポイント
	float speed_;					// 移動速度
	float initSpeed_;				// 初期の移動速度
	float discoveryLenght_;			// プレイヤーに気づく距離

	unsigned int color_;			// 球体の色
	float stateTimer_;				// 状態タイマ
	std::string stateString_;		// 状態の文字列（デバッグ用）
	State state_;					// 状態
	Vector2 target_;				// ターゲットの位置
	Vector3 discoveryPosition_;		// 発見したときの位置

	Animation2D animation_;			// アニメーション
	ActorPtr player_;				// プレイヤー

	EnemyManager enemyManager_;
};

#endif