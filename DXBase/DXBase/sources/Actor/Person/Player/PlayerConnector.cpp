#include "PlayerConnector.h"
#include"../../Body/CollisionBase.h"


#include "PlayerBody.h"
#include "PlayerBodyPoint.h"
#include "../../../Renderer/DrawShape.h"
#include "../../../Game/Time.h"

PlayerConnector::PlayerConnector(IWorld * world, const Vector2 & position, PlayerBodyPtr butty, PlayerBodyPtr retty) :
	Actor(world, "PlayerConnector", position, CollisionBase()), butty_(butty), retty_(retty),
	mPower(0.0f),
	mPuyoTimer(0.0f),
	mPuyoFlag(false) {
	create_point(PLAYER_CNTR_DIV_NUM);

	stateMgr_.change(*this, PlayerState_Enum_Union::STAND_BY);

	mPuyo = new PuyoTextureK(world, TextureID::PUYO_TEST_TEX, position, 1, 0);
}

PlayerConnector::~PlayerConnector() {
	delete mPuyo;
}

void PlayerConnector::onUpdate(float deltaTime) {
	position_ = (butty_->getPosition() + retty_->getPosition()) / 2;

	if (is_damaged()) {
		butty_->init_state(PlayerState_Enum_Single::STAND_BY);
		retty_->init_state(PlayerState_Enum_Single::STAND_BY);
		dead();
	}
	if (is_cleared()) world_->clear(true);

	//mPuyo->PuyoUpdate();

	//float x = ((butty_->getPosition() + retty_->getPosition()) / 2).x;
	//float y = ((butty_->getPosition() + retty_->getPosition()) / 2).y;
	//Vector3 pos = Vector3(x, y, 0);
	//Vector2 center = Vector2(x, y);

	//pos = pos*inv_;

	//Vector2 posVec2 = Vector2(pos.x, pos.y);

	//Vector2 vec1 = butty_->getPosition() - Vector2(x, y);
	//Vector2 vec2 = retty_->getPosition() - Vector2(x, y);
	//mPower = vec1.Length();
	////¶‚Ì‚â‚Â‚ªˆø‚Á’£‚Á‚Ä‚é
	//if (stateMgr_.currentActionType(ActionType::Right) &&
	//	stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)) {
	//	mPuyoResPos = vec2*0.6f;
	//	mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower*0.6f, 175.0f);
	//	mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f, center);
	//	mPuyoTimer = 0.0f;
	//	mPuyoFlag = true;
	//}
	////‰E‚Ì‚â‚Â‚ªˆø‚Á’£‚Á‚Ä‚é
	//else if (stateMgr_.currentActionType(ActionType::Left) &&
	//	stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)) {
	//	mPuyoResPos = vec1*0.6f;
	//	mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower*0.6f, 175.0f);
	//	mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f, center);
	//	mPuyoTimer = 0.0f;
	//	mPuyoFlag = true;
	//}
	////“¯Žž‰Ÿ‚µ
	//else if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD_BOTH))
	//{
	//	mPuyoResPos = Vector2::Zero;
	//	mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f, center);
	//	mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower / 7.0f, 200.0f);
	//	mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower / 7.0f, 200.0f);
	//}
	////‰½‚à‚µ‚Ä‚¢‚È‚¢
	//else
	//{
	//	mPuyoResPos = Vector2::Zero;
	//	if (!mPuyoFlag) {
	//		mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower / 7.0f, 175.0f);
	//		mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower / 7.0f, 175.0f);
	//	}
	//	mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f, center);
	//}

	//Vector2::Spring(mPuyoPos, mPuyoResPos, mPuyoVelo, 0.2f);
	////”ò‚ÔuŠÔ‚Í—Í‚ð‚Ç‚±‚à‰Á‚¦‚È‚¢
	//if (mPuyoFlag) {
	//	mPuyoTimer += Time::GetInstance().deltaTime();
	//	if (mPuyoTimer >= 0.5f) {
	//		mPuyoFlag = false;
	//	}
	//}
}

void PlayerConnector::onLateUpdate(float deltaTime) {}

void PlayerConnector::onDraw() const {
	//mPuyo->PuyoDraw();

	//body_.draw();
	//bezier_.draw(100, inv_);
}

void PlayerConnector::onCollide(Actor & other) {}

PlayerBodyPtr PlayerConnector::blue_body() {
	return butty_;
}

PlayerBodyPtr PlayerConnector::red_body() {
	return retty_;
}

PlayerStateMgr_Union& PlayerConnector::state_mgr() {
	return stateMgr_;
}

void PlayerConnector::state_action(float deltaTime) {
	stateMgr_.action(*this, deltaTime);
}

void PlayerConnector::create_point(int point_num) {
	for (int i = 0; i < point_num; i++) {
		auto point = std::make_shared<PlayerBodyPoint>(world_, position_, i);
		addChild(point);
		points.push_back(point);
	}
}

std::vector<Vector2> PlayerConnector::get_points() {
	std::vector<Vector2>points_pos = std::vector<Vector2>();
	for (auto i : points) {
		points_pos.push_back(i->getPosition());
	}
	return points_pos;
}

bool PlayerConnector::is_damaged() {
	//bool is_split_state = stateMgr_.get_state(PlayerState_Enum_Union::SPLIT);
	bool is_attack_state = stateMgr_.get_state(PlayerState_Enum_Union::ATTACK);
	bool is_main_target_enemy = butty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_target_enemy = retty_->hit_enemy() == HitOpponent::ENEMY;
	bool for_debug = InputMgr::GetInstance().IsKeyDown(KeyCode::P);

	return /*!is_split_state && */!is_attack_state && (is_main_target_enemy || is_sub_target_enemy || for_debug);
}

bool PlayerConnector::is_cleared() {
	bool is_main_target_partner = butty_->hit_enemy() == HitOpponent::CLEAR;
	bool is_sub_target_partner = retty_->hit_enemy() == HitOpponent::CLEAR;
	return is_main_target_partner || is_sub_target_partner;
}

bool PlayerConnector::is_dead() {
	bool is_main_dead = butty_->dead_limit();
	bool is_main_target_enemy = butty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_main_invincible = butty_->isInv();

	bool is_sub_dead = retty_->dead_limit();
	bool is_sub_target_enemy = retty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_invincible = retty_->isInv();

	return (is_main_dead && is_sub_dead) || (is_main_target_enemy && !is_main_invincible) || (is_sub_target_enemy && !is_sub_invincible);
}

Vector2 PlayerConnector::get_point(int index) {
	if (index == -1) {
		return butty_->getPosition();
	}
	if (index == points.size()) {
		return retty_->getPosition();
	}
	return points[index]->getPosition();
}


