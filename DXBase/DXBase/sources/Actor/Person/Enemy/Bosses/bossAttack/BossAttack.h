#ifndef BOSS_ATTACK_H_
#define BOSS_ATTACK_H_

#include "../../../../../Math/Math.h"
#include "../../../../../Define.h"
#include <string>

// ボス攻撃クラス(ベース)
class BossAttack {
public:
	BossAttack();
	BossAttack(const Vector2& position);
	// デストラクタ
	virtual ~BossAttack();
	// 更新
	void update(float deltaTime);
	// 攻撃
	virtual void attack(float deltaTime);
	// 移動した位置を取得します
	Vector2 getMovePosition();
	// 攻撃行動のリフレッシュを行います
	virtual void Refresh();
	// 攻撃が開始したかを返します
	bool isAttackStart();
	// 攻撃が終了したかを返します
	bool isAttackEnd();

public:
	// 位置を設定します
	void setPosition(const Vector2& position);
	// プレイヤーの位置を設定します
	void setPlayerPosition(const Vector2& position);
	// プレイヤーとの方向を設定します
	void setPlayerDirection(const Vector2& direction);
	// プレイヤーとの正規化された方向を設定します
	void setPlayerNormalizeDirection(const Vector2& direction);
	// 壁捜索オブジェクトが当たったかを設定します
	void setIsWallHit(bool isHit);
	//void setDirection(const Vector2& direction);
	// 壁移動の方向を取得します
	Vector2 getMoveDirection();
	// 床に触れているかを設定します
	void setIsGround(bool isGround);
	// 壁の下側に当たったかを設定します
	void setIsBottom(bool isBottom);
	// 触れている床の名前を設定します
	void setFloorName(const char* name);
	// 重力を使用するかを返します
	bool IsUseGravity();
	// プレイヤーの攻撃に当たるかを返します
	bool IsBodyHit();
	// プレイヤーに当たるかを返します
	bool IsAttackHit();

protected:
	float timer_;				// 時間
	std::string floorName_;		// 床の名前
	bool isAttackStart_;		// 攻撃を開始したか
	bool isAttackEnd_;			// 攻撃が終了したか
	bool isGround_;				// ボスが床に触れているのか
	bool isBottom_;				// 壁の下側に当たったか
	bool isUseGravity_;			// 重力を使うか
	bool isWspHit_;				// 壁捜索オブジェクトが当たったか
	bool isPrevWspHit_;			// 過去に壁捜索オブジェクトが当たったか
	bool isBodyHit_;			// プレイヤー本体に当たるか
	bool isAttackHit_;			// プレイヤーの攻撃に当たるか
	Vector2 position_;			// 位置
	Vector2 direction_;			// 方向
	Vector2 pPosition_;			// プレイヤーの位置
	Vector2 pDirection_;		// プレイヤーとの方向
	Vector2 pNormDirection_;	// プレイヤーとの方向
};

#endif
