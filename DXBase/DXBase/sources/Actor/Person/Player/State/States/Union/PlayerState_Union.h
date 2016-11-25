#pragma once

#include "../../Base/IState.h"
#include "../../../PlayerBody.h"
#include "../../../Player.h"
#include "../../PlayerState_Enum.h"

#include "../../../PlayerStruct.h"

// 各プレイヤーステートの基底クラス
class PlayerState_Union : public IState {
public:
	// コンストラクタ
	PlayerState_Union();
	// 全てのステートに共通する初期化処理
	virtual void common_init(Actor& actor, ActionType type) override;
	// ステートの変更処理
	virtual void change(StateElement element) override;
	// ステートが終了したか否か
	virtual bool isEnd() override;
	// 次のステートの要素
	virtual StateElement next() const override;
protected:
	bool holdable_keyR();
	bool holdable_keyL();
	bool holdable_padR();
	bool holdable_padL();
protected:
	// ステートの要素
	StateElement element_;
	// ステートが終了したか否か
	bool isEnd_;
	// プレイヤーポインタ
	Player* player_;
	// プレイヤーポインタ
	PlayerBodyPtr butty_;
	// プレイヤーポインタ
	PlayerBodyPtr retty_;
	// プレイヤーポインタ
	PlayerCntrPtr cntr_;
	// タイマー
	float timer_;
};