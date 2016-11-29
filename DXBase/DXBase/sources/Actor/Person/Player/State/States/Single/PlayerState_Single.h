#pragma once

#include "../../Base/IState.h"

#include "../../PlayerState_Enum.h"

#include "../../../PlayerPtr.h"
#include "../../../Player.h"
#include "../../../PlayerBody.h"

// 各プレイヤーステートの基底クラス
class PlayerState_Single : public IState {
public:
	// コンストラクタ
	PlayerState_Single();
	// 全てのステートに共通する初期化処理
	virtual void common_init(Actor& actor, ActionType type) override;
	// 入力処理
	virtual void input() override;
	// ステートの変更処理
	virtual void change(StateElement element) override;
	// ステートが終了したか否か
	virtual bool isEnd() override;
	// 次のステートの要素
	virtual StateElement next() const override;
private:
	// キー入力処理
	virtual void key_input();
	// パッド入力処理
	virtual void pad_input();
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
	PlayerBody* player_body_;
};