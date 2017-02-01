#pragma once

#include "../../Base/IState.h"

#include "../../PlayerState_Enum.h"

#include "../../../PlayerPtr.h"
#include "../../../Player.h"
#include "../../../PlayerBody.h"

// 各プレイヤーステートの基底クラス
class PlayerState_Single : public IState {
public:
	struct Keys {
	public:
		KeyCode up;
		KeyCode down;
		KeyCode right;
		KeyCode left;
	public:
		Keys(const KeyCode& up = KeyCode::UP, const KeyCode& down = KeyCode::DOWN, const KeyCode& right = KeyCode::RIGHT, const KeyCode& left = KeyCode::LEFT) :up(up), down(down), right(right), left(left) {}
	};
public:
	// コンストラクタ
	PlayerState_Single(const Keys& keys);
	// 全てのステートに共通する初期化処理
	virtual void common_init(Actor& actor, const ActionType& type) override;
	// 入力処理
	virtual void input(float deltaTime) override;
	// 入力処理
	virtual void common_update(float deltaTime) override;
	// 衝突処理
	virtual void collide(const Actor & other) override;
	// 描画処理
	virtual void draw()const override;
	// ステートの変更処理
	virtual void change(const StateElement& element) override;
	// ステートが終了したか否か
	virtual bool isEnd() override;
	// 次のステートの要素
	virtual StateElement next() const override;
protected:
	bool is_butty();
	bool is_retty();
private:
	// キー入力処理
	virtual void key_input(float deltaTime);
	// パッド入力処理
	virtual void pad_input(float deltaTime);
protected:
	// ステートの要素
	StateElement element_;
	// ステートの要素
	StateElement next_element_;
	// ステートが終了したか否か
	bool isEnd_;
	// タイマー
	float timer_;
	// プレイヤーポインタ
	PlayerBody* body_;
	// キー
	Keys keys_;
};