#pragma once

#include "../../Base/IState.h"

#include "../../PlayerState_Enum.h"

#include "../../../PlayerPtr.h"
#include "../../../Player.h"
#include "../../../PlayerConnector.h"
#include "../../../PlayerBody.h"

// 各プレイヤーステートの基底クラス
class PlayerState_Union : public IState {
public:
	// コンストラクタ
	PlayerState_Union(const PlayerBodyPtr& butty, const PlayerBodyPtr& retty);
	// 全てのステートに共通する初期化処理
	virtual void common_init(Actor& actor, const StateElement& element) override;
	// 入力処理
	virtual void input(float deltaTime) override;
	// 入力処理
	virtual void common_update(float deltaTime) override;
	// 衝突処理
	virtual void collide(const Actor & other) override;
	// 描画処理
	virtual void draw()const override;
	// ステートが終了したか否か
	virtual bool isEnd() override;
	// 次のステートの要素
	virtual StateElement next() const override;
private:
	// ステートの変更処理
	virtual void change(const StateElement& element) override;
protected:
	// ステートの変更処理
	void change(const PlayerState_Enum_Union& id, const ActionType& type = ActionType::None);
protected:
	// キー系フラグ
	bool holdable_keyR();
	bool holdable_keyL();
	bool move_keyR();
	bool move_keyL();
	bool jump_key();
	// パッド系フラグ
	bool holdable_padR();
	bool holdable_padL();
	bool move_padR();
	bool move_padL();
	bool jump_pad();
	// スライムの弾性表現
	Vector2 speed_b(float deltaTime);
	Vector2 speed_r(float deltaTime);
	void chase(Vector2 &position, int pointIndex);
	Vector2 clamp(const Vector2 &position, int pointIndex);

	bool isOnFloor();

	// 重力
	Vector2 gravity(float deltaTime) const;
protected:
	// ステートの要素
	StateElement element_;
	// ステートの要素
	StateElement next_element_;
	// ステートが終了したか否か
	bool isEnd_;
	// タイマー
	float timer_;
	// ばね補正速度
	Vector2 velocity_;
	// プレイヤーポインタ
	PlayerConnector* cntr_;
	// プレイヤーポインタ
	PlayerBodyPtr butty_;
	// プレイヤーポインタ
	PlayerBodyPtr retty_;
};