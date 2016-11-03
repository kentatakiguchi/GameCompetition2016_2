#pragma once

#include "Base/IState.h"
#include "../PlayerBody.h"
#include "../Player.h"

// 各プレイヤーステートの基底クラス
class PlayerState : public IState {
public:
	// コンストラクタ
	PlayerState();
	// 全てのステートに共通する初期化処理
	virtual void common_init(Actor & actor, ActionType type) override;
	// ステートの変更処理
	virtual void change(StateElement element) override;
	// ステートが終了したか否か
	virtual bool isEnd() override;
	// 次のステートの要素
	virtual StateElement next() const override;
protected:
	// プレイヤーの左右比較(右側を返す)
	PlayerBodyPtr compareMax(PlayerBodyPtr p1, PlayerBodyPtr p2);
	// プレイヤーの左右比較(左側を返す)
	PlayerBodyPtr compareMin(PlayerBodyPtr p1, PlayerBodyPtr p2);
protected:
	// ステートの要素
	StateElement element_;
	// ステートが終了したか否か
	bool isEnd_;
	// プレイヤーポインタ
	Player* player_;
	// mainとなる部位
	PlayerBodyPtr main_body_;
	// sub となる部位
	PlayerBodyPtr sub_body_;
	// タイマー
	float timer_;
};