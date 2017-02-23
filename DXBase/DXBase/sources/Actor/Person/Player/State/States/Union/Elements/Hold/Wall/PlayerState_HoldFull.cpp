#include "PlayerState_HoldFull.h"

// コンストラクタ
PlayerState_HoldFull::PlayerState_HoldFull(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : 
	PlayerState_HoldBase(butty, retty),
	PlayerState_HoldBase_Wall(butty, retty),
	PlayerState_HoldBase_Full(butty, retty) {}

// キー入力処理
void PlayerState_HoldFull::onKeyInput(float deltaTime){
	PlayerState_HoldBase_Full::onKeyInput(deltaTime);
	PlayerState_HoldBase_Wall::onKeyInput(deltaTime);
}

// パッド入力処理
void PlayerState_HoldFull::onPadInput(float deltaTime){
	PlayerState_HoldBase_Full::onPadInput(deltaTime);
	PlayerState_HoldBase_Wall::onPadInput(deltaTime);
}


