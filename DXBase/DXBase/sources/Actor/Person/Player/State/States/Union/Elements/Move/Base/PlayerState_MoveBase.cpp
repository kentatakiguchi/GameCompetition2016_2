#include "PlayerState_MoveBase.h"

#include "../../../../../../../../../Define.h"
#include "../../../../../../../../../Input/InputMgr.h"

// コンストラクタ
PlayerState_MoveBase::PlayerState_MoveBase(const PlayerBodyPtr & butty, const PlayerBodyPtr & retty) : PlayerState_Union(butty, retty) {}

// 状態固有の初期化
void PlayerState_MoveBase::unique_init(){
	// buttyのアニメーションをMOVEに変更
	butty_->animation().change(PlayerAnimID::MOVE, 2.0f);
	// rettyのアニメーションをMOVEに変更
	retty_->animation().change(PlayerAnimID::MOVE, 2.0f);

	onInit();
}

void PlayerState_MoveBase::update(float deltaTime){
	// 移動処理
	move(deltaTime);

	// ボスステージ専用イベント時にEvent状態に変更
	if (cntr_->getWorld()->isEntered()) change(PlayerState_Enum_Union::EVENT);

	onUpdate(deltaTime);
}

void PlayerState_MoveBase::end(){
	onEnd();
}

void PlayerState_MoveBase::key_input(float deltaTime){
	onKeyInput(deltaTime);
}

void PlayerState_MoveBase::pad_input(float deltaTime){
	onPadInput(deltaTime);
}

void PlayerState_MoveBase::move(float deltaTime)
{
}

void PlayerState_MoveBase::flip_animation()
{
}
