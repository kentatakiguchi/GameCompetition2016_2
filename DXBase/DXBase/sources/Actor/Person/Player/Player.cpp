#include "Player.h"

#include"../../Body/CollisionBase.h"
#include "../../../ResourceLoader/ResourceLoader.h"

#include "State/Base/State_Dammy.h"
#include "State/States/Union/Elements/PlayerState_StandBy.h"
#include "State/States/Union/Elements/PlayerState_Idle.h"
#include "State/States/Union/Elements/PlayerState_Move.h"
#include "State/States/Union/Elements/PlayerState_Hold.h"
#include "State/States/Union/Elements/PlayerState_HoldBoth.h"
#include "State/States/Union/Elements/PlayerState_Attack.h"
#include "State/States/Union/Elements/PlayerState_Damage.h"
#include "State/States/Union/Elements/PlayerState_Split.h"


#include <memory>
#include <algorithm>

Player::Player(IWorld * world, const Vector2 & position) :
	Actor(world, "Player", position, CollisionBase(Vector2(0, 0), Vector2(0, 0), 8.0f)){
	// ÉÇÉfÉãÇÃì«Ç›çûÇ›
	//modelHandle_ = MV1DuplicateModel(ResourceLoader::GetInstance().getModelID(ModelID::PLAYER));
	//animation_ = Animation(modelHandle_);
	
	auto body1 = std::make_shared<PlayerBody>(world_, "PlayerBody1", position_ + Vector2(PLAYER_MAX_NORMAL_LENGTH / 2, 0));
	auto body2 = std::make_shared<PlayerBody>(world_, "PlayerBody2", position_ - Vector2(PLAYER_MAX_NORMAL_LENGTH / 2, 0));

	addChild(body1);
	addChild(body2);


	stateMgr_.add((unsigned int)PlayerState_Enum_Union::STAND_BY, std::make_shared<PlayerState_StandBy>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::IDLE, std::make_shared<PlayerState_Idle>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::MOVE, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::HOLD, std::make_shared<PlayerState_Hold>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::HOLD_BOTH, std::make_shared<PlayerState_HoldBoth>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::QUICK, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::ATTACK, std::make_shared<PlayerState_Attack>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::DAMAGE, std::make_shared<PlayerState_Damage>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::SPLIT, std::make_shared<PlayerState_Split>());
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Union::STAND_BY));

	connect(body1, body2);

}

Player::~Player(){}

void Player::onUpdate(float deltaTime) {

	stateMgr_.action(*this, deltaTime);

	//position_ = (main_->getPosition() + sub_->getPosition()) / 2;
	//body_.RotateCapsule(main_->getPosition() - position_, sub_->getPosition() - position_, body_.GetCapsule().component_.radius);

	if (main_->hitOpponent() == PlayerBody::Opponent::ENEMY ||
		sub_->hitOpponent() == PlayerBody::Opponent::ENEMY ||
		InputMgr::GetInstance().IsKeyDown(KeyCode::P)) {
		split_body();
	}

	if (main_->hitOpponent() == PlayerBody::Opponent::PARTNER ||
		sub_->hitOpponent() == PlayerBody::Opponent::PARTNER || 
		InputMgr::GetInstance().IsKeyDown(KeyCode::C)) {

		//connect(main_, sub_);
	}

	// êVÇµÇ¢ç¿ïWÇï€ë∂Ç∑ÇÈ
	//position_ = Vector3::Lerp(position_, curPosition, 0.8f);


}

void Player::onLateUpdate(float deltaTime){
}

void Player::onDraw() const {
	//DrawFormatString(25, 25, GetColor(255, 255, 255), "%d", stateMgr_.currentState());

	//DrawFormatString(100, 25, GetColor(255, 255, 255), "%d", );

	//body_.draw(/*inv()*/);
}

void Player::onCollide(Actor & other){}

void Player::changeMotion(float deltaTime){

	if (InputMgr::GetInstance().IsKeyDown(KeyCode::L)) {
		motion_ = (motion_ + 1) % 10;
		//animation_.changeAnim(motion_);
	}
	if (InputMgr::GetInstance().IsKeyDown(KeyCode::K)) {
		motion_ = ((motion_ - 1) + 10) % 10;
		//animation_.changeAnim(motion_);
	}
}

void Player::setBody(PlayerBodyPtr main, PlayerBodyPtr sub){
	main_ = main;	
	sub_ = sub;
}

void Player::connect(PlayerBodyPtr main, PlayerBodyPtr sub){
	addChild(std::make_shared<PlayerConnector>(world_, main, sub));
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
}

void Player::split_body(){
	if (stateMgr_.currentState() == (unsigned int)PlayerState_Enum_Union::SPLIT)return;
	auto cntr = findCildren((const std::string)"PlayerConnector");
	if (cntr == nullptr)return;
	cntr->dead();
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Union::SPLIT));
}

PlayerBodyPtr Player::getMainBody() {
	return main_;
}
PlayerBodyPtr Player::getSubBody(){
	return sub_;
}




