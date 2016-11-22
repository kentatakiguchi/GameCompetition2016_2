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
#include "State/States/Union/Elements/PlayerState_Dead.h"


#include <memory>
#include <algorithm>

Player::Player(IWorld * world, const Vector2 & position) :
	Actor(world, "Player", position, CollisionBase(Vector2(0, 0), Vector2(0, 0), 8.0f)){

	auto body1 = std::make_shared<PlayerBody>(world_, "PlayerBody1", position_ - Vector2::Right * PLAYER_MAX_NORMAL_LENGTH / 2);
	auto body2 = std::make_shared<PlayerBody>(world_, "PlayerBody2", position_ + Vector2::Right * PLAYER_MAX_NORMAL_LENGTH / 2);

	addChild(body1);
	addChild(body2);

	struct_ = PlayerStruct(body1, body2, nullptr);

	set_body();

	stateMgr_.add((unsigned int)PlayerState_Enum_Union::STAND_BY, std::make_shared<PlayerState_StandBy>(std::shared_ptr<Player>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::IDLE, std::make_shared<PlayerState_Idle>(std::shared_ptr<Player>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::MOVE, std::make_shared<PlayerState_Move>(std::shared_ptr<Player>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::HOLD, std::make_shared<PlayerState_Hold>(std::shared_ptr<Player>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::HOLD_BOTH, std::make_shared<PlayerState_HoldBoth>(std::shared_ptr<Player>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::ATTACK, std::make_shared<PlayerState_Attack>(std::shared_ptr<Player>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::SPLIT, std::make_shared<PlayerState_Split>(std::shared_ptr<Player>(this)));
	stateMgr_.add((unsigned int)PlayerState_Enum_Union::DEAD, std::make_shared<PlayerState_Dead>(std::shared_ptr<Player>(this)));
	stateMgr_.changeState(IState::StateElement((unsigned int)PlayerState_Enum_Union::STAND_BY));

	connect();
}

Player::~Player(){}

void Player::onUpdate(float deltaTime) {

	stateMgr_.action(deltaTime);

	if (is_damaged()) split();

	if (is_connectable()) connect();

	if (is_dead()) dead();

	if (is_cleared()) world_->clear(true);
}

void Player::onLateUpdate(float deltaTime){
}

void Player::onDraw() const {
	//DrawFormatString(25, 25, GetColor(255, 255, 255), "%d", stateMgr_.currentState());
}

void Player::onCollide(Actor & other){}

PlayerStruct& Player::getStruct(){
	return struct_;
}

void Player::body_chase(){
	struct_.butty()->chase();
	struct_.retty()->chase();
}

void Player::body_clamp(){
	struct_.butty()->circleClamp();
	struct_.retty()->circleClamp();
}

void Player::body_gravity(){	
	struct_.butty()->gravity();
	struct_.retty()->gravity();
}

void Player::set_body(){
	struct_.butty()->set_partner(struct_.retty());
	struct_.retty()->set_partner(struct_.butty());
}

//PlayerBodyPtr Player::getMainBody() {
//	return main_;
//}
//
//PlayerBodyPtr Player::getSubBody() {
//	return sub_;
//}
//
//PlayerCntrPtr Player::getConnector(){
//	return cntr_;
//}

void Player::connect(){
	auto cntr = std::make_shared<PlayerConnector>(world_, struct_.butty(), struct_.retty());
	addChild(cntr);
	struct_.set_cntr(cntr);
	stateMgr_.changeState(IState::StateElement((unsigned int)PlayerState_Enum_Union::IDLE));
}

void Player::split(){
	if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::SPLIT))return;
	struct_.cntr()->dead();
	stateMgr_.changeState(IState::StateElement((unsigned int)PlayerState_Enum_Union::SPLIT));
}

bool Player::is_connectable(){
	bool is_split_state = stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::SPLIT);
	bool is_main_target_partner = struct_.butty()->hit_partner() == HitOpponent::PARTNER;
	bool is_sub_target_partner = struct_.retty()->hit_partner() == HitOpponent::PARTNER;
	bool for_debug = InputMgr::GetInstance().IsKeyDown(KeyCode::C);
	
	return is_split_state && (is_main_target_partner || is_sub_target_partner || for_debug);
}

bool Player::is_damaged(){
	bool is_main_target_enemy = struct_.butty()->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_target_enemy = struct_.retty()->hit_enemy() == HitOpponent::ENEMY;
	bool for_debug = InputMgr::GetInstance().IsKeyDown(KeyCode::P);
			
	return is_main_target_enemy || is_sub_target_enemy || for_debug;
}

bool Player::is_cleared(){
	bool is_main_target_partner = struct_.butty()->hit_enemy() == HitOpponent::CLEAR;
	bool is_sub_target_partner = struct_.retty()->hit_enemy() == HitOpponent::CLEAR;
	return is_main_target_partner || is_sub_target_partner;
}

bool Player::is_dead(){
	bool is_main_dead = struct_.butty()->isDead();
	bool is_main_target_enemy = struct_.butty()->hit_enemy() == HitOpponent::ENEMY;
	bool is_main_invincible = struct_.butty()->isInv();

	bool is_sub_dead = struct_.retty()->isDead();
	bool is_sub_target_enemy = struct_.retty()->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_invincible = struct_.retty()->isInv();

	return (is_main_dead && is_sub_dead) || (is_main_target_enemy && !is_main_invincible) || (is_sub_target_enemy && !is_sub_invincible);
}






