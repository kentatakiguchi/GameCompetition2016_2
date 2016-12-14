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
	PlayerState_Union();
	// 全てのステートに共通する初期化処理
	virtual void common_init(Actor& actor, const ActionType& type) override;
	// 入力処理
	virtual void input() override;
	// ステートが終了したか否か
	virtual bool isEnd() override;
	// 次のステートの要素
	virtual StateElement next() const override;
private:
	// ステートの変更処理
	virtual void change(const StateElement& element) override;
	// キー入力処理
	virtual void key_input();
	// パッド入力処理
	virtual void pad_input();
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
	//Player* player_;
	// プレイヤーポインタ
	PlayerConnector* cntr_;
	// プレイヤーポインタ
	PlayerBodyPtr butty_;
	// プレイヤーポインタ
	PlayerBodyPtr retty_;
};