#include "Player.h"

#include"../../Body/CollisionBase.h"
#include "../../../ResourceLoader/ResourceLoader.h"

#include "State/Base/State_Dammy.h"
#include "State/States/Union/Elements/PlayerState_StandBy.h"
#include "State/States/Union/Elements/PlayerState_Idle.h"
#include "State/States/Union/Elements/PlayerState_Move.h"
#include "State/States/Union/Elements/PlayerState_MoveBoth.h"
#include "State/States/Union/Elements/PlayerState_Jump.h"
#include "State/States/Union/Elements/PlayerState_Hold.h"
#include "State/States/Union/Elements/PlayerState_HoldBoth.h"
#include "State/States/Union/Elements/PlayerState_Attack.h"
#include "State/States/Union/Elements/PlayerState_Freeze.h"
#include "State/States/Union/Elements/PlayerState_Damage.h"
#include "State/States/Union/Elements/PlayerState_Split.h"
#include "State/States/Union/Elements/PlayerState_Dead.h"


#include <memory>
#include <algorithm>

Player::Player(IWorld * world, const Vector2 & position) :
	Actor(world, "Player", position, CollisionBase(Vector2(0, 0), Vector2(0, 0), 8.0f)),
	mPower(0.0f){

	auto body1 = std::make_shared<PlayerBody>(world_, "PlayerBody1", position_ + Vector2::Right * PLAYER_MAX_NORMAL_LENGTH / 2);
	auto body2 = std::make_shared<PlayerBody>(world_, "PlayerBody2", position_ - Vector2::Right * PLAYER_MAX_NORMAL_LENGTH / 2);

	addChild(body1);
	addChild(body2);

	butty_ = body1;
	retty_ = body2;

	set_body();

	stateMgr_.add((unsigned int)PlayerState_Enum_Union::STAND_BY, std::make_shared<PlayerState_StandBy>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::IDLE, std::make_shared<PlayerState_Idle>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::MOVE, std::make_shared<PlayerState_Move>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::MOVE_BOTH, std::make_shared<PlayerState_MoveBoth>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::JUMP, std::make_shared<PlayerState_Jump>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::HOLD, std::make_shared<PlayerState_Hold>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::HOLD_BOTH, std::make_shared<PlayerState_HoldBoth>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::ATTACK, std::make_shared<PlayerState_Attack>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::FREEZE, std::make_shared<PlayerState_Freeze>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::SPLIT, std::make_shared<PlayerState_Split>());
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::DEAD, std::make_shared<PlayerState_Dead>());
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Union::STAND_BY));

	connect();

	mPuyo = new PuyoTextureK(TextureID::PUYO_TEST_TEX, position, 1, 0);
}

Player::~Player(){
	delete mPuyo;
}

void Player::onUpdate(float deltaTime) {

	//stateMgr_.action(*this, deltaTime);

	//mPuyo->PuyoUpdate();

	//float x = ((butty_->getPosition() + retty_->getPosition()) / 2).x;
	//float y = ((butty_->getPosition() + retty_->getPosition()) / 2).y;
	//Vector3 pos = Vector3(x, y, 0);
	//pos = pos*inv_;
	//Vector2 posVec2 = Vector2(pos.x, pos.y);

	//Vector2 vec1 = butty_->getPosition() - Vector2(x, y);
	//Vector2 vec2 = retty_->getPosition() - Vector2(x, y);
	////Vector2 point1 = main_->getPosition();
	////Vector2 point2 = main_->getPosition() + vec1;

	//DrawCircle(vec1.x, vec1.y, 30, GetColor(255, 255, 255));
	//mPower = vec1.Length();
	//if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)||
	//	stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD_BOTH)) {
	//	//mPuyo->PuyoAddPowerEx(vec1, vec1*3.0f);
	//	mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower);
	//	mPuyo->SetPosition(posVec2 + vec2, 1.0f, 0.0f);
	//	//mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, power);
	//}
	////mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower);
	////mPuyo->SetPosition(posVec2 + vec2, 1.0f, 0.0f);
	//else
	//{
	//	mPuyo->SetPosition(posVec2, 1.0f, 0.0f);
	//}


	///*******‚Ç‚¿‚ç‚ðHOLD‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©*******/
	///*ActionType‚Å”»’f‰Â”\*/
	//if (stateMgr_.currentActionType(ActionType::Right)) {

	//}
	///**********************/

	stateMgr_.action(*this, deltaTime);

	mPuyo->PuyoUpdate();

	float x = ((butty_->getPosition() + retty_->getPosition()) / 2).x;
	float y = ((butty_->getPosition() + retty_->getPosition()) / 2).y;
	Vector3 pos = Vector3(x, y, 0);
	pos = pos*inv_;
	Vector2 posVec2 = Vector2(pos.x, pos.y);

	Vector2 vec1 = butty_->getPosition() - Vector2(x, y);
	Vector2 vec2 = retty_->getPosition() - Vector2(x, y);
	//Vector2 point1 = main_->getPosition();
	//Vector2 point2 = main_->getPosition() + vec1;

	DrawCircle(vec1.x, vec1.y, 30, GetColor(255, 255, 255));
	mPower = vec1.Length();
	//if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)||
	//	stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD_BOTH)) {
	//	//mPuyo->PuyoAddPowerEx(vec1, vec1*3.0f);

	//	//mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, power);
	//}
	//mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower);
	//mPuyo->SetPosition(posVec2 + vec2, 1.0f, 0.0f);

	//if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD) &&
	//	stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD_BOTH))
	//{
	//	mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower);
	//	mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower);
	//	mPuyo->SetPosition(posVec2, 1.0f, 0.0f);
	//}
	//else if (stateMgr_.currentActionType(ActionType::Right)&&
	//	stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)) {
	//	mPuyoResPos = vec2;
	//	mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower);
	//	mPuyo->SetPosition(posVec2 + mpPuyoPos, 1.0f, 0.0f);
	//}
	//else if (stateMgr_.currentActionType(ActionType::Left)&&
	//	stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)) {
	//	mPuyoResPos = vec1;
	//	mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower);
	//	mPuyo->SetPosition(posVec2+mpPuyoPos, 1.0f, 0.0f);
	//}
	//else if(stateMgr_.currentActionType(ActionType::Right)||
	//	stateMgr_.currentActionType(ActionType::Left))
	//{
	//	mPuyoResPos = Vector2::Zero;
	//	mPuyo->SetPosition(posVec2 + mpPuyoPos, 1.0f, 0.0f);
	//	mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower/6.0f);
	//	mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower/6.0f);
	//}
	//else
	//{
	//	mPuyoResPos = Vector2::Zero;
	//	mPuyo->SetPosition(posVec2 + mpPuyoPos, 1.0f, 0.0f);
	//}

	if (stateMgr_.currentActionType(ActionType::Right) &&
		stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)) {
		mPuyoResPos = vec2*0.6f;
		mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower*0.8f, 170.0f);
		mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f);
	}
	else if (stateMgr_.currentActionType(ActionType::Left) &&
		stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)) {
		mPuyoResPos = vec1*0.6f;
		mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower*0.8f, 170.0f);
		mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f);
	}
	else if (stateMgr_.currentActionType(ActionType::Left) ||
		stateMgr_.currentActionType(ActionType::Right)) {
		mPuyoResPos = Vector2::Zero;
		mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f);
	}
	else
	{
		mPuyoResPos = Vector2::Zero;
		mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower / 5.0f, 150.0f);
		mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower / 5.0f, 150.0f);
		mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f);
	}

	Vector2::Spring(mPuyoPos, mPuyoResPos, mPuyoVelo, 0.2f);



	if (is_damaged()) split();
	if (is_connectable()) connect();
	if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::DEAD)) dead();
	if (is_cleared()) world_->clear(true);
}

