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
//protected:
	//// プレイヤーの左右比較(右側を返す)
	//PlayerBodyPtr compareMax_H(PlayerBodyPtr p1, PlayerBodyPtr p2);
	//// プレイヤーの左右比較(左側を返す)
	//PlayerBodyPtr compareMin_H(PlayerBodyPtr p1, PlayerBodyPtr p2);
	//// プレイヤーの上下比較(上側を返す)
	//PlayerBodyPtr compareMin_V(PlayerBodyPtr p1, PlayerBodyPtr p2);
	//// 同じ座標
	//bool compare_pos(PlayerBodyPtr p1, PlayerBodyPtr p2);
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