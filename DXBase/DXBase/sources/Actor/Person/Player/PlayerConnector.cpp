#include "PlayerConnector.h"

#include"../../Body/CollisionBase.h"

#include "PlayerBody.h"
#include "PlayerBodyPoint.h"

#include "../Player/Effect/PlayerEffectObj.h"

#include "../../../Game/Time.h"

PlayerConnector::PlayerConnector(IWorld * world, const Vector2 & position, PlayerBodyPtr butty, PlayerBodyPtr retty) :
	Actor(world, "PlayerConnector", position, CollisionBase()), butty_(butty), retty_(retty),
	mPower(0.0f),
	mPuyoTimer(0.0f),
	mPuyoFlag(false) {
	// ポイントの生成
	create_point(PLAYER_CNTR_DIV_NUM);
	stateMgr_.change(*this, PlayerState_Enum_Union::STAND_BY);
	Vector2 texSize = ResourceLoader::GetInstance().GetTextureSize(TextureID::PUYO_TEST_TEX);
	inv();
	mPuyo = new PuyoTextureK(world, TextureID::PUYO_TEST_TEX, position_*inv_, 1, 0);
}

PlayerConnector::~PlayerConnector() {
	delete mPuyo;
}

void PlayerConnector::onUpdate(float deltaTime) {
	position_ = (butty_->getPosition() + retty_->getPosition()) / 2;

	if (is_damaged()) {
		world_->addActor(ActorGroup::Effect, std::make_shared<PlayerEffectObj>(world_, position_, PlayerEffectID::SEP_EXP, 5.0f, 3.0f));
		dead();
	}
	if (is_cleared()) world_->clear(true);
	//ぷよテクスチャUPdate
	puyoUpdate();
}

void PlayerConnector::onDraw() const {
	if (world_->isEntered())return;

	mPuyo->PuyoDraw();
}

PlayerBodyPtr PlayerConnector::blue_body() {
	return butty_;
}

PlayerBodyPtr PlayerConnector::red_body() {
	return retty_;
}

PlayerStateMgr_Union& PlayerConnector::state_mgr() {
	return stateMgr_;
}

void PlayerConnector::state_update(float deltaTime) {
	stateMgr_.action(*this, deltaTime);
}

void PlayerConnector::create_point(int point_num) {
	for (int i = 0; i < point_num; i++) {
		auto point = std::make_shared<PlayerBodyPoint>(world_, position_, i);
		addChild(point);
		points.push_back(point);
	}
}

float PlayerConnector::length_sum() {
	float sum = 0;
	float len1 = Vector2::Distance(butty_->position_, get_point(0));
	float len2 = Vector2::Distance(retty_->position_, get_point(points.size() - 1));
	for (unsigned int i = 0; i < points.size() - 1; i++) {
		sum += Vector2::Distance(points[i]->getPosition(), points[i + 1]->getPosition());
	}
	return sum + len1 + len2;
}

bool PlayerConnector::is_damaged() {
	bool is_attack_state = stateMgr_.get_state(PlayerState_Enum_Union::ATTACK);
	bool is_event_state = stateMgr_.get_state(PlayerState_Enum_Union::EVENT);
	bool is_leanback_state = stateMgr_.get_state(PlayerState_Enum_Union::LEAN_BACK);
	bool is_main_target_enemy = butty_->hit_enemy() == HitOpponent::ENEMY;
	bool is_sub_target_enemy = retty_->hit_enemy() == HitOpponent::ENEMY;
	bool for_debug = InputMgr::GetInstance().IsKeyDown(KeyCode::P);

	return !is_event_state && !is_leanback_state && !is_attack_state && (is_main_target_enemy || is_sub_target_enemy || for_debug);
}

bool PlayerConnector::is_cleared() {
	bool is_main_target_partner = butty_->hit_enemy() == HitOpponent::CLEAR;
	bool is_sub_target_partner = retty_->hit_enemy() == HitOpponent::CLEAR;
	return is_main_target_partner || is_sub_target_partner;
}

Vector2 PlayerConnector::get_point(int index) {
	if (index == points.size()) return retty_->getPosition();
	if (index == -1) return butty_->getPosition();
	return points[index]->getPosition();
}

void PlayerConnector::puyoUpdate() {
	float x = ((butty_->getPosition() + retty_->getPosition()) / 2).x;
	float y = ((butty_->getPosition() + retty_->getPosition()) / 2).y;
	Vector3 pos = Vector3(x, y, 0);
	Vector2 center = points[(int)(points.size() / 2)]->getPosition();

	Vector3 color;

	pos = pos*inv_;

	Vector2 posVec2 = Vector2(pos.x, pos.y);
	Vector2 vec1 = butty_->getPosition() - Vector2(x, y);
	Vector2 vec2 = retty_->getPosition() - Vector2(x, y);

	mPower = vec1.Length();
	//左のやつが引っ張ってる
	if (stateMgr_.currentActionType(ActionType::Right) &&
		stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)) {
		mPuyoResPos = vec2*0.3f;
		mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower*0.4f, 175.0f);
		mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f, center);
		mPuyoTimer = 0.0f;
		mPuyoFlag = true;
	}
	//右のやつが引っ張ってる
	else if (stateMgr_.currentActionType(ActionType::Left) &&
		stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD)) {
		mPuyoResPos = vec1*0.3f;
		mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower*0.4f, 175.0f);
		mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f, center);
		mPuyoTimer = 0.0f;
		mPuyoFlag = true;
	}
	//同時押し
	else if (stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD_BOTH))
	{
		mPuyoResPos = Vector2::Zero;
		mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f, center);
		mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower / 7.0f, 200.0f);
		mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower / 7.0f, 200.0f);
	}
	//何もしていない
	else
	{
		mPuyoResPos = Vector2::Zero;
		if (!mPuyoFlag) {
			mPuyo->PuyoAddPowerEx(vec2.Normalize(), vec2, mPower / 7.0f, 175.0f);
			mPuyo->PuyoAddPowerEx(vec1.Normalize(), vec1, mPower / 7.0f, 175.0f);
		}
		mPuyo->SetPosition(posVec2 + mPuyoPos, 1.0f, 0.0f, center);
	}

	Vector2::Spring(mPuyoPos, mPuyoResPos, mPuyoVelo, 0.2f);
	//飛ぶ瞬間は力をどこも加えない
	if (mPuyoFlag) {
		mPuyoTimer += Time::GetInstance().deltaTime();
		if (mPuyoTimer >= 0.5f) {
			mPuyoFlag = false;
		}
	}
	//距離が330だったため
	float dis = Vector2::Distance(butty_->getPosition(), retty_->getPosition()) / 330.0f;
	color = Vector3(255, MathHelper::Lerp(255, 0, dis), MathHelper::Lerp(255, 0, dis));

	mPuyo->PuyoPlayerPos(butty_->getPosition()*inv_, retty_->getPosition()*inv_, color,
		stateMgr_.currentState((unsigned int)PlayerState_Enum_Union::HOLD));
	mPuyo->PuyoUpdate();
}