void Player::onLateUpdate(float deltaTime){
}

void Player::onDraw() const {
	//DrawFormatString(25, 25, GetColor(255, 255, 255), "%d", stateMgr_.currentState());
	mPuyo->PuyoDraw();
}

void Player::onCollide(Actor & other){}

PlayerBodyPtr Player::blue_body(){
	return butty_;
}

PlayerBodyPtr Player::red_body(){
	return retty_;
}

PlayerCntrPtr Player::connector(){
	return cntr_;
}

void Player::body_chase(){
	butty_->chase();
	retty_->chase();
}

void Player::body_clamp(){
	butty_->circleClamp(cntr_->base_point(ActionType::Right));
	retty_->circleClamp(cntr_->base_point(ActionType::Left));
}

void Player::body_gravity(){	
	butty_->gravity();
	retty_->gravity();
}

bool Player::action_type(ActionType type){
	return stateMgr_.currentActionType(type);
}

void Player::set_body(){
	butty_->set_partner(retty_);
	retty_->set_partner(butty_);
}

void Player::connect(){
	auto cntr = std::make_shared<PlayerConnector>(world_, position_, butty_, retty_);
	addChild(cntr);
	cntr_ = cntr;
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
}

void Player::split(){
	if (stateMgr_.currentState())return;
	cntr_->dead();
	stateMgr_.changeState(*this, IState::StateElement((unsigned int)PlayerState_Enum_Union::SPLIT));
}

bool Player::is_connectable(){
	bool is_split_state = stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::SPLIT);
	bool is_main_target_partner = butty_->hit_partner() == HitOpponent::PARTNER;
	bool is_sub_target_partner = retty_->hit_partner() == HitOpponent::PARTNER;
	bool for_debug = InputMgr::GetInstance().IsKeyDown(KeyCode::C);
	
	return is_split_state && (is_main_target_partner || is_sub_target_partner || for_debug);
}

bool Player::is_damaged(){
	bool is_split_state = stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::SPLIT);
	bool is_main_target_enemy = butty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_target_enemy = retty_->hit_enemy() == HitOpponent::ENEMY;
	bool for_debug = InputMgr::GetInstance().IsKeyDown(KeyCode::P);
			
	return !is_split_state && (is_main_target_enemy || is_sub_target_enemy || for_debug);
}

bool Player::is_cleared(){
	bool is_main_target_partner = butty_->hit_enemy() == HitOpponent::CLEAR;
	bool is_sub_target_partner = retty_->hit_enemy() == HitOpponent::CLEAR;
	return is_main_target_partner || is_sub_target_partner;
}

bool Player::is_dead(){
	bool is_main_dead = butty_->isDead();
	bool is_main_target_enemy = butty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_main_invincible = butty_->isInv();

	bool is_sub_dead = retty_->isDead();
	bool is_sub_target_enemy = retty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_invincible = retty_->isInv();

	return (is_main_dead && is_sub_dead) || (is_main_target_enemy && !is_main_invincible) || (is_sub_target_enemy && !is_sub_invincible);
}






