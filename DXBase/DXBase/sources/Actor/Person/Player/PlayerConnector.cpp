#include "PlayerConnector.h"
#include"../../Body/CollisionBase.h"

#include "PlayerBodyPoint.h"
#include "../../../Renderer/DrawShape.h"
#include "../../../Game/Time.h"
PlayerConnector::PlayerConnector() {}

PlayerConnector::PlayerConnector(IWorld * world, const Vector2 & position, PlayerBodyPtr butty, PlayerBodyPtr retty) :
	Actor(world, "PlayerConnector", position, CollisionBase()),
	action_type_(ActionType::Right),
	mPower(0.0f),
	mPuyoTimer(0.0f),
	mPuyoFlag(false) {
	butty_ = butty;
	retty_ = retty;

	create_point(PLAYER_CNTR_DIV_NUM);
	mPuyo = new PuyoTextureK(world, TextureID::PUYO_TEST_TEX, position, 1, 0);
}

PlayerConnector::~PlayerConnector() {
	delete mPuyo;
}

void PlayerConnector::onUpdate(float deltaTime) {
	position_ = (butty_->getPosition() + retty_->getPosition()) / 2;


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

	points_update();
}

void PlayerConnector::onLateUpdate(float deltaTime) {}

void PlayerConnector::onDraw() const {
	//mPuyo->PuyoDraw();

	//body_.draw();
	//bezier_.draw(100, inv_);
}

void PlayerConnector::onCollide(Actor & other) {}

void PlayerConnector::create_point(int point_num) {
	for (int i = 0; i < point_num; i++) {
		auto point = std::make_shared<PlayerBodyPoint>(world_, position_, i/*, *this*/);
		addChild(point);
		points.push_back(point);
	}
}

void PlayerConnector::points_update(){
	auto player = std::dynamic_pointer_cast<Player>(world_->findActor("Player"));

	if (player->action_type(ActionType::Right)) action_type_ = ActionType::Right;
	if (player->action_type(ActionType::Left)) 	action_type_ = ActionType::Left;

	if (action_type_ == ActionType::Right) {
		for (int i = points.size() - 1; i >= 0; i--) {
			points[i]->compose_pos();
		}
	}
	if (action_type_ == ActionType::Left) {
		for (int i = 0; i < points.size(); i++) {
			points[i]->compose_pos();
		}
	}
}

Vector2 PlayerConnector::base_point(ActionType type) {
	if (type == ActionType::Right) return points[0]->getPosition();
	if (type == ActionType::Left)  return points[points.size() - 1]->getPosition();
	return Vector2::Zero;
}

Vector2 PlayerConnector::target() {
	if (action_type_ == ActionType::Right) {
		return butty_->getPosition();
	}
	else if (action_type_ == ActionType::Left) {
		return retty_->getPosition();
	}
	return Vector2::Zero;
}

Vector2 PlayerConnector::comp() {
	if (action_type_ == ActionType::Right) {
		return retty_->getPosition() - butty_->getPosition();

	}
	else if (action_type_ == ActionType::Left) {
		return butty_->getPosition() - retty_->getPosition();
	}
	return Vector2::Zero;
}

Vector2 PlayerConnector::target_vector(int index) {
	float length = 0;
	float cur_length = comp().Length();
	(cur_length > PLAYER_MAX_STRETCH_LENGTH) ? length = PLAYER_CNTR_DIV_LENGTH : length = cur_length / static_cast<float>(PLAYER_CNTR_DIV_NUM + 1);

	if (action_type_ == ActionType::Right) {
		return butty_->getPosition() + (retty_->getPosition() - butty_->getPosition()).Normalize() * length * (index + 1);
	}
	else if (action_type_ == ActionType::Left) {
		return retty_->getPosition() + (butty_->getPosition() - retty_->getPosition()).Normalize() * length * (points.size() - index);
	}
}

Vector2 PlayerConnector::clamp_target(Vector2 pos, int index) {

	Vector2 target = Vector2::Zero;
	if (action_type_ == ActionType::Right) {
		if (index == 0) target = butty_->getPosition();
		else target = points[index - 1]->getPosition();
	}

	if (action_type_ == ActionType::Left) {
		if (index == points.size() - 1) target = retty_->getPosition();
		else target = points[index + 1]->getPosition();
	}

	Vector2 vec = pos - target;
	if (vec.Length() <= PLAYER_CNTR_DIV_LENGTH) return pos;

	return target + vec.Normalize() * PLAYER_CNTR_DIV_LENGTH;
}

std::vector<Vector2> PlayerConnector::get_points() {
	std::vector<Vector2>points_pos = std::vector<Vector2>();
	for (auto i : points) {
		points_pos.push_back(i->getPosition());
	}
	return points_pos;
}

Vector2 PlayerConnector::get_point(int index) {
	return points[index]->getPosition();
}


