#include "PlayerState_HoldSwim.h"

// コンストラクタ
PlayerState_HoldSwim::PlayerState_HoldSwim(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) :
	PlayerState_HoldBase(butty, retty),
	PlayerState_HoldBase_Wall(butty, retty),
	PlayerState_HoldBase_Swim(butty, retty) {}

// キー入力処理
void PlayerState_HoldSwim::onKeyInput(float deltaTime){
	PlayerState_HoldBase_Swim::onKeyInput(deltaTime);
	PlayerState_HoldBase_Wall::onKeyInput(deltaTime);
}

// パッド入力処理
void PlayerState_HoldSwim::onPadInput(float deltaTime){
	PlayerState_HoldBase_Swim::onPadInput(deltaTime);
	PlayerState_HoldBase_Wall::onPadInput(deltaTime);
}


