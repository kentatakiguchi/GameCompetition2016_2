#pragma once

#include "../../Base/IState.h"
#include "../../../PlayerBody.h"
#include "../../../Player.h"
#include "../../PlayerState_Enum.h"

#include "../../../PlayerStruct.h"

// 各プレイヤーステートの基底クラス
class PlayerState_Single : public IState {
public:
	// コンストラクタ
	PlayerState_Single(const PlayerBodyPtr& player_body);
	// 全てのステートに共通する初期化処理
	virtual void common_init(ActionType type) override;
	// ステートの変更処理
	virtual void change(StateElement element) override;
	// ステートが終了したか否か
	virtual bool isEnd() override;
	// 次のステートの要素
	virtual StateElement next() const override;
protected:
	// ステートの要素
	StateElement element_;
	// ステートが終了したか否か
	bool isEnd_;
	// プレイヤーポインタ
	PlayerBodyPtr player_body_;
	// タイマー
	float timer_;
}; 