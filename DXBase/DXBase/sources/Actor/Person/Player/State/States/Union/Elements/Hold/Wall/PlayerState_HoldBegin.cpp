#include "PlayerState_HoldBegin.h"

// コンストラクタ
PlayerState_HoldBegin::PlayerState_HoldBegin(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) :
	PlayerState_HoldBase(butty, retty),
	PlayerState_HoldBase_Wall(butty, retty),
	PlayerState_HoldBase_Begin(butty, retty) {}

// キー入力処理
void PlayerState_HoldBegin::onKeyInput(float deltaTime){
	PlayerState_HoldBase_Begin::onKeyInput(deltaTime);
	PlayerState_HoldBase_Wall::onKeyInput(deltaTime);
}

// パッド入力処理
void PlayerState_HoldBegin::onPadInput(float deltaTime){
	PlayerState_HoldBase_Begin::onPadInput(deltaTime);
	PlayerState_HoldBase_Wall::onPadInput(deltaTime);
}

